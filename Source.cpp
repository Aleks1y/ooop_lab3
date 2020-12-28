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

    if (horizontal)
    {
        if (!(x >= 0 && x + length - 1 < 10) || !(y >= 0 && y <= 9))
            return false;
        else
            for (int i = 0; i < length; ++i)
            {
                if (field[y][x + i] == PLAYER_SHIP)
                    return false;
                if (x + i - 1 > -1 && field[y][x + i - 1] == PLAYER_SHIP)
                    return false;

                if (x + i + 1 < 10 && field[y][x + i + 1] == PLAYER_SHIP)
                    return false;

                if (x + i - 1 > -1 && y - 1 > -1 && field[y - 1][x + i - 1] == PLAYER_SHIP)
                    return false;

                if (x + i - 1 > -1 && y + 1 < 10 && field[y + 1][x + i - 1] == PLAYER_SHIP)
                    return false;

                if (x + i + 1 < 10 && y - 1 > -1 && field[y - 1][x + i + 1] == PLAYER_SHIP)
                    return false;

                if (y + i + 1 < 10 && field[y + 1][x + i] == PLAYER_SHIP)
                    return false;

                if (y - 1 > -1 && field[y - 1][x + i] == PLAYER_SHIP)
                    return false;

                if (x + i + 1 < 10 && y + 1 < 10 && field[y + 1][x + i + 1] == PLAYER_SHIP)
                    return false;
            }
    }
    else
    {
        if (!(y >= 0 && y + length - 1 < 10) || !(x >= 0 && x <= 9))
            return false;
        else
            for (int i = 0; i < length; ++i)
            {
                if (field[y + i][x] > 0)
                    return false;
                if (x - 1 > -1 && field[y + i][x - 1] == PLAYER_SHIP)
                    return false;

                if (x + 1 < 10 && field[y + i][x + 1] == PLAYER_SHIP)
                    return false;

                if (x - 1 > -1 && y + i - 1 > -1 && field[y + i - 1][x - 1] == PLAYER_SHIP)
                    return false;

                if (x - 1 > -1 && y + i + 1 < 10 && field[y + i + 1][x - 1] == PLAYER_SHIP)
                    return false;

                if (x + 1 < 10 && y + i - 1 > -1 && field[y + i - 1][x + 1] == PLAYER_SHIP)
                    return false;

                if (y + i + 1 < 10 && field[y + i + 1][x] == PLAYER_SHIP)
                    return false;

                if (y + i - 1 > -1 && field[y + i - 1][x] == PLAYER_SHIP)
                    return false;

                if (x + 1 < 10 && y + i + 1 < 10 && field[y + i + 1][x + 1] == PLAYER_SHIP)
                    return false;
            }
    }
    return true;
}

Player* Player::createPlayer(PlayerType type)
{
    switch (type)
    {
    case Random:
        return new RandomPlayer();
    case Optional:
        return new OptionalPlayer();
    case Interactive:
        return new ConsolePlayer();
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
            cout << "Enter information about №" << i << "three decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::three));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::three);
    }
    for (int i = 0; i < 3; ++i)
    {
        do
        {
            cout << "Enter information about  №" << i << "two decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::two));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::two);
    }
    for (int i = 0; i < 4; ++i)
    {
        do
        {
            cout << "Enter information about  №" << i << "one decked ship (int x, int y, bool ishorizontal)";
            cin >> x >> y >> ishorizontal;
        } while (!isGoodShip(x - 1, y - 1, ishorizontal, ShipType::one));
        SetShip(x - 1, y - 1, ishorizontal, ShipType::one);
    }
}

pair<int, int> ConsolePlayer::nextStep()
{
    cout << "Enter int x int y" << endl;

    int x, y;
    cin >> x >> y;
    return make_pair(x - 1, y - 1);
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

pair<int, int> RandomPlayer::nextStep()
{
    int x = rand() % 10;
    int y = rand() % 10;

    return make_pair(x, y);
}

RandomPlayer::RandomPlayer()
{
    FillFieldRandom();
}

pair<int, int> OptionalPlayer::strategyFire()
{
    if (diag0 < 10)
    {
        lastPoint = make_pair(diag0, diag0);
        diag0++;
        return lastPoint;
    }
    else if (diag1 < 10)
    {
        lastPoint = make_pair(9 - diag1, diag1);
        diag1++;
        return lastPoint;
    }
    else if (diag2 < 10)
    {
        lastPoint = make_pair(4, diag2);
        diag2++;
        return lastPoint;
    }
    else if (diag3 < 10)
    {
        lastPoint = make_pair(diag3, 5);
        diag3++;
        return lastPoint;
    }
    else
    {
        lastPoint = make_pair(rand() % 10, rand() % 10);
        return lastPoint;
    }
}

pair<int, int> OptionalPlayer::nextStep()
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
        lastPoint = make_pair(lastSuccessPoints[lastSuccessPoints.size() - 1].first + 1, lastSuccessPoints[lastSuccessPoints.size() - 1].second);
        break;
    case 1:
        lastPoint = make_pair(lastSuccessPoints[lastSuccessPoints.size() - 1].first - 1, lastSuccessPoints[lastSuccessPoints.size() - 1].second);
        break;
    case 2:
        lastPoint = make_pair(lastSuccessPoints[lastSuccessPoints.size() - 1].first, lastSuccessPoints[lastSuccessPoints.size() - 1].second + 1);
        break;
    case 3:
        lastPoint = make_pair(lastSuccessPoints[lastSuccessPoints.size() - 1].first, lastSuccessPoints[lastSuccessPoints.size() - 1].second - 1);
        break;
    }

    return lastPoint;
}

