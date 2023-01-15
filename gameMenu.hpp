class gameMenu
{
private:
    int menu();
    bool saveCreation();
    bool loadSave();
    void settingMenu();

protected:
    int selection;
    std::vector<std::string> saves;
    std::string filename;
    player loadedPlayer;
    bool assignStat();
    void saveGame();
    void loadGame();
public:
    gameMenu();
    ~gameMenu();
};

std::atomic_bool keyPressed[5] = {false}; 
static int choice = 0;
color c;

bool special_characters(char c) {
    std::string s = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_";
    for (const auto &i : s)
        if (i == c) return false;
    return true;
}

void addStatWindow(player lp, std::vector<std::string> name, int select, int AP, std::string errStat){
    int r_index = 0, t_index = 0, count = 0, ticks = 0;
    std::string header = "Assign Stat Points", err_resize = "RESIZE", symbol = "[+]", aPoints = "Available:", aply = "Apply", rst = "Reset";
    aPoints += std::string(40 - std::to_string(AP).size() - aPoints.size(), ' ') + std::to_string(AP);
    winSize window;
    std::vector<std::string> items;
    for (const auto &i : name){
        items.push_back((count == select ? "[" + i : i) + std::string((count == select ? 37 : 38) - (i.size() + 1) - (std::to_string(lp.getBaseStats()[i]).substr(0,std::to_string(lp.getBaseStats()[i]).find('.') + 3).size() + 1),' ') + std::to_string(lp.getBaseStats()[i]).substr(0, std::to_string(lp.getBaseStats()[i]).find('.') + 3) + " ");
        count++;
    }
    aply = (select == items.size() ?  "[  " + aply + "  ]" : "[    " + aply + "    ]");
    rst = (select == items.size() + 1 ?  "[  " + rst + "  ]" : "[    " + rst + "    ]");
    count = 231;
    while (!keyPressed[4]) {
        std::cout << "\033[0;0H";
        window.update();
        r_index = 0, t_index = 0;
        for (int i = 0; i < window.height - 1; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 2 || j == 0 || j == window.width - 1) {
                    std::cout << "#";
                }else if(window.height < 21 || window.width < 45) {
                    if (i == window.height / 2 && j > window.width / 2 - err_resize.size() / 2 && j <= window.width / 2 - err_resize.size() / 2 + err_resize.size())
                        std::cout << err_resize[t_index++];
                    else
                        std::cout << " ";
                }else if(errStat.size() && (i >= window.height / 2 - 1 && i <= window.height/2 + 1) && j > 5 && j < window.width - 6) {
                        if (i == window.height/2 && j > window.width / 2 - errStat.size() / 2 && j <= window.width / 2 - errStat.size() / 2 + errStat.size())
                            std::cout << c.getBC(196) << errStat[t_index++] << c.cReset();
                        else
                            std::cout << c.getBC(196) << " " << c.cReset();
                }else if(i > window.height / 2 - name.size() - 2 &&  i <= window.height / 2 - name.size() + name.size() - 1 && j > window.width / 2 - 20 && j <= window.width / 2 + 20){
                    if (i == window.height / 2 - name.size() - 1){
                        if(j > window.width / 2 - header.size() / 2 && j <= window.width / 2 - header.size() / 2 + header.size())
                            std::cout << c.getBC(4) << header[t_index++] << c.cReset();
                        else
                            std::cout << c.getBC(4) << " " << c.cReset();
                    }else if (i > window.height / 2 - name.size() - 1){
                        std::cout << c.getBC(7) << c.getC(0);
                        if (j > window.width / 2 - 20 && j <= window.width / 2 + 17)
                        {
                            std::cout << items[r_index][t_index++] << c.cReset();
                            if (j == window.width / 2 + 17)
                                t_index = 0;
                        }else if (j > window.width / 2 + 17){
                            std::cout << (select == r_index ? c.getBC(4) + c.getC(15) : c.getBC(7) + c.getC(0)) << symbol[t_index++] << c.cReset();
                            if (t_index == symbol.size())
                                r_index++;
                        }
                    }else{
                        std::cout << c.getBC(12) << " " << c.cReset();
                    }
                }else if(i == window.height / 2 - name.size() + name.size() && j > window.width / 2 - 20 && j <= window.width / 2 + 20){
                    std::cout<< c.getBC(4) + (t_index > aPoints.size() - std::to_string(AP).size() - 1 ? c.getC(count): "") << aPoints[t_index++] << c.cReset();
                }else if(i == window.height / 2 - name.size() + name.size() + 2 && j > window.width / 2 - 20 && j <= window.width / 2){
                    if (j > window.width / 2 - 10 - aply.size() / 2  && j <= window.width / 2 - 10 - aply.size() / 2 + aply.size()){
                        std::cout << (select == items.size() ? c.getBC(4) : c.getBC(17)) << aply[t_index++] << c.cReset();
                        if (t_index == aply.size())
                            t_index = 0;
                    }
                    else{
                        std::cout << " " ;
                    }
                }else if(i == window.height / 2 - name.size() + name.size() + 2 && j > window.width / 2 && j <= window.width / 2 + 20){
                    if (j > window.width / 2 + 10 - rst.size() / 2  && j <= window.width / 2 + 10 - rst.size() / 2 + rst.size())
                        std::cout << (select == items.size() + 1 ? c.getBC(4) : c.getBC(17)) << rst[t_index++] << c.cReset();
                    else
                        std::cout << " ";
                }else{
                    std::cout << " ";
                }
            }
            t_index = 0;
            std::cout << std::endl;
        }
        if (ticks++ > 18)
            if (--count < 196)
                count = 231;
        usleep(50000);
    }
}

