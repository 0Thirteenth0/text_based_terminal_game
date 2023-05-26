class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard, equipCategory, statName;
    std::map<std::string, float> curr_stat;
    int curr_h, curr_w, game_s;

    //displayer
    void characterDisplay();
    void displayStats();
    void displayEXP();
    void displayUI(int s);
    void inventoryMenu();
    void settingsMenu();

    //updater
    void updateGameMap(int);
    void updateInventoryM(int);
    void updateSettingM(int);
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
        gameBoard[i][window.width-33] = '#';
    }

    // experience progress bar
    displayEXP();
    // display character figure
    characterDisplay();
    // display player stats
    displayStats();
    //display options/interactable menus.
    displayUI(select);

    

    
    
    
}
void game::updateInventoryM(int select) {
    int padding = (window.width - 4) / 4, iter = 0, category = 0;
    if (window.height < 49 || window.width < 125)
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
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 + 20][i] = '#';
        for (int i = window.width/2 - equip.size()/2; i < window.width/2 - equip.size()/2 + equip.size(); i++)
            gameBoard[window.height/2 - 19][i] = equip[iter++];
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 - 18][i] = '#';
        for (int i = window.height/2 - 16; i < window.height/2 - 4; i+=2) {
            iter = 0;
            for(int j = padding+1; j < padding + 1 + equipCategory[category].size(); j++){
                // once equipments are added to the game: if(j ==padding+neck.size()) and sue for loop to add equipment Name and the closeing ']';
                gameBoard[i][j] = equipCategory[category][iter++];
            }
            category++;
            iter = equipCategory[category].size() - 1;
            for(int j = gameBoard[i].find('#', window.width/2) - 1; j > gameBoard[i].find('#', window.width/2) -  equipCategory[category].size() - 1; j--){
                // once equipments are added to the game: if(j ==padding+neck.size()) and sue for loop to add equipment Name and the closeing ']';
                gameBoard[i][j] = equipCategory[category][iter--];
            }
            category++;
        }
        iter = 0;
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 - 6][i] = '#';
        for (int i = window.width/2 - inven.size()/2; i < window.width/2 - inven.size()/2 + inven.size(); i++)
            gameBoard[window.height/2 - 5][i] = inven[iter++];
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 - 4][i] = '#';
    }
}
void game:: updateSettingM(int select) {
    int padding = (window.width - 4) / 4, iter = 0, category = 0;
    std::string Header = "Setting";
    if (window.height < 49 || window.width < 125)
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
        // top border
        for (int i = padding; i < window.width-padding-3; i++)
            gameBoard[window.height / 2 - 20][i] = '#';
        //side border
        for (int i = window.height / 2 - 19; i < window.height / 2 + 20; i++) {
            for (int j = padding; j < window.width - padding - 3; j++) {
                 if (j == padding || j == window.width - padding - 4)
                    gameBoard[i][j] = '#';
                else
                    gameBoard[i][j] = ' ';
            }
        }
        // bottom border
        for (int j = padding; j < window.width - padding - 3; j++)
            gameBoard[window.height / 2 + 20][j] = '#';
        iter = 0;
        // header 
        for (int i = padding*2 - Header.size()/2; i < padding*2 - Header.size()/2 + Header.size(); i++){
            gameBoard[window.height / 2 - 19][i] = Header[iter++];
        }
    }
}


