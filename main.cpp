/*
                    # ############################################################# #
                    # Game Idea:                                                    #
                    # 1. Turn-based                                                 #
                    # 2. player have hp, armor, attack, coins, and crit-chance      #
                    #   I. equipments maybe added in the later version.             #
                    # 3. player have choice of path to take on the map.             #
                    #   I. "?" represnt random events.                              #
                    #   II. "X" represent enermy encounter.                         #
                    #   III. "R" represents resting area (restore hp).              #
                    #   IV. "$" represent shop. (purchase stat points).             #
                    # 4. control are simply just number keys:                       #
                    #   I. May include keys for checking stats.                     #
                    #   II. If equipment is added, need a key for inventory access. #
                    #   III. Ability to save game data.(Shortcut key to save data)  #
                    #   IV. May add in Text-log functionality.                      #
                    # ############################################################# #
*/
#ifndef ISRM
#define ISRM
#include <iostream>
#endif

#ifndef F_STREAM
#define F_STREAM
#include <fstream>
#endif

#ifndef IMANIP
#define IMANIP
#include <iomanip>
#endif

#ifndef UNI
#define UNI
#include <unistd.h>
#endif

namespace fs = std::filesystem;
const std::string st = "STAT", equip = "EQUIPMENTS", inven = "INVENTORY", ptAssign = "Stat Points:";

#define B_HP    "b_hp"
#define M_HP    "m_hp"
#define HP      "hp"
#define B_ATT   "b_att"
#define ATT     "att"
#define B_MATT  "b_mAtt"
#define MATT    "mAtt"
#define B_CRITC "b_critC"
#define CRITC   "critC"
#define B_CRITR "b_critR"
#define CRITR   "critR"
#define B_DEF   "b_def"
#define DEF     "def"
#define B_MDEF  "b_mDef"
#define MDEF    "mDef"
#define B_SPD   "b_spd"
#define SPD     "spd"


#include <sstream>
#include <map>
#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <filesystem>
#include <atomic>
#include <thread>
#include <mutex>
#include <fcntl.h>
#include <condition_variable>
#include "utility.hpp"

void cursorSet(int y, int x) {
    std::string c = "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
    std::cout << c;
}


// MISC lib
#include "color.hpp"
#include "winSize.hpp"

std::atomic_bool keyPressed[6] = {false}; 
static int choice = 0;
color c;
winSize window;
// ### Entity lib
#include "./entity/entity.hpp"

// ### game window lib
#include "gameMenu.hpp"
#include "game.hpp"



int main(int argv, char** argc) {
    system("clear");
    BufferToggle t;
    t.off();
    
    game start;

    t.on();
    return 0;
}