void menuScreen(int selection)
{
    std::vector<std::string> title; 
    std::string err_resize = "RESIZE", newGame = "[1] New Game", load = "[2] Load Save", set = "[3] Setting", ext = "[4] Exit";
    int ticks = 0, t_index = 0, r_index = 0, cRand = rand() % c.getSize();
    title.push_back("    .___        _____.__       .__  __            ");
    title.push_back("    |   | _____/ ____\\__| ____ |__|/  |_  ____    ");
    title.push_back("    |   |/    \\   __\\|  |/    \\|  \\   __\\/ __ \\   ");
    title.push_back("    |   |   |  \\  |  |  |   |  \\  ||  | \\  ___/   ");
    title.push_back("    |___|___|  /__|  |__|___|  /__||__|  \\___  >  ");
    title.push_back("             \\/              \\/              \\/   ");
    title.push_back("     ____.                                        ");
    title.push_back("    |    | ____  __ _________  ____   ____ ___.__.");
    title.push_back("    |    |/  _ \\|  |  \\_  __ \\/    \\_/ __ <   |  |");
    title.push_back("/\\__|    (  <_> )  |  /|  | \\/   |  \\  ___/\\___  |");
    title.push_back("\\________|\\____/|____/ |__|  |___|  /\\___  > ____|");
    title.push_back("                                  \\/     \\/\\/     ");
    winSize window;
    while (!keyPressed[0])
    {
        std::cout << "\033[0;0H";
        window.update();
        r_index = 0, t_index = 0;
        for (int i = 0; i < window.height - 1; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (window.height - 1 < title.size() + 12 || window.width - 3  < title[0].size()){
                    if (i == 0 || i == window.height - 2) {
                        std::cout << "#";
                    }else if (i == window.height / 2 && j > window.width / 2 - err_resize.size() / 2 && j <= window.width / 2 + err_resize.size() / 2){
                        std::cout << err_resize[t_index++];
                    }else if (j == 0 || j == window.width - 1) {
                        std::cout << "#";
                    }else{
                        std::cout << " ";
                    }
                }else{
                    if (i == 0 || i == window.height - 2 || j == 0 || j == window.width - 1) {
                        std::cout << "#";
                    }else if (i > (window.height / 2 > 10 ? window.height / 2 - title.size() : 4) && i < (window.height / 2 > 10 ? window.height / 2 - title.size() + title.size(): title.size() + 4) && j > window.width / 2 - title[r_index].size() / 2 && j < (window.width - 2) / 2 + title[r_index].size() / 2 + 2){
                        std::cout << c.getC(cRand) << title[r_index][t_index++] << c.cReset();
                        if(t_index == title[r_index].size())
                            r_index++;
                    }else if(i == (window.height / 2 > 10 ? window.height / 2 - title.size() + title.size() + 2 : 18) && j > window.width / 2 - newGame.size() / 2 && j < (window.width - 2) / 2 + newGame.size() / 2 + 2){
                        if (selection == 1)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << newGame[t_index++] << c.cReset();
                    }else if(i == (window.height / 2 > 10 ? window.height / 2 - title.size() + title.size() + 4 : 20) && j > window.width / 2 - load.size() / 2 && j < (window.width - 2) / 2 + load.size() / 2 + 3){
                        if (selection == 2)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << load[t_index++] << c.cReset();
                    }else if(i == (window.height / 2 > 10 ? window.height / 2 - title.size() + title.size() + 6 : 22) && j > window.width / 2 - newGame.size() / 2 && j <= (window.width / 2 - newGame.size() / 2) + set.size()){
                        if (selection == 3)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << set[t_index++] << c.cReset();
                    }else if(i == (window.height / 2 > 10 ? window.height / 2 - title.size() + title.size() + 8 : 24) && j > window.width / 2 - newGame.size() / 2 && j <= (window.width / 2 - newGame.size() / 2) + ext.size()){
                        if (selection == 4)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << ext[t_index++] << c.cReset();
                    }else{
                        std::cout << ' ';
                    }
                }
            }
            t_index = 0;
            std::cout << std::endl;
        }
        if (!(++ticks % 3)){
            ticks = 0;
            cRand = rand() % c.getSize();
        }

        usleep(50000);
    }
}

