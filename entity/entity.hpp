// base class
class entity
{
protected:
    // coord on the map
    int beg_y = 0, beg_x = 0, y_Length = 0, x_Length = 0;
    std::string name;
    int exp, expNeeded;
    unsigned int level;
    int money;
    int statPoint;
    std::map<std::string, float> baseStats, stats;
public:
    entity(/* args */);
    ~entity();
};


// Derived class of entity : player
class player : public entity
{
public:
    std::vector<std::string> character;
    bool s_StatAssigned = false;
    player(/* args */);
    ~player();
    void add_stat(std::string, double);
    friend std::ostream &operator<<(std::ofstream &, player &);
    friend std::istream &operator>>(std::ifstream &, player& );
    std::string &getName();
    std::map<std::string,float> &getBaseStats() { return baseStats; }
    int &getAP() {return statPoint;}
    int &getExp() {return exp;}
    int getExpNeed() {return expNeeded;}
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
    std::map<std::string, int> shopItems;
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
    character.push_back("     .-\"-.      ");
    character.push_back("    /_ _  \\     ");
    character.push_back("    \\@ @  /     ");
    character.push_back("    (_> _)      ");
    character.push_back("      `)(_      ");
    character.push_back("      /((_`)_,  ");
    character.push_back("      \\__(/-\"   ");
    character.push_back("     __|||__    ");
    character.push_back("    ((__|__))   ");
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
std::ostream &operator<<(std::ofstream &out, player &p) {
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
std::istream &operator>>(std::ifstream &in, player &p) {
    std::string line = "", portion = "", portion1 = "";
    getline(in, line);
    std::stringstream ss(line);
    ss >> p.name;
    ss >> p.level;
    ss >> p.statPoint;
    ss >> p.expNeeded;
    ss >> p.exp;
    ss >> p.money;
    ss >> p.s_StatAssigned;
    getline(in, line);
    ss.clear();
    ss.str(line);
    while (ss){
        ss >> portion >> portion1;
        p.baseStats[portion] = std::stof(portion1);
    }
    getline(in, line);
    ss.clear();
    ss.str(line);
    while (ss){
        ss >> portion >> portion1;
        p.stats[portion] = std::stof(portion1);
    }
    return in;
}

std::string &player::getName() {
    return name;
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