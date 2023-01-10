class winSize
{
public:
    int width, height;
    winSize(/* args */);
    ~winSize();
    void update();
};

winSize::winSize(/* args */){
    update();
}
void winSize::update(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    height = w.ws_row;
    width = w.ws_col;
}

winSize::~winSize(){}