void loadWindows(const std::vector<std::string> &saves, int select) {
    int r_index = 0, t_index = 0;
    std::vector<std::string> options;
    std::string prompt = "    Load Saves    ", err_resize = "RESIZE";
    std::string pg = "page ";
    int cnt = 1;
    for (const auto &save : saves)
        options.push_back("["+ std::to_string(cnt++) + "] " + save.substr(9, save.find('.', 9) - 9));
    std::string pg2 = std::to_string(select/20 + 1) + " of " + std::to_string((options.size()/20 + (options.size()%20 ? 1 : 0)));
    for (int i = pg.size() + pg2.size(); i < prompt.size(); i++)
        pg += ' ';
    pg += pg2;
    
    while (!keyPressed[2])
    {
        winSize window;
        std::cout << "\033[0;0H";
        window.update();
        t_index = 0, r_index = (select/20)*20;
        for (int i = 0; i < window.height - 1; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 2 || j == 0 || j == window.width - 1) {
                    std::cout << "#";
                }else if(window.height < 30 || window.width < prompt.size() + 2) {
                    if(i == window.height / 2 && j > window.width / 2 - err_resize.size()/2 && j <= window.width / 2 - err_resize.size()/2 + err_resize.size())
                        std::cout << err_resize[t_index++];
                    else
                        std::cout << " ";
                }else if(i > window.height / 2 - window.height / 3 && i <= window.height / 2 - window.height / 3 + 21 && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    if (i == window.height / 2 - window.height / 3 + 1) {
                        std::cout << c.getBC(4) << c.getC(7) << prompt[t_index++] << c.cReset();
                    }else if (i > window.height / 2 - window.height / 3 + 1 && r_index < options.size() && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2) {
                        if (select == r_index)
                                std::cout << c.getBC(4) << c.getC(7);
                        else 
                            std::cout << c.getBC(7) << c.getC(4);
                        if(t_index < options[r_index].size()){
                            std::cout << options[r_index][t_index++] << c.cReset();
                        }
                        else{
                            std::cout << " " << c.cReset();
                        }
                    }else{
                        std::cout << c.getBC(7) << " " << c.cReset();
                    }
                }else if(i == window.height / 2 - window.height / 3 + 22 && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    std::cout << c.getBC(4) << c.getC(7) << pg[t_index++] << c.cReset();
                }else{
                    std::cout << ' ';
                }
            }
            if (r_index < options.size() && t_index == options[r_index].size())
                r_index++;
            t_index = 0;
            std::cout << std::endl;
        }
        usleep(50000);
    }
}

