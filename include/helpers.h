#pragma once

#include <string>
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework {

class PointerReader {
public:
  u32 offs;
  bool ok;

  PointerReader()
    : offs(0),
      ok(true)
  {
  }

  PointerReader& operator()()
  {
    this->ok = true;
    return *this;
  }

  PointerReader& reset()
  {
    this->ok = true;
    return *this;
  }

  PointerReader& read(u32 addr, u32 begin = 0x14000000,
                      u32 end = 0x18000000)
  {
    if (this->ok) {
      this->ok = Process::Read32(addr, this->offs) &&
                 (begin < this->offs && this->offs < end);
    }

    return *this;
  }

  PointerReader& add(u32 val)
  {
    return this->read(this->offs + val);
  }

  u32 get() const
  {
    return this->offs;
  }
};

}  // namespace CTRPluginFramework