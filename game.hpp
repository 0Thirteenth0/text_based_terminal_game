class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard;
    winSize T_WinS;
    int curr_h, curr_w;
public:
    game(/* args */);
    void update();
    void printGB();
    ~game();
};

game::game(/* args */) {
    update();
    if (!loadedPlayer.s_StatAssigned && assignStat()){
            loadedPlayer.s_StatAssigned  = true;     
            saveGame();
    }

    printGB();
}

game::~game(){}

void game::printGB() {
    for(auto i : gameBoard)
        std::cout << i << "\n";
}

void game::update() {
    T_WinS.update();
    curr_h = T_WinS.height;
    curr_w = T_WinS.width;
    gameBoard.resize(T_WinS.height - 2);
    for(int i = 0; i < gameBoard.size(); i++){
        if(i == 0 || i == gameBoard.size() - 1)
            gameBoard[i] = std::string(T_WinS.width, '#');
        else
            gameBoard[i] = "#" + std::string(T_WinS.width - 2,' ') + "#";
    }
    
}