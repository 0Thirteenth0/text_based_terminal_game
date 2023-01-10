
class player : public entity
{
private:
    std::string name;
    double exp, expNeeded;
    unsigned int level;
    int money;
    int statPoint;
    std::map<std::string, float> baseStats, stats;

public:
    player(/* args */);
    ~player();
    void add_stat(std::string, double);
    friend std::ostream &operator<<(std::ofstream &, player);
    friend std::istream &operator>>(std::ifstream &, player);
    void name_change(std::string);
};

player::player(/* args */)
{
    name = "player";
    money = 100;
    level = 1, exp = 0, expNeeded = 50;
    baseStats[B_HP] = stats[M_HP] = stats[HP] = 50;
    baseStats[B_ATT] = stats[ATT] = 10;
    baseStats[B_MATT] = stats[MATT] = 10;
    baseStats[B_DEF] = stats[DEF] = 10;
    baseStats[B_MDEF] = stats[MDEF] = 10;
    baseStats[B_CRITC] = stats[CRITC] = 10;
    baseStats[B_CRITR] = stats[CRITR] = 10;
    baseStats[B_SPD] = stats[SPD] = 10;
    statPoint = 10;
}

// extract data into save file;
std::ostream &operator<<(std::ofstream &out, player p) {
    out << p.name << " " << p.level << " " << p.statPoint << " " << p.expNeeded << " " << p.exp << " " << p.money<< "\n";
    for (auto &i : p.baseStats)
        out << i.first << " " << i.second << "\t";
    out << "\n";
    for (auto &i : p.stats)
        out << i.first << " " << i.second << "\t";
    out << "\n";
    return out;
}
// read data into game
std::istream &operator>>(std::ifstream &in, player p) {
    std::string line = "";
    int index = 0;
    std::string portion;
    getline(in, line);
    p.name = line.substr(index, line.find(' ', index) - index);
    index = line.find(' ', index) + 1;
    p.level = std::stoi(line.substr(index, line.find(' ', index) - index));
    index = line.find(' ', index) + 1;
    p.statPoint = std::stoi(line.substr(index, line.find(' ', index) - index));
    index = line.find(' ', index) + 1;
    p.expNeeded = std::stod(line.substr(index, line.find(' ', index) - index));
    index = line.find(' ', index) + 1;
    p.exp = std::stod(line.substr(index, line.find(' ', index) - index));
    index = line.find(' ', index) + 1;
    p.money = std::stoi(line.substr(index));
    index = 0;
    getline(in, line);
    while (index < line.size())
    {
        portion = line.substr(index, line.find(' ', index) - index);
        index = line.find(' ', index) + 1;
        p.baseStats[portion] = std::stof(line.substr(index, line.find('\t', index)));
        index = line.find('\t', index) + 1;
    }
    index = 0;
    getline(in, line);
    while (index < line.size())
    {
        portion = line.substr(index, line.find(' ', index) - index);
        index = line.find(' ', index) + 1;
        p.stats[portion] = std::stof(line.substr(index, line.find('\t', index)));
        index = line.find('\t', index) + 1;
    }
    return in;
}

void player::name_change(std::string n) {
    name = n;
}

player::~player()
{
}

void player::add_stat(std::string stat, double value)
{

}