void settingWindow() {
    std::string inprogress = "       In Progress!       ";
    int left = 0, right = 0, t_index = 0, ticks = 0;
    winSize window;
    while (!keyPressed[1])
    {
        std::cout << "\033[0;0H";
        window.update();
        t_index = 0;
        for (int i = 0; i < window.height - 1; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 2) {
                    std::cout << c.getBC(0) << "#";
                }else if(i == window.height / 2 - 2 && j > window.width / 2 - inprogress.size() / 2 && j < (window.width - 2) / 2 + inprogress.size() / 2 + 2){
                    std::cout << c.getBC(0) << inprogress[t_index++];
                }else if (j == 0 || j == window.width - 1) {
                    std::cout << c.getBC(0) << "#";
                }else{
                    std::cout << c.getBC((j + left - right) % c.getSize()) << ' ';
                }
                right--;
                std::cout << c.cReset();
            }
            t_index = 0;
        } 
        left += 4, right++;
        std::cout << std::endl;
        usleep(200000);
    }
}

void outputFileWindow(const std::string &filename, std::string err) {
    std::string prompt = "Please Enter a Filename!", nameErr = "Error: Name is Too Long!", err_resize = "RESIZE";
    int r_index = 0, t_index = 0, ticks = 0;
    winSize window;
    while (!keyPressed[3])
    {
        std::cout << "\033[0;0H";
        window.update();
        t_index = 0;
        for (int i = 0; i < window.height - 1; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 2 || j == 0 || j == window.width - 1) {
                    std::cout << "#";
                }else if(window.height < 5 || window.width < prompt.size() + 6) {
                    if (i == window.height / 2 && j > window.width / 2 - err_resize.size() / 2 && j <= window.width / 2 - err_resize.size() / 2 + err_resize.size())
                        std::cout << err_resize[t_index++];
                    else
                        std::cout << " ";
                }else if(i == window.height / 2 - 2 && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    if (err.size()){
                        std::cout << c.getC(r_index) << err[t_index++] << c.cReset();
                    }else if (filename.size() == 0)
                        std::cout << c.getC(r_index) << prompt[t_index++] << c.cReset();
                    else if (t_index < filename.size())
                        if (filename.size() <= prompt.size())
                            std::cout << c.getBC(7) << c.getC(4) << filename[t_index++] << c.cReset();
                        else
                            std::cout << c.getBC(7) << c.getC(4) << nameErr[t_index++] << c.cReset();
                    else
                        std::cout << c.getBC(7) << " " << c.cReset();
                }else{
                    std::cout << ' ';
                }
            }
            t_index = 0;
            std::cout << std::endl;
        }
        if(!(++ticks % 7))
            r_index = r_index == 0 ? 15 : 0;
        usleep(50000);
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

gameMenu::gameMenu(/* args */)
{
    for (const auto & entry : fs::directory_iterator("savegame"))
        saves.push_back(entry.path());
    selection = menu();
}

void gameMenu::saveGame() {
    std::ofstream ofile(filename);
    if(ofile.is_open())
        ofile << loadedPlayer;
    ofile.close();
}

void gameMenu::loadGame() {
    std::ifstream ifile(filename);
    if(ifile.is_open())
        ifile >> loadedPlayer;
    ifile.close();
}

int gameMenu::menu() {
    int select = '0';
    while (true)
    {
        std::thread lockf(menuScreen, choice);        
        select = getch();
        // Set the flag with true to break the loop.
        keyPressed[0] = true;
        lockf.join();
        keyPressed[0] = false;
        if (select == ','){
            choice--;
            if (choice < 0)
                choice = 4;
        }else if (select == '.'){
            choice++;
            if (choice > 4)
                choice = 0;
        }
        if (select - '0' == 1 || (select == '\n' && choice == 1)){
            select = choice;
            if (saveCreation()){
                filename = "savegame/" + filename + ".txt";
                saveGame();
                break;
            }
            filename = "";
        }else if (select - '0' == 2 || (select == '\n' && choice == 2)) {
            select = choice;
            if(loadSave()){
                loadGame();
                break;
            }
        }else if (select - '0' == 3 || (select == '\n' && choice == 3)) {
            settingMenu();
        }else if (select - '0' == 4 || (select == '\n' && choice == 4)){
            exit(EXIT_SUCCESS);
        }
    }
    return select;
}

