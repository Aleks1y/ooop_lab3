#pragma once
#include <iostream>
#include <vector>

#define DESTROYED 3
#define DAMAGED 2
#define MISSED -1
#define EMPTY_FIELD 0
#define PLAYER_SHIP 1

using namespace std;

enum PlayerType
{
    Random,
    Optional,
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
public:
    bool successOnLastStep = false;
    bool destroyShipOnLast = false;
    int field[10][10] = { { 0 } };
    bool isGoodShip(int x, int y, bool horizontal, ShipType type);
    void SetShip(int x, int y, bool horizontal, ShipType type);
    void FillFieldRandom();
    void FillField();
    virtual pair<int, int> nextStep() = 0;
    static Player* createPlayer(PlayerType type);
};

class ConsolePlayer : public Player
{
public:
    pair<int, int> nextStep() override;
    ConsolePlayer();
};

class RandomPlayer : public Player
{
public:
    pair<int, int> nextStep() override;
    RandomPlayer();
};

class OptionalPlayer :public Player
{
private:
    int vectorFire = 0;
    vector<pair<int, int>> lastSuccessPoints;
    pair<int, int>   lastPoint;
    int diag0 = 0;
    int diag1 = 0;
    int diag2 = 0;
    int diag3 = 0;
    pair<int, int> strategyFire();
public:
    pair<int, int> nextStep() override;
    OptionalPlayer();
};

class Judge
{
public:
    size_t player1destroyed = 0;
    size_t player2destroyed = 0;
    bool isPlayerDead(Player player);
    bool isGoodStep(int x, int y, Player* player);
    int step(int x, int y, Player* player);
};

void execute(int rounds, PlayerType firstType, PlayerType secondType);
