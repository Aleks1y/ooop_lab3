#include "Header.h"

void Player::SetShip(int x, int y, bool horizontal, ShipType type)
{
    int length = (int)type;

    if (horizontal)
         for (int i = 0; i < length; ++i)
            field[y][x + i] = PLAYER_SHIP;
    else
        for (int i = 0; i < length; ++i)
            field[y + i][x] = PLAYER_SHIP;
}

bool Player::isGoodShip(int x, int y, bool horizontal, ShipType type)
{
    int length = (int)type;

    for (size_t k = 0; k < length; k++)
    {
        for (int i = -1; i < 2; i++)
        {
            if (y + i < 10 && y + i >= 0)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x + j < 10 && x + j >= 0 && field[y + i][x + j] != EMPTY_FIELD)
                    {
                        return false;
                    }
                }
            }
        }
        x += (int)horizontal;
        y += (int)(!horizontal);
        if (x > 9 || y > 9)
            return false;
    }
    return true;
}

void Player::SetSuccessOnLastStep(bool val)
{
    successOnLastStep = val;
}

void Player::SetDestroyShipOnLast(bool val)
{
    destroyShipOnLast = val;
}

shared_ptr<Player> Player::createPlayer(PlayerType type)
{
    switch (type)
    {
    case Random:
        return make_shared<RandomPlayer>();
    case Optimal:
        return make_shared<OptimalPlayer>();
    case Interactive:
        return make_shared<ConsolePlayer>();
    }
}
void Player::FillFieldRandom()
{
    bool ishorizontal;
    int x, y;
    do
    {
        ishorizontal = (rand() % 2);
        x = rand() % 10;
        y = rand() % 10;
    }while (!isGoodShip(x, y, ishorizontal, ShipType::four));
    SetShip(x, y, ishorizontal, ShipType::four);

    for (int i = 0; i < 2; ++i)
    {
        do
        {
            ishorizontal = (rand() % 2);
            x = rand() % 10;
            y = rand() % 10;
        } while (!isGoodShip(x, y, ishorizontal, ShipType::three));
        SetShip(x, y, ishorizontal, ShipType::three);
    }
    for (int i = 0; i < 3; ++i)
    {
        do
        {
            ishorizontal = (rand() % 2);
            x = rand() % 10;
            y = rand() % 10;
        } while (!isGoodShip(x, y, ishorizontal, ShipType::two));
        SetShip(x, y, ishorizontal, ShipType::two);
    }
    for (int i = 0; i < 4; ++i)
    {
        do
        {
            ishorizontal = (rand() % 2);
            x = rand() % 10;
            y = rand() % 10;
        } while (!isGoodShip(x, y, ishorizontal, ShipType::one));
        SetShip(x, y, ishorizontal, ShipType::one);
    }
}

