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
color::color() : reset("\u001b[0m"), cSize(16) {
    c = new std::string [cSize];
    bc = new std::string [cSize];
    int code = 0;
    for (int i = 0; i < cSize; i++)
    {
        if (code == 8)
            code = 0;
        if (i < cSize / 2)
            c[i] = "\u001b[3" + std::to_string(code++) + "m";
        else
            c[i] = "\u001b[3" + std::to_string(code++) + ";1m";
    }
    code = 0;
    for (int i = 0; i < cSize; i++)
    {
        if (code == 8)
            code = 0;
        if (i < cSize / 2)
            bc[i] = "\u001b[4" + std::to_string(code++) + "m";
        else
            bc[i] = "\u001b[4" + std::to_string(code++) + ";1m";
    }
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