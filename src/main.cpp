#include <3ds.h>
#include <vector>
#include "csvc.h"
#include "cheats.h"

namespace CTRPluginFramework {

class OverlayPluginMenu {
public:
  std::vector<MenuEntry*> entries;

  void append(MenuEntry* entry)
  {
    this->entries.emplace_back(entry);
  }
};

OverlayPluginMenu* overlay_menu = nullptr;

// ----------------------------------------------------
//  Overlay Menu
// ----------------------------------------------------
void OverlayMenu(MenuEntry* e)
{
  static bool is_opened = false;

  static size_t index = 0;

  static auto const osd = [](Screen const& screen) -> bool {
    constexpr int height = 14;
    constexpr int max = 240 / height;
    constexpr int firstdy = (240 - height * max) / 2;

    static char strbuf[0x100];

    if (!screen.IsTop || !is_opened)
      return false;

    u32 start = std::max<int>(0, (int)index - 6);

    u32 const end =
      std::min<int>(overlay_menu->entries.size(), start + max);

    u32 dy = firstdy;

    for (; start < end; start++, dy += height) {
      auto& entry = overlay_menu->entries[start];

      sprintf(strbuf, "[%c] %s", entry->IsActivated() ? '*' : ' ',
              entry->Name().c_str());

      if (start == index)
        screen.Draw(">", 16, dy);

      screen.Draw(strbuf, 24, dy);
    }

    return true;
  };

  if (e->WasJustActivated())
    OSD::Run(osd);
  else if (!e->IsActivated())
    OSD::Stop(osd);

  if (Controller::IsKeysPressed(Key::Start | Key::ZL)) {
    is_opened ^= 1;
  }

  if (!is_opened)
    return;

  auto menu = overlay_menu;

  if (Controller::IsKeysPressed(Key::CPadUp)) {
    if (index >= 1)
      index--;
  }
  else if (Controller::IsKeysPressed(Key::CPadDown)) {
    if (index + 1 < menu->entries.size())
      index++;
  }

  if (Controller::IsKeysPressed(Key::X)) {
    if (auto entry = menu->entries[index]; entry->IsActivated())
      entry->Disable();
    else
      entry->Enable();
  }

  for (auto&& entry : overlay_menu->entries) {
    if (entry->IsActivated())
      entry->GetGameFunc()(entry);
  }
}

// ----------------------------------------------------
//  Address Viewer
// ----------------------------------------------------
void AddressViewer(MenuEntry* entry)
{
  static u32 addr = 0;
  static u32 value = 0;
  static bool read = 0;

  auto const osd = [](Screen const& screen) -> bool {
    if (!screen.IsTop) {
      screen.Draw(read ? Utils::Format("%08X: %08X", addr, value)
                       : Utils::Format("%08X: ?", addr),
                  8, 8);

      return true;
    }

    return false;
  };

  if (entry->WasJustActivated())
    OSD::Run(osd);
  else if (!entry->IsActivated())
    OSD::Stop(osd);

  if (Controller::IsKeysPressed(Key::ZL)) {
    Keyboard("change address to view").Open(addr, addr);
  }

  read = Process::Read32(addr, value);
}

// ----------------------------------------------------
//  Pointer Viewer
// ----------------------------------------------------
void PointerViewer(MenuEntry* entry)
{
  static constexpr auto readMaximum = 20;

  static u32 addr = 0;
  static u32 value = 0;
  static int index = 0;

  static int offsets[readMaximum]{0};
  static u32 count = 0;

  static u8 rlimit = 10;

  static constexpr auto LineBufferLength = 30;
  static char fullbuf[LineBufferLength * (readMaximum + 1)];

  auto const osd = [](Screen const& screen) -> bool {
    if (!screen.IsTop)
      return false;

    u32 dy = 230 - count * 10;

    char* pbuf = fullbuf;
    dy = screen.Draw(pbuf, 0, dy);

    //
    // cursor
    if (u32 idxdy = dy + index * 10; idxdy <= 230)
      screen.Draw(">", 0, dy + index * 10);

    //
    // addr and offsets
    for (u32 i = 1; i <= rlimit; i++, dy += 10) {
      screen.Draw(pbuf + LineBufferLength * sizeof(char) * i, 8, dy);
    }

    return false;
  };

  if (entry->WasJustActivated())
    OSD::Run(osd);
  else if (!entry->IsActivated())
    OSD::Stop(osd);

  char* pbuf = fullbuf;

  if (Process::Read32(addr, value)) {
    sprintf(pbuf, "%X: %X", addr, value);
  }
  else {
    sprintf(pbuf, "%X: ?", addr);
  }

  for (count = 0; Process::CheckAddress(value) && count < rlimit;
       count++) {
    pbuf += LineBufferLength * sizeof(char);

    if (Process::Read32(value + offsets[count], value)) {
      if (offsets[count] != 0)
        sprintf(pbuf, "%c%x %X", offsets[count] > 0 ? '+' : '-',
                std::abs(offsets[count]), value);
      else
        sprintf(pbuf, "%X", value);
    }
  }

  for (; count <= std::min<u32>(index, rlimit); count++) {
    pbuf += LineBufferLength * sizeof(char);

    if (offsets[count] != 0)
      sprintf(pbuf, "offs=%c%x", offsets[count] > 0 ? '+' : '-',
              std::abs(offsets[count]));
    else
      sprintf(pbuf, "offs=0");
  }

  if (Controller::IsKeysDown(ZL)) {
    if (Controller::IsKeysPressed(Key::X)) {
      Keyboard("change read limit (Maximum = 20)")
        .Open(rlimit, rlimit);

      if (rlimit > 20)
        rlimit = 20;
    }

    if (Controller::IsKeysPressed(DPadLeft)) {
      Keyboard("change first address").Open(addr, addr);
    }

    if (Controller::IsKeysPressed(DPadRight)) {
      Keyboard("change offset")
        .Open((u32&)offsets[index], (u32)offsets[index]);
    }

    if (Controller::IsKeysPressed(DPadUp)) {
      if (--index < 0)
        index = 0;
    }

    if (Controller::IsKeysPressed(DPadDown)) {
      if (++index >= rlimit)
        index = rlimit - 1;
    }
  }
}

// ----------------------------------------------------
//  Search Instruction
// ----------------------------------------------------
void SearchInstruction(MenuEntry* entry)
{
  struct Item {
    u32 addr;  // of opcode
    u32 offset;
  };

  enum SearchType {
    ST_Specify,
    ST_Branch,
  };

  static std::vector<std::string> const searchTypeStrings = {
    "Specify hex-value",
    "Branch",
  };

  static SearchType searchType = ST_Specify;

  static u32 begin = 0x100000;
  static u32 end = 0x200000;
  static u32 target = 0;

  static u32 instruction = 0;  // Don't write

  static std::vector<Item> result;

  static int choice;

  while (true) {
  loop_begin_1:
    choice =
      OSDMenu("Select option", {"New search", "View result"}).open();

    if (choice == -1)
      break;

    if (choice == 0) {
      while (true) {
        choice =
          OSDMenu("Input search-options",
                  {
                    std::string("Search-type: ") +
                      searchTypeStrings[searchType],
                    Utils::Format("Begin address: %08X", begin),
                    Utils::Format("End address: %08X", end),
                    Utils::Format("Instruction = %08X", instruction),
                    "[Search]",
                  })
            .open();

        switch (choice) {
          case 0:
            choice =
              OSDMenu("Select search type", searchTypeStrings).open();

            if (choice != -1)
              searchType = (SearchType)choice;

            continue;

          case 1:
            Keyboard("Begin address").Open(begin, begin);
            continue;

          case 2:
            Keyboard("End address").Open(end, end);
            continue;

          case 4:
            break;

          case -1:
            goto loop_begin_1;
        }

        break;
      }

      if (Keyboard("Begin addr").Open(begin, begin) != 0)
        return;

      if (Keyboard("End addr").Open(end, end) != 0)
        return;

      if (begin >= end) {
        MessageBox(
          "Invalid range, end-address must bigger than "
          "begin-address.")();

        return;
      }

      if (Keyboard("Target addr").Open(target, target) != 0)
        return;

      auto const& screen = OSD::GetTopScreen();

      result.clear();

      Clock clock;

      u32 const range = end - begin;
      u32 tmp = 0;

      for (u32 offset = 0, addr = begin; addr <= end; addr += 4) {
        constexpr int win_width = 240;
        constexpr int win_height = 100;
        constexpr int win_posX = (400 - win_width) / 2;
        constexpr int win_posY = (240 - win_height) / 2;
        constexpr int drawMilliseconds = 100;

        offset = ((target - addr - 8) >> 2) & 0xFFFFFF;

        Controller::Update();

        if (Controller::IsKeysDown(Key::B))
          break;

        if (Process::Read32(addr, tmp) &&
            tmp == (0xEB << 24) | offset) {
          result.emplace_back(Item{addr, offset});
        }

        if (clock.HasTimePassed(Milliseconds(drawMilliseconds))) {
          clock.Restart();

          screen.DrawRect(win_posX + 1, win_posY + 1, win_width - 10,
                          win_height - 10, Color::Black);

          screen.DrawSysfont("Searching...", win_posX + 8,
                             win_posY + 8);

          screen.DrawSysfont(Utils::Format("Now=%X", addr),
                             win_posX + 8, win_posY + 30);

          screen.DrawSysfont(
            Utils::Format("Found: %d/%d", result.size(), range),
            win_posX + 8, win_posY + 46);

          screen.DrawSysfont("(Hold B to cancel)", win_posX + 8,
                             win_posY + 68);
        }

        OSD::SwapBuffers();
        Sleep(Milliseconds(1));
      }

      if (result.empty()) {
        MessageBox("Not found.")();
      }
      else {
        MessageBox(Utils::Format("%d found.", result.size()))();
      }
    }

    if (choice == 1) {
      if (result.empty()) {
        MessageBox("No results.")();
        return;
      }

      std::vector<std::string> vec;

      for (auto&& item : result) {
        vec.emplace_back(
          Utils::Format("%06X: %08X", item.addr, *(u32*)item.addr));
      }

      OSDMenu(
        Utils::Format("Found instructions (target=%08X)", target),
        std::move(vec))
        .open();
    }
  }
}

void PatchProcess(FwkSettings& settings)
{
}

void InstantMenuOptions(MenuEntry* entry)
{
}

void InitMenu(PluginMenu& menu)
{
  menu += new MenuEntry("Instant Menu", InstantMenuOptions);

  auto itemCodes = new MenuFolder("Item Codes");

  *itemCodes += new MenuEntry("Item Wheel", item_wheel);

  *itemCodes +=
    new MenuEntry("Disable bomb-omb limit", disable_bomb_limit);

  *itemCodes +=
    new MenuEntry("Fast bomb-omb explosion", fast_bomb_explosion);

  *itemCodes += new MenuEntry("Big bomb-omb", big_bomb);

  menu += itemCodes;

  auto tools = new MenuFolder("Tools");

  *tools += new MenuEntry("Address Viewer", AddressViewer);
  *tools += new MenuEntry("Pointer Viewer", PointerViewer);

  *tools +=
    new MenuEntry("Search Instruction", nullptr, SearchInstruction);

  menu += tools;
}

int main(void)
{
  PluginMenu menu{"Sevenstar [MK7-Japan 0x30600]", 1, 0, 0, ""};

  menu.ShowWelcomeMessage(false);
  menu.SynchronizeWithFrame(true);

  InitMenu(menu);

  OSD::Notify("sevenstar!");

  return menu.Run();
}

}  // namespace CTRPluginFramework
