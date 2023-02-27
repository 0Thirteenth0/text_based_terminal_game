#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sstream>
#include <cmath>
#include <sys/ioctl.h>
#include <vector>
#include <filesystem>
#include <atomic>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include <fcntl.h>
#include <condition_variable>
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

class BufferToggle
{
    private:
        struct termios t;

    public:
        /*
         * Disables buffered input
         */

        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
        /*
         * Enables buffered input
         */
        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
};

int mygetch() {
    char ch;
    int error;
    static struct termios Otty, Ntty;

    fflush(stdout);
    tcgetattr(0, &Otty);
    Ntty = Otty;

    Ntty.c_iflag  =  0;     /* input mode       */
    Ntty.c_oflag  =  0;     /* output mode      */
    Ntty.c_lflag &= ~ICANON;    /* line settings    */

#if 1
    /* disable echoing the char as it is typed */
    Ntty.c_lflag &= ~ECHO;  /* disable echo     */
#else
    /* enable echoing the char as it is typed */
    Ntty.c_lflag |=  ECHO;  /* enable echo      */
#endif

    Ntty.c_cc[VMIN]  = CMIN;    /* minimum chars to wait for */
    Ntty.c_cc[VTIME] = CTIME;   /* minimum wait time    */

#if 1
    /*
    * use this to flush the input buffer before blocking for new input
    */
    #define FLAG TCSAFLUSH
#else
    /*
    * use this to return a char from the current input buffer, or block if
    * no input is waiting.
    */
    #define FLAG TCSANOW

#endif

    if ((error = tcsetattr(0, FLAG, &Ntty)) == 0) {
        error  = read(0, &ch, 1 );        /* get char from stdin */
        error += tcsetattr(0, FLAG, &Otty);   /* restore old settings */
    }

    return (error == 1 ? (int) ch : -1 );
}
int main(int argc, char **argv) {
    char s[2] = {0};
    BufferToggle t;
    t.off();
    while (1) {
        if (kbhit())
        {
            std::cout << "Hello\n" <<std::endl;
        }else {
            std::cout << "Helsslo\n" << std::endl;
        }
        
        
        
        sleep(1);
         
        system("clear");
    }
    t.on();
}