void Player::FillField()
{
    bool ishorizontal;
    int x, y;
    do
    {
        cout << "Enter information about four decked ship (int x, int y, bool ishorizontal)";
        cin >> x >> y >> ishorizontal;
    } while (!isGoodShip(x, y, ishorizontal, ShipType::four));
    SetShip(x - 1, y - 1, ishorizontal, ShipType::four);

    for (int i = 0; i < 2; ++i)
    {
        do
        {
            cout << "Enter information about #" << i + 1 << " three decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::three));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::three);
    }
    for (int i = 0; i < 3; ++i)
    {
        do
        {
            cout << "Enter information about #" << i + 1 << " two decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::two));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::two);
    }
    for (int i = 0; i < 4; ++i)
    {
        do
        {
            cout << "Enter information about #" << i + 1 << " one decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::one));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::one);
    }
}

Coord ConsolePlayer::nextStep()
{
    cout << "Enter int x int y" << endl;

    int x, y;
    cin >> x >> y;
    return { x - 1, y - 1 };
}

ConsolePlayer::ConsolePlayer()
{
    string str;
    do
    {
        cout << "Do you want to set the ships random? yes/no \n";
        cin >> str;
    } while (str != "yes" && str != "no");

    if (str == "yes")
        FillFieldRandom();

    else
        FillField();
}

Coord RandomPlayer::nextStep()
{
    int x = rand() % 10;
    int y = rand() % 10;

    return { x, y };
}

RandomPlayer::RandomPlayer()
{
    FillFieldRandom();
}

Coord OptimalPlayer::strategyFire()
{
    if (diag0 < 10)
    {
        lastPoint = { diag0, diag0 };
        diag0++;
        return lastPoint;
    }
    else if (diag1 < 10)
    {
        lastPoint = { 9 - diag1, diag1 };
        diag1++;
        return lastPoint;
    }
    else if (diag2 < 10)
    {
        lastPoint = { 4, diag2 };
        diag2++;
        return lastPoint;
    }
    else if (diag3 < 10)
    {
        lastPoint = { diag3, 5 };
        diag3++;
        return lastPoint;
    }
    else
    {
        lastPoint = { rand() % 10, rand() % 10 };
        return lastPoint;
    }
}

Coord OptimalPlayer::nextStep()
{
    if (!successOnLastStep && lastSuccessPoints.empty())
        return strategyFire();
    else if (!successOnLastStep && !lastSuccessPoints.empty())
    {
        while (lastSuccessPoints.size() > 1)
        {
            lastSuccessPoints.pop_back();
        }
        vectorFire = (vectorFire + 1) % 4;
    }
    else if (destroyShipOnLast)
    {
        lastSuccessPoints.clear();
        vectorFire = 0;
        return strategyFire();
    }
    else if (successOnLastStep)
        lastSuccessPoints.push_back(lastPoint);

    switch (vectorFire)
    {
    case 0:
        lastPoint = { lastSuccessPoints[lastSuccessPoints.size() - 1].first + 1, lastSuccessPoints[lastSuccessPoints.size() - 1].second };
        break;
    case 1:
        lastPoint = {lastSuccessPoints[lastSuccessPoints.size() - 1].first - 1, lastSuccessPoints[lastSuccessPoints.size() - 1].second};
        break;
    case 2:
        lastPoint = { lastSuccessPoints[lastSuccessPoints.size() - 1].first, lastSuccessPoints[lastSuccessPoints.size() - 1].second + 1 };
        break;
    case 3:
        lastPoint = { lastSuccessPoints[lastSuccessPoints.size() - 1].first, lastSuccessPoints[lastSuccessPoints.size() - 1].second - 1 };
        break;
    }

    return lastPoint;
}

OptimalPlayer::OptimalPlayer()
{
    FillFieldRandom();
}


size_t Judge::GetPlayerDestroyed(bool isFirst)
{
    return isFirst ? player1destroyed : player2destroyed;
}

void Judge::IncPlayerDestroyed(bool isFirst)
{
    isFirst ? player1destroyed++ : player2destroyed++;
}

bool Judge::isGoodField(const int (&field)[10][10])
{
    size_t emptySquares = 0,
        countOne = 0,
        countTwo = 0,
        countThree = 0,
        countFour = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (field[i][j] == PLAYER_SHIP)
            {
                if (!(i - 1 >= 0 && field[i - 1][j] == PLAYER_SHIP) && !(j - 1 >= 0 && field[i][j - 1] == PLAYER_SHIP))
                {
                    size_t length = 1,
                        vectorY = 0,
                        vectorX = 0;
                    if (i + 1 < 10 && field[i + 1][j] == PLAYER_SHIP)
                        vectorY = 1;
                    else
                        vectorX = 1;
                    while (i + vectorY < 10 && j + vectorX < 10 && field[i + vectorY][j + vectorX] == PLAYER_SHIP)
                    {
                        length++;
                        vectorY ? vectorY++ : vectorX++;
                    }

                    if (length == 1)
                        countOne++;
                    else if (length == 2)
                        countTwo++;
                    else if (length == 3)
                        countThree++;
                    else if (length == 4)
                        countFour++;
                    else
                        return false;
                }
            }
            else
            {
                emptySquares++;
            }
        }
    }
    if (countOne == 4 && countTwo == 3 && countThree == 2 && countFour == 1 && emptySquares == (100 - 4 - 3 * 2 - 2 * 3 - 4))
        return true;

    return false;
}

bool Judge::isGoodStep(int x, int y, bool isFirst)
{
    if (x < 0 || y < 0 || x > 9 || y > 9)
        return false;
    

    if(FIELD[y][x] < 0 || FIELD[y][x] > 1)
        return false;

    return true;
}

int Judge::step(int x, int y, bool isFirst)
{
    if (FIELD[y][x] == EMPTY_FIELD)
    {
        FIELD[y][x] = MISSED;
        return MISSED;
    }
    if (FIELD[y][x] == PLAYER_SHIP)
    {
        
        FIELD[y][x] = DAMAGED;

        for (int i = 1; y - i > -1 && (isFirst ? field2 : field1)[y - i][x] > 0; i++)
        {
            if (FIELD[y - i][x] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; y + i < 10 && FIELD[y + i][x] > 0; i++)
        {
            if (FIELD[y + i][x] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; x - i > -1 && FIELD[y][x - i] > 0; i++)
        {
            if (FIELD[y][x - i] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; x + i < 10 && FIELD[y][x + i] > 0; i++)
        {
            if (FIELD[y][x + i] == PLAYER_SHIP)
                return DAMAGED;
        }

        int vectorY = 0,
            vectorX = 0;

        if (y - 1 >= 0 && FIELD[y - 1][x] == DAMAGED)
            vectorY = -1;
        else if (y + 1 < 10 && FIELD[y + 1][x] == DAMAGED)
            vectorY = 1;
        else if (x - 1 >= 0 && FIELD[y][x - 1] == DAMAGED)
            vectorX = -1;
        else if (x + 1 < 10 && FIELD[y][x + 1] == DAMAGED)
            vectorX = 1;
        
        do 
        {
            for (int i = -1; i < 2; i++)
            {
                if (y + i < 10 && y + i >= 0)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        if (x + j < 10 && x + j >= 0 && FIELD[y + i][x + j] == EMPTY_FIELD)
                        {
                            FIELD[y + i][x + j] = MISSED;
                        }
                    }
                }
            }
            y += vectorY;
            x += vectorX;
        } while ((vectorY != 0 || vectorX != 0) && y < 10 && x < 10 && y >= 0 && x >= 0 && FIELD[y][x] == DAMAGED);

        return DESTROYED;
    }
}

Judge::Judge(shared_ptr<Player> player1, shared_ptr<Player> player2)
{
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            field1[i][j] = player1->field[i][j];
            field2[i][j] = player2->field[i][j];
        }
    }

    if (!isGoodField(field1) || !isGoodField(field2))
        throw("Bad field");
}

