#pragma once
#include <iostream>
#include <vector>

#define DESTROYED 3
#define DAMAGED 2
#define MISSED -1
#define EMPTY_FIELD 0
#define PLAYER_SHIP 1
#define FIELD (isFirst ? field2 : field1) 

using namespace std;
using Coord = pair<int, int>;

enum PlayerType
{
    Random,
    Optimal,
    Interactive
};

enum class ShipType
{
    four = 4,
    three = 3,
    two = 2,
    one = 1
};

class Player
{
    friend class Judge;
protected:
    bool successOnLastStep = false;
    bool destroyShipOnLast = false;
    int field[10][10] = { { 0 } };
    bool isGoodShip(int x, int y, bool horizontal, ShipType type);
    void SetShip(int x, int y, bool horizontal, ShipType type);
    void FillFieldRandom();
    void FillField();
public:
    void SetSuccessOnLastStep(bool val);
    void SetDestroyShipOnLast(bool val);
    static shared_ptr<Player> createPlayer(PlayerType type);
    virtual Coord nextStep() = 0;
    virtual ~Player() {};
};

class ConsolePlayer : public Player
{
public:
    Coord nextStep() override;
    ConsolePlayer();
};

class RandomPlayer : public Player
{
public:
    Coord nextStep() override;
    RandomPlayer();
};

class OptimalPlayer :public Player
{
private:
    int vectorFire = 0;
    vector<Coord> lastSuccessPoints;
    Coord   lastPoint;
    int diag0 = 0;
    int diag1 = 0;
    int diag2 = 0;
    int diag3 = 0;
    Coord strategyFire();
public:
    Coord nextStep() override;
    OptimalPlayer();
};

class Judge
{
private:
    int field1[10][10];
    int field2[10][10];
    size_t player1destroyed = 0;
    size_t player2destroyed = 0;
public:
    size_t GetPlayerDestroyed(bool isFirst);
    void IncPlayerDestroyed(bool isFirst);
    bool isGoodField(const int (&field)[10][10]);
    bool isGoodStep(int x, int y, bool isFirst);
    int step(int x, int y, bool isFirst);
    Judge(shared_ptr<Player> player1, shared_ptr<Player> player2);
};

void execute(int rounds, PlayerType firstType, PlayerType secondType);
