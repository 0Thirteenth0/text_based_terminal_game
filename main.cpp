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
#include <condition_variable>

void cursorSet(int y, int x) {
    std::string c = "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
    std::cout << c;
}

// MISC lib
#include "color.hpp"
#include "winSize.hpp"

// ### Entity lib
#include "./entity/entity.hpp"

// ### game window lib
#include "gameMenu.hpp"
#include "game.hpp"



class BufferToggle
{
    private:
        struct termios t;

    public:
        /*
         * Disables buffered input
         */

        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }


        /*
         * Enables buffered input
         */

        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
};


int main(int argv, char** argc) {
    system("clear");
    BufferToggle t;
    std::vector<std::string> save_games;
    t.off();
    // for (const auto & entry : fs::directory_iterator("savegame"))
    //     save_games.push_back(entry.path());
    // for (const auto & i : save_games)
    //     std::cout << i.substr(9) << "\t";
    // std::cout << "\n";
    game start;


    
    t.on();
}