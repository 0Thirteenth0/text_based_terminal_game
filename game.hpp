class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard;
    int curr_h, curr_w;
    void characterDisplay();
    void displayStats();
    void displayEXP();
    void displayUI();
public:
    game(/* args */);
    void updateG();
    
    ~game();
};




void game::updateG() {
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
    // experience progress ui
    displayEXP();
    characterDisplay();
    

    
    
    
    
    
    
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
void game::displayUI(){

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
    curr_h = window.height, curr_w = window.width;
    updateG();
    keyP = '\0';
    int select = 0;
    while (true) {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateG();
        for (const auto &i : gameBoard)
            std::cout << i << std::endl;
        if (kbhit())
            keyP = getchar();
        if(keyP == 'h')
            break;
    }
}

game::~game(){}
