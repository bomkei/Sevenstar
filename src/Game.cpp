#include "CTRPluginFramework.hpp"
#include "Unicode.h"
#include "csvc.h"
#include "3ds.h"
#include <math.h>
#include <vector>
#include "helpers.h"
#include "cheats.h"

namespace CTRPluginFramework {

bool Game::is_in_race()
{
  u32 offset;

  if (Process::Read32(0x14000084, offset) &&
      is_in_range(offset, 0x14000000, 0x18000000))
    if (Process::Read32(offset + 0x316C, offset) &&
        is_in_range(offset, 0x14000000, 0x18000000))
      return Process::Read32(offset + 0x118, offset) &&
             (offset & 0xFF);

  return 0;
}

}  // namespace CTRPluginFramework