// base class
class entity
{
private:

protected:
    int y = 0, x = 0;

public:
    entity(/* args */);
    ~entity();
};


// Derived class of entity : player
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
    bool s_StatAssigned = false;
    player(/* args */);
    ~player();
    void add_stat(std::string, double);
    friend std::ostream &operator<<(std::ofstream &, player);
    friend std::istream &operator>>(std::ifstream &, player);
    void name_change(std::string);
    std::map<std::string,float> &getBaseStats() { return baseStats; }
    int &getAP() {return statPoint;}
    void operator=(const player &);
};

// Derived class of entity : event
class event : public entity
{
private:

protected:
    

public:
    event(/* args */);
    ~event();
};

// Derived class of entity : enermyENCT
class emermyENCT : public entity
{
private:
    /* data */
public:
    emermyENCT(/* args */);
    ~emermyENCT();
};

// Derived class of entity : shop
class shop : public entity
{
private:
    /* data */
public:
    shop(/* args */);
    ~shop();
};

// Base class Entity Function Definitions:
entity::entity(/* args */)
{
}

entity::~entity()
{
}


// player function definitions:
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
    s_StatAssigned = false;
}

void player::operator=(const player & cpy){
    name = cpy.name, exp = cpy.exp, expNeeded = cpy.expNeeded, level = cpy.level, money = cpy.money;
    statPoint= cpy.statPoint, s_StatAssigned = cpy.s_StatAssigned;
    baseStats = cpy.baseStats, stats = cpy.stats;
}

// extract data into save file;
std::ostream &operator<<(std::ofstream &out, player p) {
    out << p.name << " " << p.level << " " << p.statPoint << " " << p.expNeeded << " " << p.exp << " " << p.money << " " << p.s_StatAssigned <<"\n";
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
    p.money = std::stoi(line.substr(index, line.find(' ', index) - index));
    index = line.find(' ', index) + 1;
    p.s_StatAssigned = std::stoi(line.substr(index));
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

// enermyENCT function definitions:
emermyENCT::emermyENCT(/* args */)
{
}

emermyENCT::~emermyENCT()
{
}


// event function definitions:
event::event(/* args */)
{
}

event::~event()
{
}

// shop function definitions:
shop::shop(/* args */)
{
}

shop::~shop()
{
}