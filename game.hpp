class game : public gameMenu
{
private:
    std::vector<std::string> gameBoard;
    int curr_h, curr_w;
public:
    game(/* args */);
    void update();
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
void getInput() {
    
}


game::game(/* args */) {
    if (!loadedPlayer.s_StatAssigned && assignStat()){
            loadedPlayer.s_StatAssigned  = true;     
            saveGame();
    }
    curr_h = window.height, curr_w = window.width;
    update();
    int select = 0;
    while (true)
    {
        window.update();
        if (window.height != curr_h || window.width != curr_w)
            update();
        std::thread lockf(printGB, gameBoard); 
        std::thread checkResize(toggleGameBoard, curr_h, curr_w);
        // find a way to make the window reflect immediately to the change when the window is resized
        select = getch();
        // Set the flag with true to break the loop.
        keyPressed[6] = true;
        lockf.join();

        keyPressed[6] = false;
    }
    

}

game::~game(){}

void game::update() {
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