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

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IN-PROGRESS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

## GameMenu:
  NAV for game menu

    - Num key 1-3 to pick options
    - '<' or ',' to navigate up
    - '>' or '.' to navigate down
![ezgif com-gif-maker-2](https://user-images.githubusercontent.com/95335912/212165285-c81e1d45-f849-44f1-839b-9bcec65a011d.gif)
 
    1. New Game - creates a save file in .txt to the ./savegame folder.
    2. Load Game - loads progress from ./savegame folder.
    3. Setting - supposely can change the style/color of game.
    4. Exit - exits program with exit(EXIT_SUCCESS);
#### New Game:
    - Prompts to enter a new save game name to create new save in ./savegame folder.
    - Name must be between 1 and 14 length characters.
    - Name must not be already existing in the ./savegame folder.
    - Name your character
![ezgif com-gif-maker](https://user-images.githubusercontent.com/95335912/212164278-edef7502-6bbd-4960-aad5-6275f26721a6.gif)


#### Load Game Menu:
    - '<' or ',' and '>' or '.' to navigate through the list of saved progress.
    - Loads progress from save file in ./savegame folder.
      * !!- Currently only loads player data. -!!
    - Things to Optimize:
      * Order of savefile being listed is not in order, need a way to sort it by date.
![ezgif com-gif-maker](https://user-images.githubusercontent.com/95335912/211419640-01d30881-b90a-49f6-b1a7-c2670d0ee67b.gif)

#### Settings:
    - This functionality is not available as of now.
      * The settings that I'm thinking to manipulate is the color/theme of the game.
![ezgif com-gif-maker](https://user-images.githubusercontent.com/95335912/211701350-35acec43-d8dd-4dd1-bb21-65e0048ce80b.gif)

#### Attribute Assign:
    - Assigns attribute points from leveling to the player.
      * Stats points weight still need to be balanced.
        ; Right now for testing critC is +1 for every attribute points to balance starting AP
          will be adjusted to 0.01 and every attribute points added to critC will +0.01 to
          base critC.
![ezgif com-gif-maker-4](https://user-images.githubusercontent.com/95335912/212501625-7e162433-0eb3-46c6-99b8-14cd07829d6f.gif)


# In-Game:
 ### Game Design and Concept:
  #### Planning:
    - Design:
      1. Frame of the game will be with "#", empty backgrounds will be ' '.
      2. Might use ansi escape code to manipulate the row and colum of to write on the
        terminal inorder to better lower the refresh frame.
        - "\033[#;#H" or "\033[#;#f" might not work as expected, it moves the cursor 
          to the desired position however also clears everything after it.
      3. need a better way to edit the screen output.
        - save the output into a 2d dynamic array or vector and edit the output that 
          way (mostlikely vector);
          1. ability to add little decoration ascii art into the output.
          2. ability to put entities onto the output.
            * entities/paths '$'=Shop 'player'=Player 'X'=EnermyEncounter 'R'=RestArea
              '?'=RandomEvent
      4. UI, such as:
        - keybind hints
        - character status and inventory menu and UI icon. Example:
<img width="823" alt="Screenshot 2023-01-09 at 5 31 21 PM" src="https://user-images.githubusercontent.com/95335912/211441598-4d4b96d1-28b1-4c5a-bd24-9e7bf951ea4d.png">

        - Keybind to select path to take will simply be ',' or '<' and '>' or '.'
          or numkey 1/2/3/4 to select the path.
        - keybind to access UI stuff can be toggled by pressing a key; '/' or 'i'
          * navigating using ',' , and '.' keys
      5. Battle Screen with enermy encounter with 'X' path (will need another symbol to
         represent boss encounter).
      6. Shop screen with '$' path
      7. Random encounter screen with '?' path.
      8. Rest screen with 'R' path.
        
    - Concept:
      1. Level based
        - passing any station will result in enermy encounter difficulty to increase
          by a small amount:
          (possibly: exp += 2^(level station passed/2) + level station passed).
        - defeating boss encounter will increase difficulty by extra amount 
        (possibly: exp += 2^(level station passed/2) + level station passed * 2).
      2. Exp Reward
        - defeating a enermy encounter will grants 
          (possibly: exp += 2^(enermyLevel / 2) + level station passed)
      3. Exp needed will increase by:
        - previous exp needed = previousEXPneed * 1.5
      4. May add in grinding levels, help player to pass current level station.
      5. if player dies in any event, the game will not be over:
        - penalty:
          * loss of experience and money?
      6. 
        


