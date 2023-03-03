class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard;
    int curr_h, curr_w, game_s;
    void characterDisplay();
    void displayStats();
    void displayEXP();
    void displayUI(int s);
    void inventoryMenu();
    void settingsMenu();
    void updateGameMap(int);
    void updateInventoryM(int);
public:
    game(/* args */);
    

    
    ~game();
};



void game::updateGameMap(int select) {
    int traversal = 0;
    window.update();
    curr_h = window.height;
    curr_w = window.width;
    gameBoard.clear();
    gameBoard.resize(window.height - 1);
    for(int i = 0; i < curr_h - 1; i++){
        if(i == 0 || i == curr_h - 2)
            gameBoard[i] = std::string(curr_w, '#');
        else
            gameBoard[i] = "#" + std::string(curr_w - 2,' ') + "#";
    }
    // experience progress bar
    displayEXP();
    // display character figure
    characterDisplay();
    //display options/interactable menus.
    displayUI(select);

    

    
    
    
}
void game::updateInventoryM(int select) {
    int padding = (window.width - 4) / 4, iter = 0;
    if (window.height < 49 || window.width < 100)
    {
        std::string message = "Please Resize";
        
        for (int i = 0; i < window.height-1; i++)
        {
            if (i == 0 || i == window.height - 2)
                gameBoard[i] = std::string(window.width, '#');
            else
                gameBoard[i] = "#" + std::string(window.width - 2, ' ') + "#";
        }
        for (int i = window.width/2 - message.size()/2; i < window.width/2 - message.size()/2 + message.size(); i++)
            gameBoard[window.height/2][i] = message[iter++];
    }else{
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 - 20][i] = '#';
        for (int i = window.height / 2 - 19; i < window.height / 2 + 20; i++) {
            for (int j = padding; j < window.width - padding - 3; j++) {
                if (j == padding || j == window.width - padding - 4)
                    gameBoard[i][j] = '#';
                else
                    gameBoard[i][j] = ' ';
            }
        }
        iter = 0;
        std::string equip = "Equipments";
        for (int i = window.width/2 - equip.size()/2; i < window.width/2 - equip.size()/2 + equip.size(); i++)
            gameBoard[window.height/2 - 19][i] = equip[iter++];
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 + 20][i] = '#';
    }

    
    
    
}

void game::inventoryMenu() {
    updateGameMap(0);
        
    while (true)
    {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateGameMap(0);
        int select = 0;
        char keyP = '\0';
        updateInventoryM(select);
        for (const auto &i : gameBoard)
            std::cout << i << std::endl;
        keyP = '\0';
        if(kbhit())
            keyP = getchar();
        if(keyP == 27)
            break;
    }
    


    
    
    
}

void game::settingsMenu() {

}

