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

