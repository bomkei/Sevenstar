#include <3ds.h>
#include <vector>
#include "csvc.h"
#include "cheats.cpp"

namespace CTRPluginFramework {

void InitMenu(PluginMenu& menu)
{
  menu += new MenuFolder(
    "Kart Codes",
    {

      new MenuEntry("Invincibility", invincible,
                    "You will be invincible. You will also appear blinking on "
                    "other people's screens online."),

      new MenuEntry(
        "Aimbot", aimbot,
        "Your aim will be locked onto a specific player. Press D-Pad "
        "Up to increase player, and D-Pad Down to reset it."),
      new MenuEntry(
        "Always Star Power", alwaysStarPower,
        "You will always have star effects, such as invincibility and color."),

      new MenuEntry("Always Black Kart", alwaysBlackKart,
                    "Your kart will awlays be black as if you got bloopered."),

      new MenuEntry("Always Shocked", alwaysShocked,
                    "Your kart will always be small as if you got shocked."),
      new MenuEntry(
        "Always Crushed", alwaysCrushed,
        "Your kart will always be flat as if you got crushed. This is only "
        "visible "
        "on opponents screens online. On your screen, you'll appear normally."),
      new MenuEntry(
        "Trick Anywhere", trickAnywhere,
        "You will be able to perform a trick anywhere by pressing R."),
      new MenuEntry(
        "Instant MiniTurbo", instantMT,
        "You will instantly get red and blue MiniTurbos when drifting."),

      new MenuEntry("Huge Bunnyhop", hugeBunnyhop,
                    "You will jump very high when hopping before a drift."),
      new MenuEntry("Size Changer", sizeChanger,
                    "Your kart will constantly increase and decrease in size. "
                    "Use D-Pad Left "
                    "and D-Pad Right to change the speed at which your kart "
                    "will change size. "
                    "This code can cause problems sometimes.")});

  menu += new MenuFolder(
    "Speed & Movement Codes",
    {

      new MenuEntry("200cc", TwoHundredCC,
                    "You will go 200cc speeds. Restart the race after applying "
                    "the code for the effect to take place."),

      new MenuEntry("500cc", FiveHundredCC,
                    "You will go 500cc speeds. Restart the race after applying "
                    "the code for the effect to take place."),
      new MenuEntry("Instant Acceleration", instantAcceleration,
                    "Your kart will instantly accelerate to the "
                    "maximum speed when pressing A."),

      new MenuEntry(
        "Instant Backwards Acceleration", instantBackAcceleration,
        "Your kart will instantly accelerate to it's maximum reverse "
        "speed when pressing B."),
      new MenuEntry(
        "Instant Stop", instantStop,
        "Your kart will instantly come to a complete stop when pressing A+B."),
      new MenuEntry(
        "Fast Reverse Speeds", fastReverse,
        "You will reverse at higher speeds than before when holding B."),
      new MenuEntry("Inside Drifing Kart", insideDrift,
                    "Your kart will drift inwards, like certain bikes did in "
                    "Mario Kart Wii."),
      new MenuEntry(
        "Stalking Hack", stalking,
        "-Y + Right = Increase Player\n-Y + Left = Decrease Player\n-Y + Up = "
        "Stalk the player until code is disabled\n-Hold Y to stalk the player "
        "temporarily, release Y to stop stalking\n-Y + Down = Disable Code"),

      new MenuEntry("Touch Screen Teleporter", TouchCode,
                    "Touch the bottom screen or drag your stylus across it to "
                    "warp your kart to that position on the map!"),

      new MenuEntry("Moonjump", moonjump,
                    "-Start + R = Enable\n\nThis code will let you fly high."),
      new MenuEntry(
        "Drive Anywhere", driveAnywhere,
        "-Start = Disable\n-Select = Enable\n-Select + Up = Go Up\n-Select + "
        "Down "
        "= Go Down\n\nThis code is a remake of Supastarrio's code for MKDS."),
      new MenuEntry("Save Slot Teleporter", saveSlotTeleporter,
                    "-Start + X = Save Current Position\n-Start + Y = Load "
                    "Saved Position")});

  //
  // Item Codes
  menu += new MenuFolder(
    "Item Codes",
    {new MenuEntry("Item Wheel", itemWheel,
                   "-X = Bullet\n-Y = Tanooki\n-Start = Blue Shell\n-Select = "
                   "Lightning\n-D-Pad Left = Lucky 7\n-D-Pad Right = Red "
                   "Shell\n-D-Pad Up = Green Shell\n-D-Pad Down = Bob-Omb"),
     new MenuEntry(
       "Always Have Certain Item", nullptr, SetItem,
       "You will be able to choose the item you want when exiting the menu."),

     new MenuEntry("Cycle Completely Random Item", randomItems,
                   "You will be constantly given a random item."),
     new MenuEntry(
       "Truly Random Items", trulyRandomItems,
       "Items will be completely random, regardless of your position. The "
       "bottom "
       "screen item icon will tell you the item you were supposed to recieve, "
       "while the top screen item icon will tell you the purely random item "
       "you "
       "recieved."),

     new MenuEntry("Drop Mushrooms", dropMushrooms,
                   "This code replaces green shells with droppable mushrooms. "
                   "Throw a 'green shell' to drop a mushroom."),
     new MenuEntry("Fast Blue Shell", fastBlueShell,
                   "Blue shells will go very fast."),

     new MenuEntry("Stopped Blue Shell", stoppedBlueShell,
                   "Blue shells will not move after being thrown."),
     new MenuEntry("Fast Green Shell", fastGreenShell,
                   "Green shells will go very fast."),

     new MenuEntry("Stopped Green Shell", stoppedGreenShell,
                   "Green shells will not move after being thrown."),

     new MenuEntry(
       "Control Bullet", bulletControl,
       "You will be able to control your bullets.\n-Start + Right = "
       "Enable\n-Start + Left = Disable"),

     new MenuEntry("Bullet Speed Modifier", bulletSpeed,
                   "-X = Very Fast\n-B = Stopped\n-A = Normal Speed"),
     new MenuEntry(
       "Blue Shell Ride", blueShellRide,
       "-D-Pad Left = Enable\nYou will warp to a blue shell and ride it."),

     new MenuEntry("Disable Star Music", disableStarMusic,
                   "The star music won't play when you're in a star.")});

  // Cource Codes
  menu += new MenuFolder(
    "Course Codes",
    {
      new MenuEntry("CPU Brawl", cpuBrawl,
                    "The CPU will on top of each other, fighting."),

      new MenuEntry("Max Timer", maxTimer,
                    "The timer will freeze at 4:59.9xx."),
      new MenuEntry("Water Everywhere", waterEverywhere,
                    "You will always be underwater."),
    });

  //
  // Menu Codes
  menu += new MenuFolder(
    "Menu & Other Codes",
    {new MenuEntry("No Countdown", noCountdown,
                   "You will be able to drive when the "
                   "countdown normally would be happening."),
     new MenuEntry(
       "Speedometer", spedometer,
       "You will be able to see your current speed in your preferred unit."),
     new MenuEntry(
       "Mii Dumper", nullptr, miiDumper,
       "This code can dump any player's Mii from an online match. Follow the "
       "instructions on screen after enabling the code in an online lobby. If "
       "the "
       "room is not fully populated, certain buttons may be blank or contain "
       "previous player's names. You can dump previous players with no problem "
       "even if they're not in the room."),
     new MenuEntry("Disable First Person View", disableFirstPersonView,
                   "You will not be able to activate first "
                   "person view by pressing Up on the D-Pad."),

     new MenuEntry("No Disconnect", NoDC,
                   "You will not get disconnected unless the cause of the "
                   "disconnection is an actual network problem."),
     new MenuEntry("Fast Game/Anti-Matrix", fastGame,
                   "The game will move at a very fast speed. "
                   "Unstable, use at your own risk!"),
     new MenuEntry(
       "Live Time Trial Ghost Replay", timeTrialGhost,
       "This code will let you view any ghost. Please follow these steps:\n1. "
       "Activate this code and then enter the time trial with the ghost you "
       "want "
       "to view.\n2. Your kart will be out of bounds. Restart the race.\n3. "
       "Done! "
       "The code should be working."),

     new MenuEntry("VR Extender", vrExtender,
                   "-Start = 999999\n-Select = 420000\n-D-Pad Down = 0\n-D-Pad "
                   "Up = 696969\n-D-Pad Right = 666666\n-D-Pad Left = 777777"),

     new MenuEntry(
       "Set Custom VR", nullptr, SetVR,
       "A keyboard will come up when you exit the menu and you will "
       "be allowed to enter your desired VR, between 0 and 999999 "
       "(Be sure to enter values in hexadecimal)"),

     new MenuEntry("Random VR", randomVR,
                   "A random VR value between 1 and 999999 will be generated."),
     new MenuEntry(
       "Unlock Everything", unlockEverything,
       "Everything will be unlocked. After enabling, save the game by "
       "completing "
       "a time trial or something, exit the game, and open it again. At this "
       "point everything should be permanently unlocked.")});

  //
  // Custom Game Modes
  menu += new MenuFolder(
    "Custom Game Modes",
    {new MenuEntry("Elimination Mode", eliminationMode,
                   "Every 30 seconds, the player in last place will be "
                   "eliminated. The last "
                   "player standing wins! This mode works best in rooms with "
                   "more players."),
     new MenuEntry(
       "Countdown Mode", CountdownMode,
       "You will have 2 minutes to race. Every time you hit a player with an "
       "item, your time will increase by 3 seconds. You will need to "
       "strategically gain more time while still being towards the front of "
       "the "
       "pack. The player in first place when everyone's time runs out wins!"),

     new MenuEntry("Drivable 200cc", TwoHundredCCStable,
                   "This version of 200cc has brake drifting by pressing B "
                   "during drifts (also works in boosts and while in the air), "
                   "and drifting at lower speeds and in off road. Items will "
                   "also travel at speeds proprtional to the CC."),

     new MenuEntry("Drivable 500cc", FiveHundredCCStable,
                   "This version of 500cc has brake drifting by pressing B "
                   "during drifts (also works in boosts and while in the air), "
                   "and drifting at lower speeds and in off road. Items will "
                   "also travel at speeds proprtional to the CC.")});

  menu += new MenuFolder(
    "Region & Flag Codes", "",
    {new MenuEntry(
       "Set Custom Flag", nullptr, SetFlag,
       "A keyboard will come up when you exit the menu and you will "
       "be allowed to enter your desired flag ID (in hexadecimal). "
       "You can get these from the MK7 NTR Plugin GBAtemp thread."),
     new MenuEntry(
       "Set Custom Globe Coordinates", nullptr, SetCoordinates,
       "A keyboard will come up when you exit the menu and you will "
       "be allowed to enter your desired coordinates. You can get "
       "these from the MK7 NTR Plugin GBAtemp thread.")});
}

int main(void)
{
  PluginMenu menu{"DarkFlare's Online MK7 Plugin", 3, 8, 4,
                  "This is a plugin developed by DarkFlare that contains many "
                  "popular MK7 hacks. Please be sure to read all of the notes "
                  "for instructions on how to use a certain code. If there is "
                  "a problem, report it on the official GBAtemp thread."};

  menu.SynchronizeWithFrame(true);

  InitMenu(menu);

  return menu.Run();
}

void PatchProcess(FwkSettings& settings)
{
}

}  // namespace CTRPluginFramework