void game::displayEXP(){
    int expPercentage = (window.width - 2)*(double(loadedPlayer.getExp()) / loadedPlayer.getExpNeed());
    int numOfSpaces = (expPercentage+1) > window.width / 2 - std::to_string(loadedPlayer.getExp()).size() - 1 ? window.width / 2 - std::to_string(loadedPlayer.getExp()).size() - 1 : expPercentage; 
    gameBoard[1].clear();
    gameBoard[1] += "#";
    if (expPercentage > 0)
        gameBoard[1] += c.getBC(18) + std::string(numOfSpaces, ' ');
    gameBoard[1] += (numOfSpaces == expPercentage ? c.cReset() : "") + std::string((window.width / 2 - std::to_string(loadedPlayer.getExp()).size() - 1) - numOfSpaces, ' ');
    numOfSpaces = window.width / 2 - std::to_string(loadedPlayer.getExp()).size() - 1;
    for (int i = 0; i < std::to_string(loadedPlayer.getExp()).size(); i++, numOfSpaces++) {
        if (numOfSpaces == expPercentage && expPercentage)
            gameBoard[1] += c.cReset();
        gameBoard[1] += std::to_string(loadedPlayer.getExp())[i];
    }
    gameBoard[1] += (numOfSpaces++ == expPercentage ? c.cReset() : "") + " ";
    gameBoard[1] += (numOfSpaces++ == expPercentage ? c.cReset() : "") + "/";
    gameBoard[1] += (numOfSpaces++ == expPercentage ? c.cReset() : "") + " ";
    for (int i = 0; i < std::to_string(loadedPlayer.getExpNeed()).size(); i++, numOfSpaces++) {
        if (numOfSpaces == expPercentage && expPercentage)
            gameBoard[1] += c.cReset();
        gameBoard[1] += std::to_string(loadedPlayer.getExpNeed())[i];
    }
    if (numOfSpaces < expPercentage){
        gameBoard[1] += std::string(window.width / 2 + std::to_string(loadedPlayer.getExpNeed()).size() + 1 + expPercentage - numOfSpaces < window.width - 2 ? expPercentage - numOfSpaces : window.width - window.width / 2 - std::to_string(loadedPlayer.getExpNeed()).size() - 4, ' ') + c.cReset();
        numOfSpaces = expPercentage;
    }   
    if (window.width - 2 > numOfSpaces)
        gameBoard[1] += std::string(window.width - 2 - numOfSpaces, ' ');
    gameBoard[1] += "#";
    if (expPercentage >= window.width - 2)
        gameBoard[1] += c.cReset();
    gameBoard[2] = std::string(window.width, '#');
    
}
void game::displayUI(int s){
    std::string inv = s == 1 ? " "+ c.getBC(18) + "[ Inventory ]" + c.cReset()+ " " : "  [Inventory]  ";
    std::string set = s == 2 ? " "+ c.getBC(18) + "[ setting ]"+ c.cReset() + " ":"  [setting]  ";
    gameBoard[window.height - 4] = std::string(window.width, '#');
    gameBoard[window.height - 3] = "#" + inv + set + std::string(window.width - inv.size() - set.size() - 2 + (s > 0 && s < 3 ? c.getBC(18).size() + c.cReset().size() -4 : s == 3 ? -6 : -4), ' ') + "#" + (s == 3 ? c.getBC(18) + "[ ? ]" + c.cReset(): "[?]") + "#";

}

void game::displayStats() {
    
}

void game::characterDisplay() {
    int traversal = 0;
    for (int i = 0; i < loadedPlayer.character.size() + 1; i++) {
        for (int j = window.width - loadedPlayer.character[0].size() - 1; j < window.width - 1; j++)
        {
            if(j == window.width - loadedPlayer.character[0].size() - 1){
                gameBoard[i+3][j] = '#';
            } else if (i == 0) {
                if (j >= window.width - loadedPlayer.character[0].size()/2 - loadedPlayer.getName().size()/2 && j < window.width - loadedPlayer.character[0].size()/2 - loadedPlayer.getName().size()/2 + loadedPlayer.getName().size())
                    gameBoard[i+3][j] = loadedPlayer.getName()[traversal++];
            } else {
                gameBoard[i+3][j] = loadedPlayer.character[i-1][j - (window.width - loadedPlayer.character[i].size())];
            }
        }
    }
    for (int j = window.width - loadedPlayer.character[0].size() - 1; j < window.width-1; j++)
        gameBoard[loadedPlayer.character.size()+3][j] = '#';
}

game::game(/* args */) {
    if (!loadedPlayer.s_StatAssigned && assignStat()) {
            loadedPlayer.s_StatAssigned  = true;     
            saveGame();
    }
    curr_h = window.height, curr_w = window.width, game_s = 0;
    updateGameMap(game_s);
    char keyP = '\0';
    while (true) {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateGameMap(game_s);
        for (const auto &i : gameBoard)
            std::cout << i << std::endl;
        keyP = '\0';
        if (kbhit())
            keyP = getchar();
        if (keyP == '.' || keyP == '>') {
            if (++game_s > 3)
                game_s = 1;
            displayUI(game_s);
        }
        if (keyP == ',' || keyP == '<') {
            if (--game_s < 1) 
                game_s = 3;
            displayUI(game_s);
        }

        if (keyP == '\n') {
            switch (game_s) {
                case 1:
                    inventoryMenu();
                    updateGameMap(game_s);
                    break;
                case  2:
                    
                    updateGameMap(game_s);
                    break;
                default:
                    break;
            }
        }
        
        if(keyP == 'p')
            break;
    }
}

game::~game(){}
