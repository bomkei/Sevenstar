#include "cheats.h"

namespace CTRPluginFramework {

namespace {
u32 offset = 0, offset2 = 0, data32 = 0, cmp32 = 0;
u16 data16 = 0, cmp16 = 0;
u8 data8 = 0, cmp8 = 0;
float dataf = 0;
}  // namespace

void DropItem(MenuEntry* entry)
{
  if (Controller::IsKeysDown(Start + DPadUp)) {
    Process::Write8(offset + 0x006BEA00, 0x01);
  }

  if (Controller::IsKeysDown(Start + DPadDown)) {
    Process::Write8(offset + 0x006BEA00, 0x00);
  }

  offset = 0;
  offset = 0x10000000;

  Process::Read32(offset + 0x040005AC, data32);

  offset = data32;
  Process::Read32(offset + 0x00000650, data32);
  offset = data32;
  offset += 0xFFFF0000;
  if (Process::Read16(offset + 0x0000F268, cmp16) &&
      (cmp16 & 0xFFFF) != 0x0000) {
    Process::Write16(offset + 0x0000F268, 0x0000);
  }
  if (Process::Read16(offset + 0x0000F26C, cmp16) &&
      (cmp16 & 0xFFFF) != 0x0000) {
    Process::Write16(offset + 0x0000F26C, 0x0000);
  }
  data32 = 0;
  if (Process::Read16(offset + 0x006BEA00, cmp16) &&
      (cmp16 & 0xFFFF) == 0x0001) {
    Process::Write8(offset + 0x002D4458, 0x00);
    offset = 0x10000000;
    if (Process::Read16(offset + 0x054805E0, cmp16) &&
        (cmp16 & 0xFFFF) < 0x0001) {
      Process::Read32(offset + 0x040005AC, data32);
      offset = data32;
      Process::Read32(offset + 0x00000650, data32);
      offset = data32;
      offset += 0xFFFF0000;
      Process::Write8(offset + 0x0000EE9A, 0x00);
      Process::Write16(offset + 0x0000F25C, 0x0000);
      Process::Write16(offset + 0x000101F6, 0x0000);
      Process::Write16(offset + 0x0000F268, 0xFFFF);
      offset = 0x10000000;
      Process::Read32(offset + 0x040005AC, data32);
      offset = data32;
      Process::Read32(offset + 0x00000650, data32);
      offset = data32;
      Process::Read32(offset + 0xFFFFE28C, data32);
      offset = 0x00000000;
      Process::Read32(offset + 0x0065DA44, data32);
      offset = data32;
      Process::Read32(offset + 0x00002124, data32);
      offset = data32;
      Process::Write32(offset + 0x00000024, data32);
      offset += 0x4;
      offset = 0x10000000;
      Process::Read32(offset + 0x040005AC, data32);
      offset = data32;
      Process::Read32(offset + 0x00000650, data32);
      offset = data32;
      Process::Read32(offset + 0xFFFFE290, data32);
      offset = 0x00000000;
      Process::Read32(offset + 0x0065DA44, data32);
      offset = data32;
      Process::Read32(offset + 0x00002124, data32);
      offset = data32;
      Process::Write32(offset + 0x00000028, data32);
      offset += 0x4;
      offset = 0x10000000;
      Process::Read32(offset + 0x040005AC, data32);
      offset = data32;
      Process::Read32(offset + 0x00000650, data32);
      offset = data32;
      Process::Read32(offset + 0xFFFFE294, data32);
      offset = 0x00000000;
      Process::Read32(offset + 0x0065DA44, data32);
      offset = data32;
      Process::Read32(offset + 0x00002124, data32);
      offset = data32;
      Process::Write32(offset + 0x0000002C, data32);
      offset += 0x4;
    }
  }
}
}  // namespace CTRPluginFramework