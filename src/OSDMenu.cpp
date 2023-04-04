#include "cheats.h"

namespace CTRPluginFramework {

static std::vector<OSDMenu*> _inst;

static OSDMenu& get_instance()
{
  return **_inst.rbegin();
}

OSDMenu::OSDMenu(std::string const& title,
                 std::vector<std::string> const& vec)
  : title(title),
    entries(vec)
{
  _inst.push_back(this);
}

OSDMenu::OSDMenu(std::string&& title, std::vector<std::string>&& vec)
  : title(std::move(title)),
    entries(std::move(vec))
{
  _inst.push_back(this);
}

OSDMenu::~OSDMenu()
{
  _inst.pop_back();
}

int OSDMenu::open(bool useTopScreen, bool overlay)
{
  static bool is_opened = false;
  static int index = 0;

  static auto const drawer = [](Screen const& screen) -> bool {
    constexpr int win_width = 334;
    constexpr int win_height = 194;
    constexpr int win_posX = (400 - win_width) / 2;
    constexpr int win_posY = (240 - win_height) / 2;

    constexpr int height = 10;
    constexpr int titleHeight = 12;
    constexpr int max = (win_height - titleHeight) / height;
    constexpr int firstdy = win_posY + titleHeight + 1;

    if (!screen.IsTop)
      return false;

    auto& inst = get_instance();

    // background
    screen.DrawRect(win_posX, win_posY, win_width, win_height,
                    Color::Black);

    // title-text
    screen.Draw(inst.title, win_posX, win_posY);

    // draw line under title-text
    screen.DrawRect(win_posX + 4, win_posY + titleHeight, 100, 1,
                    Color::White);

    u32 const start = std::max<int>(0, (int)index + max - 4);
    u32 const end = std::min<int>(inst.entries.size(), start + max);

    u32 dy = firstdy;

    for (u32 i = start; i < end; i++, dy += height) {
      screen.Draw(inst.entries[i], win_posX, dy);
    }

    screen.DrawRect(
      win_posX + 1, firstdy + (index - start + 1) * height,
      (inst.entries[index].length() + 1) * 8, 1, Color::Green);

    return true;
  };

  bool isPaused = Process::IsPaused();
  Screen const* screen = nullptr;

  if (overlay) {
    OSD::Run(drawer);
  }
  else {
    if (!isPaused)
      Process::Pause();

    screen =
      useTopScreen ? &OSD::GetTopScreen() : &OSD::GetBottomScreen();
  }

  u32 key_tick = 0;

  while (true) {
    Controller::Update();

    for (auto&& key : {Key::DPadUp, Key::DPadDown}) {
      if (Controller::IsKeysDown(key)) {
        if (key_tick == 0 || (key_tick >= 20 && key_tick % 2 == 0)) {
          if (key == Key::DPadUp) {
            if (index > 0)
              index--;
          }
          else if (index + 1 < this->entries.size()) {
            index++;
          }

          if (key_tick > 30)
            key_tick = 30;
        }

        key_tick++;
      }
      else if (Controller::IsKeysReleased(key)) {
        key_tick = 0;
      }
    }

    if (Controller::IsKeysPressed(Key::A)) {
      break;
    }

    if (Controller::IsKeysPressed(Key::B)) {
      index = -1;
      break;
    }

    Sleep(Milliseconds(1));

    if (!overlay) {
      drawer(*screen);
      OSD::SwapBuffers();
    }
  }

  if (overlay) {
    OSD::Stop(drawer);
  }
  else {
    OSD::SwapBuffers();

    if (!isPaused)
      Process::Play();
  }

  return index;
}

}  // namespace CTRPluginFramework