void game::inventoryMenu() {
    updateGameMap(0);
    int select = 0;
    while (true)
    {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateGameMap(0);
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
    updateGameMap(0);
    int select = 0;
    while (true)
    {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateGameMap(0);
        char keyP = '\0';
        updateSettingM(select);
        for (const auto &i : gameBoard)
            std::cout << i << std::endl;
        keyP = '\0';
        if(kbhit())
            keyP = getchar();
        if(keyP == 27)
            break;
    }
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
    gameBoard[window.height - 3] = "#" + inv + set + std::string(window.width - inv.size() - set.size() - 2 + (s > 0 && s < 3 ? c.getBC(18).size() + c.cReset().size() -6 : -6 ), ' ') + "#" + (s == 3 ? c.getBC(18) + "[ ? ]" + c.cReset(): " [?] ") + "#";
}

void game::displayStats() {
    curr_stat = loadedPlayer.getStats();
    std::string AP = std::to_string(loadedPlayer.getAP()), tmp = "";
    for (int i = window.width - 18; i < window.width - 14; i++)
        gameBoard[loadedPlayer.character.size() + 4][i] = st[i - (window.width - 18)];
    for (int i = loadedPlayer.character.size() + 5, iter = 0; i < loadedPlayer.character.size() + 13; i+=2) {
        tmp = std::to_string(loadedPlayer.getStats()[statName[iter]]);
        tmp = tmp.substr(0, tmp.find('.') != -1 ? tmp.find('.') : tmp.size());
        for (int j = window.width - 31; j < window.width - 31 + statName[iter].size(); j++) 
            gameBoard[i][j] = statName[iter][j - (window.width - 31)];
        for (int j = window.width - 19; j > window.width - 19 - tmp.size(); j--)
            gameBoard[i][j] = tmp[j - (window.width - 19) + tmp.size()-1];
        iter++;
        tmp = std::to_string(loadedPlayer.getStats()[statName[iter]]);
        tmp = tmp.substr(0, tmp.find('.') != -1 ? tmp.find('.') : tmp.size());
        for (int j = window.width - 15 ; j <= window.width - 15 + statName[iter].size() - 1; j++)
            gameBoard[i][j] = statName[iter][j - (window.width - 15)];
        for (int j = window.width - 3; j > window.width - 3 - tmp.size(); j--)
            gameBoard[i][j] = tmp[j - (window.width - 3) + tmp.size()-1];   
        iter++;
        gameBoard[i][window.width - 17] = '|'; 
        if (iter < 7)
            gameBoard[i+1][window.width - 17] = '|';
    }
    for (int i = window.width - 31; i < window.width - 31 + ptAssign.size() ; i++)
        gameBoard[loadedPlayer.character.size() + 13][i] = ptAssign[i - (window.width - 31)];
    for (int i = window.width - 2; i >= window.width - 1 - AP.size(); i--)
        gameBoard[loadedPlayer.character.size() + 13][i - 1] = AP[i - (window.width - 1) + AP.size()];
    for (int i = window.width - 32; i < window.width - 1; i++)
        gameBoard[loadedPlayer.character.size() + 14][i] = '#';
}

void game::characterDisplay() {
    int traversal = 0;
    for (int i = 0; i < loadedPlayer.character.size() + 1; i++, traversal = 0) {
        for (int j = window.width - 32; j < window.width - 1; j++)
        {
            if (i == 0) {
                if (j >= window.width - 16 - loadedPlayer.getName().size()/2 && j < window.width - 16 - loadedPlayer.getName().size()/2 + loadedPlayer.getName().size())
                    gameBoard[i+3][j] = loadedPlayer.getName()[traversal++];
            } else if (i > 0 && j > window.width - 16 - loadedPlayer.character[i].size()/2 && j<=window.width - 16 - loadedPlayer.character[i].size()/2 + loadedPlayer.character[i].size()) {
                gameBoard[i+3][j] = loadedPlayer.character[i-1][traversal++];
            }
        }
    }
    for (int j = window.width - 32; j < window.width-1; j++)
        gameBoard[loadedPlayer.character.size()+3][j] = '#';
}

game::game(/* args */) {
    if (!loadedPlayer.s_StatAssigned && assignStat()) {
            loadedPlayer.s_StatAssigned  = true;     
            saveGame();
    }
    equipCategory.push_back("    Neckness []");
    equipCategory.push_back("[] Head        ");
    equipCategory.push_back("        Body []");
    equipCategory.push_back("[] Glove       ");
    equipCategory.push_back("       MainH []");
    equipCategory.push_back("[] SecondaryH  ");
    equipCategory.push_back("        Ring []");
    equipCategory.push_back("[] Ring        ");
    equipCategory.push_back("        Belt []");
    equipCategory.push_back("[] Shoe        ");
    statName.push_back(HP);
    statName.push_back(SPD);
    statName.push_back(ATT);
    statName.push_back(MATT);
    statName.push_back(CRITC);
    statName.push_back(CRITR);
    statName.push_back(DEF);
    statName.push_back(MDEF);
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
                    settingsMenu();
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