bool gameMenu::saveCreation(){
    std::string fExistErr = "";
    int key = '0';
    while (true)
    {
        bool fExist = false;
        std::thread lockf(outputFileWindow, filename, fExistErr);  
        key = getch();
        fExistErr.clear();      
        // Set the flag with true to break the loop.
        keyPressed[3] = true;
        lockf.join();
        keyPressed[3] = false;
        if (!special_characters(key))
            filename += key;
        else if(key == 127)
            filename = filename.substr(0, filename.size() - 1);
        if (key == '\n'){
            if (filename.size() > 14 || filename.size() < 1)
            {
                fExist = true;
                filename = "";
                fExistErr = "Length need to be 1-14  ";
            }
            for (const auto & i : saves){
                if(filename + ".txt" == i.substr(9)) {
                    fExist = true;
                    filename = "";
                    fExistErr = "Error File Already Exist";
                    break;
                }
            }
            if (fExist)
                continue;
            return true;
        }
        if (key == 27)
            return false;
    }
    return true;
}

bool gameMenu::loadSave(){
    int select = 0;
    choice = 0;
    while (true)
    {
        std::thread lockf(loadWindows, saves, choice);        
        select = getch();
        // Set the flag with true to break the loop.
        keyPressed[2] = true;
        lockf.join();
        keyPressed[2] = false;
        switch (select)
        {
        case ',':
            choice--;
            if (choice < 0)
                choice = saves.size() - 1;
            break;
        case '.':
            choice++;
            if (choice == saves.size())
                choice = 0;
            break;
        case 27:
            return false;
        case '\n':
            filename = saves[choice];
            return true;
        default:
            break;
        }
    }
    return true;
}

void gameMenu::settingMenu(){
    int key = '0';
    while (true)
    {
        std::thread lockf(settingWindow);        
        key = getch();
        // Set the flag with true to break the loop.
        keyPressed[1] = true;
        lockf.join();
        if (key == 27)
            break;
        else
            keyPressed[1] = false;
    }
    keyPressed[1] = false;
}

gameMenu::~gameMenu(){}

bool gameMenu::assignStat() {
    int select = 0;
    std::string errorMessage = "";
    choice = 0;
    std::vector<std::string> statLable;
    player old = loadedPlayer;
    statLable.push_back(B_HP);
    statLable.push_back(B_ATT);
    statLable.push_back(B_MATT);
    statLable.push_back(B_CRITC);
    statLable.push_back(B_CRITR);
    statLable.push_back(B_DEF);
    statLable.push_back(B_MDEF);
    statLable.push_back(B_SPD);
    while (true)
    {
        std::thread lockf(addStatWindow, loadedPlayer, statLable, choice, loadedPlayer.getAP(), errorMessage);        
        select = getch();
        // Set the flag with true to break the loop.
        keyPressed[4] = true;
        lockf.join();
        keyPressed[4] = false;
        errorMessage = "";
        int s = (loadedPlayer.getAP() > 0 ? 0 : statLable.size());
        switch (select)
        {
        case ',':
            choice--;
            if (choice < s)
                choice = statLable.size() + 1;
            break;
        case '.':
            choice++;
            if (choice == statLable.size() + 2)
                choice = (loadedPlayer.getAP() ? 0 : statLable.size());
            break;
        case '\n':
            if (choice < statLable.size())
            {
                loadedPlayer.getBaseStats()[statLable[choice]]++;
                if (!(--loadedPlayer.getAP()))
                    choice = statLable.size();
            }else if (choice == statLable.size() + 1){
                loadedPlayer = old;
            }else if (choice == statLable.size()){
                switch (loadedPlayer.getAP())
                {
                case 0:
                    return true;
                default:
                    if (!loadedPlayer.s_StatAssigned){
                        errorMessage = "Please Assign All Stat Points For Your Starting Character!";
                        break;
                    }               
                    return false;
                }
            }
            break;
        case 27:
            return false;
        default:
            break;
        }  
    }
    return false;
}

