#include <3ds.h>
#include <vector>
#include "csvc.h"
#include "cheats.h"

namespace CTRPluginFramework {

void PatchProcess(FwkSettings& settings)
{
}

void InitMenu(PluginMenu& menu)
{
  menu += ItemCodes::create_folder();
}

int main(void)
{
  PluginMenu menu{"Sevenstar", 1, 0, 0, ""};

  menu.ShowWelcomeMessage(false);
  menu.SynchronizeWithFrame(true);

  InitMenu(menu);

  OSD::Notify("good morning :)");

  return menu.Run();
}

}  // namespace CTRPluginFramework
