#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sstream>
#include <cmath>
using namespace std;


class color
{
private:
    string reset;
    int cSize;
    string *c = nullptr, *bc = nullptr;
public:
    color();
    ~color();
    string cReset() const;
    string getC(int) const;
    string getBC(int) const;
    int getSize() const;
};

void cursorSet(int y, int x) {
    std::string c = "\033[" + std::to_string(y) + ";" + std::to_string(x) + "f";
    std::cout << c;
}

// ANSI Color Manip...
color::color() : reset("\u001b[0m"), cSize(16*16) {
    c = new  string [cSize];
    bc = new  string [cSize];
    int count = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            c[count++] = "\u001b[38;5;" + std::to_string(i * 16 + j) + "m ";
    count = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            bc[count++] = "\u001b[48;5;" +  to_string(i * 16 + j) + "m ";
}
color::~color() {
    delete[] c;
    delete[] bc;
}
 string color::getC(int x) const{
    return c[x];
}
 string color::getBC(int x) const{
    return bc[x];
}
 string color::cReset() const {
    return reset;
}
int color::getSize() const {
    return cSize;
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


int main() {
    color c;
    for (int i = 0; i < c.getSize(); i++){
        std::cout << c.getBC(i);
        for (int j = 0; j < c.getSize(); j++)
            std::cout << c.getC(j) << j << " ";
        std::cout << c.cReset() << std::endl;
    }
    // for (int i = 0; i < c.getSize(); i++)
    //     std::cout << c.getC(i) << i;
    // std::cout << std::endl;
    // for (int i = 0; i < c.getSize(); i++)
    //     std::cout << c.getBC(i) << i;
    // std::cout << std::endl;
    
    return 0;
    
}