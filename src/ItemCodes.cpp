#include "cheats.h"

namespace CTRPluginFramework {

ItemID* get_item_pointer()
{
  u32 offset;

  if (Game::is_in_race() && Process::Read32(0x14000074, offset) &&
      is_in_range(offset, 0x14000000, 0x18000000))
    if (Process::Read32(offset - 0x1B5C, offset) &&
        is_in_range(offset, 0x14000000, 0x18000000))
      if (Process::Read32(offset + 0x27AC, offset) &&
          is_in_range(offset, 0x14000000, 0x18000000))
        return (ItemID*)offset;

  return 0;
}

bool write_item(ItemID item)
{
  if (auto p = (u32)get_item_pointer(); p) {
    Process::Write32(p + 0x3c, -1);
    Process::Write32(p + 0xa8, 3);
    Process::Write32(p + 0xc8, item);
    Process::WriteFloat(p + 0xd8, 1.f);

    return true;
  }

  return false;
}

// ボム兵無限
void disable_bomb_limit(MenuEntry* entry)
{
  if (entry->WasJustActivated())
    Process::Write32(0x2d0714, 0xe3a0001e);
  else if (!entry->IsActivated())
    Process::Write32(0x2d0714, 0xe1520000);
}

// ボム兵高速爆発
void fast_bomb_explosion(MenuEntry* entry)
{
  if (entry->WasJustActivated())
    Process::Write32(0x665e58, 300.f);
  else if (!entry->IsActivated())
    Process::Write32(0x665e58, 50.f);
}

// ボム兵サイズ変更
void big_bomb(MenuEntry* entry)
{
}

// 無限アイテム
void item_wheel(MenuEntry* entry)
{
  static const std::pair<u32, ItemID> key_item_map[] = {
    {Key::ZL, ITEM_Thunder},
    {Key::ZR, ITEM_BlueShell},

    {Key::DPadUp, ITEM_Banana},
    {Key::DPadDown, ITEM_BombOmb},
    {Key::DPadLeft, ITEM_GreenShell},
    {Key::DPadRight, ITEM_RedShell},

    // Y
    {Key::Y | Key::DPadUp, ITEM_Squid},
    {Key::Y | Key::DPadDown, ITEM_Star},
    {Key::Y | Key::DPadLeft, ITEM_Lucky7},
    {Key::Y | Key::DPadRight, ITEM_FireFlower},

    // C-Stick
    {Key::CStickUp, ITEM_SuperLeef},
    {Key::CStickDown, ITEM_BulletBill},
    {Key::CStickLeft, ITEM_GoldMashroom},
    {Key::CStickRight, ITEM_TripleMashroom},

  };

  for (auto&& [key, item] : key_item_map) {
    if (Controller::IsKeysDown(key)) {
      write_item(item);
      break;
    }
  }
}

}  // namespace CTRPluginFramework