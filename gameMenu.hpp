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

void addStatWindow(int select){
    int r_index = 0, t_index = 0;
    std::string header = "Assign Data";
    winSize window;
    while (!keyPressed[4]) {
        std::cout << "\033[0;0H";
        window.update();
        r_index = 0, t_index = 0;
        for (int i = 0; i < window.height - 2; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 3 || j == 0 || j == window.width - 1) {
                    std::cout << "#";
                }else{
                    std::cout << " ";
                }
            }
            t_index = 0;
            std::cout << std::endl;
        }
        
        usleep(50000);
    }
}

void menuScreen(int selection)
{
    std::vector<std::string> title;
    std::string err_resize = "RESIZE", newGame = "[1] New Game", load = "[2] Load Save", set = "[3] Setting";
    int ticks = 0, t_index = 0, r_index = 0;
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
        for (int i = 0; i < window.height - 2; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (window.height - 2 < title.size() + 12 || window.width - 2  < title[0].size()){
                    if (i == 0 || i == window.height - 3) {
                        std::cout << "#";
                    }else if (i == (window.height - 3) / 2 && j > window.width / 2 - err_resize.size() / 2 && j <= window.width / 2 + err_resize.size() / 2){
                        std::cout << err_resize[t_index++];
                    }else if (j == 0 || j == window.width - 1) {
                        std::cout << "#";
                    }else{
                        std::cout << " ";
                    }
                }else{
                    if (i == 0 || i == window.height - 3) {
                        std::cout << "#";
                    }else if (i > 4 && i < 16 && j > window.width / 2 - title[r_index].size() / 2 && j < (window.width - 2) / 2 + title[r_index].size() / 2 + 2) {
                        std::cout << title[r_index][t_index++];
                        if(t_index == title[r_index].size())
                            r_index++;
                    }else if(i == 18 && j > window.width / 2 - newGame.size() / 2 && j < (window.width - 2) / 2 + newGame.size() / 2 + 2){
                        if (selection == 1)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << newGame[t_index++] << c.cReset();
                    }else if(i == 20 && j > window.width / 2 - load.size() / 2 && j < (window.width - 2) / 2 + load.size() / 2 + 3){
                        if (selection == 2)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << load[t_index++] << c.cReset();
                    }else if(i == 22 && j > window.width / 2 - newGame.size() / 2 && j <= (window.width / 2 - newGame.size() / 2) + set.size()){
                        if (selection == 3)
                            std::cout << c.getBC(2) << c.getC(4);
                        std::cout << set[t_index++] << c.cReset();
                    }else if (j == 0 || j == window.width - 1) {
                        std::cout << "#";
                    }else{
                        std::cout << ' ';
                    }
                }
            }
            t_index = 0;
        }
        std::cout << std::endl;
        if (++ticks % 30)
            ticks = 0;
        usleep(50000);
    }
}

void loadWindows(const std::vector<std::string> &saves, int select) {
    int r_index = 0, t_index = 0;
    std::vector<std::string> options;
    std::string prompt = "    Load Saves    ";
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
        for (int i = 0; i < window.height - 2; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 3) {
                    std::cout << "#";
                }else if(i > 7 && i <= 28  && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    if (i == 8) {
                        std::cout << c.getBC(12) << c.getC(7) << prompt[t_index++] << c.cReset();
                    } else if (i > 8 && r_index < options.size() && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2) {
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
                }else if(i == 29 && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    std::cout << c.getBC(12) << c.getC(7) << pg[t_index++] << c.cReset();
                }else if (j == 0 || j == window.width - 1) {
                    std::cout << "#";
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
    int r_index = 0, t_index = 0, ticks = 0;
    winSize window;
    while (!keyPressed[1])
    {
        std::cout << "\033[0;0H";
        window.update();
        t_index = 0;
        for (int i = 0; i < window.height - 2; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 3) {
                    std::cout << c.getBC(0) << "#";
                }else if(i == window.height / 2 - 2 && j > window.width / 2 - inprogress.size() / 2 && j < (window.width - 2) / 2 + inprogress.size() / 2 + 2){
                    std::cout << c.getBC(0) << inprogress[t_index++];
                }else if (j == 0 || j == window.width - 1) {
                    std::cout << c.getBC(0) << "#";
                }else{
                    std::cout << c.getBC((j + r_index) % c.getSize()) << ' ';
                }
                std::cout << c.cReset();
            }
            t_index = 0;
        }
        
        r_index++;
        
        std::cout << std::endl;
        usleep(200000);
    }
}

void outputFileWindow(const std::string &filename, std::string err) {
    std::string prompt = "Please Enter a Filename!", nameErr = "Error: Name is Too Long!";
    int r_index = 0, t_index = 0, ticks = 0;
    winSize window;
    while (!keyPressed[3])
    {
        std::cout << "\033[0;0H";
        window.update();
        t_index = 0;
        for (int i = 0; i < window.height - 2; i++)
        {
            for (int j = 0; j < window.width; j++)
            {
                if (i == 0 || i == window.height - 3) {
                    std::cout << "#";
                }else if(i == window.height / 2 - 2 && j > window.width / 2 - prompt.size() / 2 && j < (window.width - 2) / 2 + prompt.size() / 2 + 2){
                    if (err.size()){
                        std::cout << c.getC(r_index) << err[t_index++] << c.cReset();
                    }else if (filename.size() == 0)
                        std::cout << c.getC(r_index) << prompt[t_index++] << c.cReset();
                    else if (t_index < filename.size())
                        if (filename.size() <= prompt.size())
                            std::cout << c.getBC(7) << c.getC(8) << filename[t_index++] << c.cReset();
                        else
                            std::cout << c.getBC(7) << c.getC(8) << nameErr[t_index++] << c.cReset();
                    else
                        std::cout << c.getBC(7) << " " << c.cReset();
                }else if (j == 0 || j == window.width - 1) {
                    std::cout << "#";
                }else{
                    std::cout << ' ';
                }
            }
            t_index = 0;
            std::cout << std::endl;
        }
        if(!(++ticks % 7))
            r_index = r_index == 0 ? 8 : 0;
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
                choice = 3;
        }else if (select == '.'){
            choice++;
            if (choice > 3)
                choice = 0;
        }
        if (select - '0' == 1 || (select == '\n' && choice == 1)){
            select = choice;
            if (saveCreation()){
                std::ofstream ofile;
                ofile.open(filename = "./savegame/" + filename + ".txt");
                ofile << loadedPlayer;
                ofile.close();
                break;
            }
            filename = "";
        }else if (select - '0' == 2 || (select == '\n' && choice == 2)) {
            select = choice;
            if(loadSave()){
                std::ifstream ifile(filename = "./"+filename);
                if(ifile.is_open())
                   ifile >> loadedPlayer;
                ifile.close();
                break;
            }
            
        }else if (select - '0' == 3 || (select == '\n' && choice == 3)) {
            settingMenu();
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
    choice = 0;
    while (true)
    {
        std::thread lockf(addStatWindow, choice);        
        select = getch();
        // Set the flag with true to break the loop.
        keyPressed[4] = true;
        lockf.join();
        keyPressed[4] = false;
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
            return true;
        default:
            break;
        }
    }
    return false;
}