OptionalPlayer::OptionalPlayer()
{
    FillFieldRandom();
}

bool Judge::isGoodStep(int x, int y, Player* player)
{
    if (x < 0 || y < 0 || x > 9 || y > 9)
        return false;
    

    if(player->field[y][x] < 0 || player->field[y][x] > 1)
        return false;

    return true;
}

int Judge::step(int x, int y, Player* player)
{
    if (player->field[y][x] == EMPTY_FIELD)
    {
        player->field[y][x] = MISSED;
        return MISSED;
    }
    if (player->field[y][x] == PLAYER_SHIP)
    {
        
        player->field[y][x] = DAMAGED;

        for (int i = 1; y - i > -1 && player->field[y - i][x] > 0; i++)
        {
            if (player->field[y - i][x] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; y + i < 10 && player->field[y + i][x] > 0; i++)
        {
            if (player->field[y + i][x] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; x - i > -1 && player->field[y][x - i] > 0; i++)
        {
            if (player->field[y][x - i] == PLAYER_SHIP)
                return DAMAGED;
        }

        for (int i = 1; x + i < 10 && player->field[y][x + i] > 0; i++)
        {
            if (player->field[y][x + i] == PLAYER_SHIP)
                return DAMAGED;
        }

        int vectorY = 0,
            vectorX = 0;

        if (y - 1 >= 0 && player->field[y - 1][x] == DAMAGED)
            vectorY = -1;
        else if (y + 1 < 10 && player->field[y + 1][x] == DAMAGED)
            vectorY = 1;
        else if (x - 1 >= 0 && player->field[y][x - 1] == DAMAGED)
            vectorX = -1;
        else if (x + 1 < 10 && player->field[y][x + 1] == DAMAGED)
            vectorX = 1;
        
        do 
        {
            for (int i = -1; i < 2; i++)
            {
                if (y + i < 10 && y + i >= 0)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        if (x + j < 10 && x + j >= 0 && player->field[y + i][x + j] == EMPTY_FIELD)
                        {
                            player->field[y + i][x + j] = MISSED;
                        }
                    }
                }
            }
            y += vectorY;
            x += vectorX;
        } while ((vectorY != 0 || vectorX != 0) && y < 10 && x < 10 && y >= 0 && x >= 0 && player->field[y][x] == DAMAGED);

        return DESTROYED;
    }
}

void execute(int rounds, PlayerType firstType, PlayerType secondType)
{
    srand(time(NULL));
    int scoreFirst = 0;
    int scoreSecond = 0;
    for (size_t i = 0; i < rounds; i++)
    {
        Player* first = Player::createPlayer(firstType);
        Player* second = Player::createPlayer(secondType);

        Judge judge;

        bool motion = 1;
        while (judge.player1destroyed != 10 && judge.player2destroyed != 10)
        {
            pair<int, int> step;
            do
            {
                step = (motion ? first : second)->nextStep();
                if (!judge.isGoodStep(step.first, step.second, (motion ? second : first)))
                {
                    (motion ? first : second)->successOnLastStep = 0;
                    continue;
                }
                break;
            } while (true);

            switch (judge.step(step.first, step.second, (motion ? second : first)))
            {
            case MISSED:
                (motion ? first : second)->successOnLastStep = 0;
                (motion ? first : second)->destroyShipOnLast = 0;
                cout << (motion ? "First player missed" : "Second player missed") << endl;
                motion ? motion = false : motion = true;
                break;
            case DAMAGED:
                (motion ? first : second)->successOnLastStep = 1;
                (motion ? first : second)->destroyShipOnLast = 0;
                cout << (motion ? "First player damaged" : "Second player damaged") << endl;
                break;
            case DESTROYED:
                (motion ? first : second)->successOnLastStep = 1;
                (motion ? first : second)->destroyShipOnLast = 1;
                motion ? judge.player1destroyed++ : judge.player2destroyed++;
                cout << (motion ? "First player destroyed" : "Second player destroyed") << endl;
                break;
            }
        }

        if (judge.player1destroyed == 10)
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
