class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard;
    int curr_h, curr_w;
public:
    game(/* args */);
    void updateG();
    ~game();
};



void printGB(const std::vector<std::string> &gameBoard) {
    while (!keyPressed[6])
    {
        std::cout << "\033[0;0H";
        for(auto i : gameBoard)
            std::cout << i << "\n";
    }
        
}

void toggleGameBoard(int curr_h, int curr_w) {
    while (window.height == curr_h && curr_w == window.width)
        window.update();
    keyPressed[6] = true;
}


void game::updateG() {
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
    
    
}

game::game(/* args */) {
    if (!loadedPlayer.s_StatAssigned && assignStat()){
            loadedPlayer.s_StatAssigned  = true;     
            saveGame();
    }
    curr_h = window.height, curr_w = window.width;
    updateG();
    int select = 0;
    while (true)
    {
        std::cout << "\033[0;0H";
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            updateG();
        for (const auto &i : gameBoard)
            std::cout << i << std::endl;
        
        // find a way to make the window reflect immediately to the change when the window is resized
        // Set the flag with true to break the loop.
        if (kbhit())
            select = getchar();
        
        if(select == 'h')
            break;
    }
    

}

game::~game(){}
