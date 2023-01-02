class player
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
    friend std::ostream &operator<<(std::ostream &, player);
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

std::ostream &operator<<(std::ostream &out, player p) {
    out << p.name << " " << p.level << " " << p.statPoint << " " << p.expNeeded  << p.exp << " " << p.money<< "\n";
    for (auto &i : p.baseStats)
        out << i.first << ":" << i.second << " ";
    out << "\n";
    for (auto &i : p.stats)
        out << i.first << ":" << i.second << " ";
    out << "\n";
    return out;
}
player::~player()
{
}
