
# text_based_terminal_game

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

controls: 

  NAV for game menu
  
    - num key 1-3 to pick options
    - '<' or ',' to navigate up
    - '>' or '.' to navigate down
 Content of Gamemenu:
    i. New Game - creates a save file in .txt to the ./savegame folder
      - then enters the game (in progress)
    ii. Load Game - loads progress from ./savegame folder (in progress)
    iii. setting - supposely can change the style/color of game.
