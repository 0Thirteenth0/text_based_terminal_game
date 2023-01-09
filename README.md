# text_based_terminal_game

      # run with: g++ main.cpp -std=c++17 -pthread && ./a.out

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
                    
CURRENTLY ONLY GAME MENU IS BEING WORKED ON. (INPROGRESS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>) 

## GameMenu:

  NAV for game menu
  
    - num key 1-3 to pick options
    - '<' or ',' to navigate up
    - '>' or '.' to navigate down
![ezgif com-gif-maker-2](https://user-images.githubusercontent.com/95335912/211420343-eb76a431-1018-4cad-84dd-0c756c954e01.gif)
    
 Content of Gamemenu:
 
    i. New Game - creates a save file in .txt to the ./savegame folder.
    ii. Load Game - loads progress from ./savegame folder.
      - '<' or ',' and '>' or '.' to navigate through the list of saved progress
    iii. setting - supposely can change the style/color of game.

 ![ezgif com-gif-maker](https://user-images.githubusercontent.com/95335912/211419640-01d30881-b90a-49f6-b1a7-c2670d0ee67b.gif)