void execute(int rounds, PlayerType firstType, PlayerType secondType)
{
    srand(time(NULL));
    int scoreFirst = 0;
    int scoreSecond = 0;
    for (size_t i = 0; i < rounds; i++)
    {
        shared_ptr<Player> first = Player::createPlayer(firstType);
        shared_ptr<Player> second = Player::createPlayer(secondType);

        Judge judge(first, second);

        bool motion = 1;
        while (judge.GetPlayerDestroyed(1) != 10 && judge.GetPlayerDestroyed(0) != 10)
        {
            Coord step;
            do
            {
                step = (motion ? first : second)->nextStep();
                if (!judge.isGoodStep(step.first, step.second, motion))
                {
                    (motion ? first : second)->SetSuccessOnLastStep(0);
                    continue;
                }
                break;
            } while (true);

            switch (judge.step(step.first, step.second, motion))
            {
            case MISSED:
                (motion ? first : second)->SetSuccessOnLastStep(0);
                (motion ? first : second)->SetDestroyShipOnLast(0);
                cout << (motion ? "First player missed" : "Second player missed") << endl;
                motion ? motion = false : motion = true;
                break;
            case DAMAGED:
                (motion ? first : second)->SetSuccessOnLastStep(1);
                (motion ? first : second)->SetDestroyShipOnLast(0);
                cout << (motion ? "First player damaged" : "Second player damaged") << endl;
                break;
            case DESTROYED:
                (motion ? first : second)->SetSuccessOnLastStep(1);
                (motion ? first : second)->SetDestroyShipOnLast(1);
                judge.IncPlayerDestroyed(motion);
                cout << (motion ? "First player destroyed" : "Second player destroyed") << endl;
                break;
            }
        }

        if (judge.GetPlayerDestroyed(1) == 10)
            scoreFirst++;
        else
            scoreSecond++;

        cout << "First player score: " << scoreFirst << endl;
        cout << "Second player score: " << scoreSecond << endl;
    }
    if (scoreFirst > scoreSecond)
        cout << "The First player wins";
    else if (scoreFirst < scoreSecond)
        cout << "The Second player wins";
    else
        cout << "Equal points";
}
