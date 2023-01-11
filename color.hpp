class color
{
private:
    std::string reset;
    int cSize;
    std::string *c = nullptr, *bc = nullptr;
public:
    color();
    ~color();
    std::string cReset() const;
    std::string getC(int) const;
    std::string getBC(int) const;
    int getSize() const;
};

// ANSI Color Manip...
color::color() : reset("\u001b[0m"), cSize(16*16) {
    c = new  std::string [cSize];
    bc = new  std::string [cSize];
    int count = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            c[count++] = "\u001b[38;5;" + std::to_string(i * 16 + j) + "m";
    count = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            bc[count++] = "\u001b[48;5;" + std::to_string(i * 16 + j) + "m";
}
color::~color() {
    delete[] c;
    delete[] bc;
}
std::string color::getC(int x) const{
    return c[x];
}
std::string color::getBC(int x) const{
    return bc[x];
}
std::string color::cReset() const {
    return reset;
}
int color::getSize() const {
    return cSize;
}