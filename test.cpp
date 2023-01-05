#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sstream>
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

// ANSI Color Manip...
color::color() : reset("\u001b[0m"), cSize(16) {
    c = new  string [cSize];
    bc = new  string [cSize];
    int code = 0;
    for (int i = 0; i < cSize; i++)
    {
        if (code == 8)
            code = 0;
        if (i < cSize / 2)
            c[i] = "\u001b[3" +  to_string(code++) + "m";
        else
            c[i] = "\u001b[3" +  to_string(code++) + ";1m";
    }
    code = 0;
    for (int i = 0; i < cSize; i++)
    {
        if (code == 8)
            code = 0;
        if (i < cSize / 2)
            bc[i] = "\u001b[4" +  to_string(code++) + "m";
        else
            bc[i] = "\u001b[4" +  to_string(code++) + ";1m";
    }
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
    for (int i = 0; i < c.getSize(); i++)
    {
         cout << c.getC(i) << i << c.cReset();
    }
     cout <<  endl;

    for (int i = 0; i < c.getSize(); i++)
    {
         cout << c.getBC(i) << i << c.cReset();
    }
     cout <<  endl;

    return 0;
    
}