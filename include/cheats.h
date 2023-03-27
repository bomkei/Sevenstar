#pragma once

#include "CTRPluginFramework.hpp"

#define write8(a, v) (*(u8*)(a) = (u32)v)
#define write16(a, v) (*(u16*)(a) = (u32)v)
#define write32(a, v) (*(u32*)(a) = (u32)v)

#define read32(a) (*(u32*)a)

#define writef(a, v) (*(float*)a = v)

inline bool is_in_range(u32 value, u32 lowerbound, u32 upperbound)
{
  return value > lowerbound && value < upperbound;
}

namespace CTRPluginFramework {

enum ItemID : u16 {
  ITEM_Banana = 0,
  ITEM_GreenShell = 1,
  ITEM_Mashroom = 3,
  ITEM_RedShell = 2,
  ITEM_BombOmb = 4,
  ITEM_Squid = 5,
  ITEM_BlueShell = 6,
  ITEM_TripleMashroom = 7,
  ITEM_Star = 8,
  ITEM_BulletBill = 9,
  ITEM_Thunder = 10,
  ITEM_GoldMashroom = 11,
  ITEM_FireFlower = 12,
  ITEM_SuperLeef = 13,
  ITEM_Lucky7 = 14,
};

//
// アイテム系
class ItemCodes {
public:
  static u16* get_item_pointer();

  static bool write_item(ItemID item);

  // ボム兵無限
  static void disable_bomb_limit(MenuEntry* entry);

  // ボム兵高速爆発
  static void fast_bomb_explosion(MenuEntry* entry);

  // ボム兵サイズ変更
  static void big_bomb(MenuEntry* entry);

  // 無限アイテム
  static void item_wheel(MenuEntry* entry);

  static MenuFolder* create_folder();
};

class Game {
public:
  static bool is_in_race();
};

}  // namespace CTRPluginFramework