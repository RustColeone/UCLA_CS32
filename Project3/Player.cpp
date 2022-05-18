#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>

#include "utility.h"

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
    Point lastAttackedPoint;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
    : Player(nm, g), lastAttackedPoint(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if (!b.placeShip(Point(k, 0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (lastAttackedPoint.c > 0)
        lastAttackedPoint.c--;
    else
    {
        lastAttackedPoint.c = game().cols() - 1;
        if (lastAttackedPoint.r > 0)
            lastAttackedPoint.r--;
        else
            lastAttackedPoint.r = game().rows() - 1;
    }
    return lastAttackedPoint;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
    // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual bool isHuman()const;
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

    virtual ~HumanPlayer() {} //implement a v dtor.
private:
    Point lastAttackedPoint;
};
bool HumanPlayer::isHuman()const
{
    return true;
}

HumanPlayer::HumanPlayer(string nm, const Game& g)
    : Player(nm, g), lastAttackedPoint(0, 0)
{}

bool HumanPlayer::placeShips(Board& b)
{
    cout << name() << ", you need to place the " << game().nShips() << " ships of yours." << endl;
    for (int k = 0; k < game().nShips(); k++)
    {
        b.display(false);

        string enteredDirection;
        //cout<<cinDirection.size();
        Direction userDirection = VERTICAL;
        bool condition = true;
        while (true)
        {
            cout << "Direction must be h or v" << endl;
            cout << "Enter h for horizontal or v for vertical placement for your " 
                    << game().shipName(k) << " with size " << game().shipLength(k) << " blocks.";
            cin >> enteredDirection;
            if (enteredDirection[0] == 'v' && enteredDirection.size() == 1)
            {
                userDirection = VERTICAL;
                break;
            }
            if (enteredDirection[0] == 'h' && enteredDirection.size() == 1)
            {
                userDirection = HORIZONTAL;
                break;
            }
        }


        string userRow, userCol;
        int row = -1, col = -1;

        //cin>>coordinatesr;
        while (true)//not even an int
        {
            cout << "Where to place the ship (Row Column): ";
            cin >> userRow >> userCol;
            //stringstream myStreamr(coordinatesr);
            //stringstream myStreamc(coordinatesc);
            if (isNumber(userRow) && isNumber(userCol))
            {
                row = stoi(userRow);
                col = stoi(userCol);
                if (b.placeShip(Point(row, col), k, userDirection)) {
                    break;
                }
                else {
                    cout << "Looks like an Invalid Coordinate." << endl;
                    continue;
                }
            }
            cout << "You must enter two integers." << endl;
        }
    }
    b.display(false);

    return true;
}

Point HumanPlayer::recommendAttack() //returns a point
{

    string userRow, userCol;
    int row = -1, col = -1;
    while (true)
    {
        cout << "Where to place the ship (Row Column): ";
        cin >> userRow >> userCol;
        if (isNumber(userRow) && isNumber(userCol))
        {
            row = stoi(userRow);
            col = stoi(userCol);
            if (row > game().rows() || col > game().cols() || row < 0 || col < 0) {
                cout << "Looks like an Invalid Coordinate." << endl;
                continue;
            }
            else {
                break;
            }
        }
        cout << "You must enter two integers." << endl;
    }


    lastAttackedPoint.r = row;
    lastAttackedPoint.c = col;

    return lastAttackedPoint;
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    //Not Required
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
    //Not Required
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class MediocrePlayer : public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

    virtual ~MediocrePlayer() {} //implement a v dtor.
private:
    bool placementHelper(Board& b, int& numberOfShipsLeft, int shipID, int& count, int& numberofShipsPlaced);
    Point lastAttackedPoint;

    struct PointProperty {
        Point location;
        int maxLengthH;
        int maxLengthV;
    };
    struct ShipProperty {

        ShipProperty(int setId, Point loc, Direction dir) {
            id = setId;
            location = loc;
            direction = dir;
        }
        int id;
        Point location;
        Direction direction;
    };

    vector<ShipProperty> placedShip;

    vector<Point> attackedCells;
    vector<Point> queuedCells;
    Point PointofInterest;

    bool chooseRandomly;


};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
    : Player(nm, g), lastAttackedPoint(0, 0)
{
    chooseRandomly = true;
}

bool MediocrePlayer::placementHelper(Board& b, int& numberOfShipsLeft, int shipID, int& count, int& numberofShipsPlaced)
{
    //Terminating recursion:
    //Not enough space
    int areaBoard = game().rows() * game().cols();
    for (int i = 0; i < game().nShips(); i++)
        areaBoard -= game().shipLength(i);
    if (areaBoard < 0)
        return false;

    //When no ship to place always successful
    if (numberOfShipsLeft <= 0) {
        return true;
    }

    //same as above
    if (shipID < 0 || shipID >= game().nShips()) {
        return true;
    }

    //has done more than 50 times
    if (count > 50) {
        return false;
    }

    //All ships placed
    if (numberofShipsPlaced == game().nShips()) {
        count++;
        return true;
    }

    int longestPossibleShip = max(game().rows(), game().cols());
    bool placeSuccessful = false;
    bool subplaced = placementHelper(b, numberOfShipsLeft, shipID - 1, count, numberofShipsPlaced);

    bool placedVertical;
    bool placedHorizontal;

    //b.display(false);

    for (int r = 0; r < game().rows() && !placeSuccessful; r++) {
        for (int c = 0; c < game().cols() && !placeSuccessful; c++) {
            if (subplaced) {
                if (randInt(2) == 0) {
                    placedHorizontal = b.placeShip(Point(r, c), shipID, HORIZONTAL);
                    placedVertical = b.placeShip(Point(r, c), shipID, VERTICAL);
                }
                else {
                    placedVertical = b.placeShip(Point(r, c), shipID, VERTICAL);
                    placedHorizontal = b.placeShip(Point(r, c), shipID, HORIZONTAL);
                }
                if (placedVertical) {
                    placedShip.push_back(ShipProperty(shipID, Point(r, c), VERTICAL));
                    numberOfShipsLeft -= 1;
                    numberofShipsPlaced += 1;
                    placeSuccessful = true;
                }
                else if (placedHorizontal) {
                    placedShip.push_back(ShipProperty(shipID, Point(r, c), HORIZONTAL));
                    numberOfShipsLeft -= 1;
                    numberofShipsPlaced += 1;
                    placeSuccessful = true;
                }
            }
        }
    }
    if (!placeSuccessful) {
        //nowhere to place, that means we must delete everything and try again
        for (int i = placedShip.size() - 1; i >= 0; i--) {
            b.unplaceShip(placedShip[i].location, placedShip[i].id, placedShip[i].direction);
            placedShip.pop_back();
        }
        numberofShipsPlaced = 0;
        return false;
    }

    //if this is reached then this must be true;
    return true;
}

bool MediocrePlayer::placeShips(Board& b)   //i guess for debugging purposes, i can turn this player into a human to display his board better for me.
{
    for (int c = 0; c < 50; c++)
    {
        b.block();
        bool fiftyTries = false;
        int id = game().nShips() - 1;
        int numberofShipsLeft = game().nShips();
        int numberofShipsPlaced = 0;

        if (placementHelper(b, numberofShipsLeft, id, c, numberofShipsPlaced)) //if success then return true.
        {
            b.unblock();
            return true;
        }

        b.unblock();

        //backup plan
        int k = 0;
        for (int r = 0; r < game().rows(); r++) {
            for (int c = 0; c < game().rows(); c++) {
                if (randInt(2) == 0) {
                    if (b.placeShip(Point(r, c), k, HORIZONTAL)) {
                        k++; 
                    }

                }
                else {
                    if (b.placeShip(Point(k, 0), k, VERTICAL)) {
                        k++;
                    }

                }
                if (k >= game().nShips())//this means all placed
                    return true;
            }
        }
    }
    return false;

}

Point MediocrePlayer::recommendAttack() //returns a point
{
    if (chooseRandomly)
    {
        bool attackedBefore = true;
        while (attackedBefore) {
            lastAttackedPoint = game().randomPoint();
            if (attackedCells.size() == 0) {
                break;
            }
            for (int i = 0; i < attackedCells.size(); i++) {
                if (pointComparison(attackedCells[i], lastAttackedPoint)) {
                    break;
                }
                if (i == attackedCells.size() - 1) {
                    attackedBefore = false;
                }
            }
        }
    }
    else
    {
        if (queuedCells.size() > 0)
        {
            int randomPosition = randInt(queuedCells.size());
            lastAttackedPoint = queuedCells[randomPosition];
            queuedCells.erase(queuedCells.begin() + randomPosition);
        }
        else {
            chooseRandomly = true;
            return recommendAttack();
        }
    }
    return lastAttackedPoint;
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    attackedCells.push_back(p);
    bool shotFoundTarget = false;
    if (chooseRandomly)
    {
        if (shotHit && !shipDestroyed)
        {
            chooseRandomly = false;
            shotFoundTarget = true;
        }
    }
    if (!chooseRandomly)
    {
        if (shotFoundTarget)
        {
            for (int i = 0; i < queuedCells.size(); i++)
            {
                //empty queued cells before continue
                queuedCells.pop_back();
            }

            PointofInterest = p;
            for (int i = 1; i < 5; i++) {
                Point potentialPoint = Point(p.r + i, p.c);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r - i, p.c);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r, p.c + i);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r, p.c - i);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }
            }
        }
        if (queuedCells.size() == 0) {
            chooseRandomly = true;
        }

        if (shotHit && shipDestroyed) {
            chooseRandomly = true;
        }
    }


}

void MediocrePlayer::recordAttackByOpponent(Point /* p */)
{
    //Ignore
}

class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

    virtual ~GoodPlayer() {} //implement a v dtor.
private:
    bool placementHelper(Board& b, int& numberOfShipsLeft, int shipID, int& count, int& numberofShipsPlaced);
    Point lastAttackedPoint;

    struct PointProperty {
        Point location;
        int maxLengthH;
        int maxLengthV;
    };
    struct ShipProperty {

        ShipProperty(int setId, Point loc, Direction dir) {
            id = setId;
            location = loc;
            direction = dir;
        }
        int id;
        Point location;
        Direction direction;
    };

    vector<ShipProperty> placedShip;

    vector<Point> attackedCells;
    vector<Point> queuedCells;
    Point PointofInterest;

    bool chooseRandomly;

    bool wideSearch = true;


};

GoodPlayer::GoodPlayer(string nm, const Game& g)
    : Player(nm, g), lastAttackedPoint(0, 0)
{
    chooseRandomly = true;
}

bool GoodPlayer::placementHelper(Board& b, int& numberOfShipsLeft, int shipID, int& count, int& numberofShipsPlaced)
{
    //Terminating recursion:
    //Not enough space
    int areaBoard = game().rows() * game().cols();
    for (int i = 0; i < game().nShips(); i++)
        areaBoard -= game().shipLength(i);
    if (areaBoard < 0)
        return false;

    //When no ship to place always successful
    if (numberOfShipsLeft <= 0) {
        return true;
    }

    //same as above
    if (shipID < 0 || shipID >= game().nShips()) {
        return true;
    }

    //has done more than 50 times
    if (count > 50) {
        return false;
    }

    //All ships placed
    if (numberofShipsPlaced == game().nShips()) {
        count++;
        return true;
    }

    int longestPossibleShip = max(game().rows(), game().cols());
    bool placeSuccessful = false;
    bool subplaced = placementHelper(b, numberOfShipsLeft, shipID - 1, count, numberofShipsPlaced);

    bool placedVertical;
    bool placedHorizontal;

    //b.display(false);

    for (int r = 0; r < game().rows() && !placeSuccessful; r++) {
        for (int c = 0; c < game().cols() && !placeSuccessful; c++) {
            if (subplaced) {
                if (randInt(2) == 0) {
                    placedHorizontal = b.placeShip(Point(r, c), shipID, HORIZONTAL);
                    placedVertical = b.placeShip(Point(r, c), shipID, VERTICAL);
                }
                else {
                    placedVertical = b.placeShip(Point(r, c), shipID, VERTICAL);
                    placedHorizontal = b.placeShip(Point(r, c), shipID, HORIZONTAL);
                }
                if (placedVertical) {
                    placedShip.push_back(ShipProperty(shipID, Point(r, c), VERTICAL));
                    numberOfShipsLeft -= 1;
                    numberofShipsPlaced += 1;
                    placeSuccessful = true;
                }
                else if (placedHorizontal) {
                    placedShip.push_back(ShipProperty(shipID, Point(r, c), HORIZONTAL));
                    numberOfShipsLeft -= 1;
                    numberofShipsPlaced += 1;
                    placeSuccessful = true;
                }
            }
        }
    }
    if (!placeSuccessful) {
        //nowhere to place, that means we must delete everything and try again
        for (int i = placedShip.size() - 1; i >= 0; i--) {
            b.unplaceShip(placedShip[i].location, placedShip[i].id, placedShip[i].direction);
            placedShip.pop_back();
        }
        numberofShipsPlaced = 0;
        return false;
    }

    //if this is reached then this must be true;
    return true;
}

bool GoodPlayer::placeShips(Board& b)   //i guess for debugging purposes, i can turn this player into a human to display his board better for me.
{
    
    chooseRandomly = false;
    queuedCells.push_back(Point(0, 0));
    bool pointExisted = false;
    for (int r = 0; r < game().rows(); r += 4) {
        for (int c = 0; c < game().cols(); c += 4) {
            for (int i = 0; i < queuedCells.size(); i++) {
                pointExisted = pointExisted || pointComparison(queuedCells[i], Point(r, c));
            }
            if (pointExisted) {
                break;
            }
            if (game().isValid(Point(r, c))) {
                queuedCells.push_back(Point(r, c));
            }
        }
    }
    

    for (int c = 0; c < 50; c++)
    {
        b.block();
        bool fiftyTries = false;
        int id = game().nShips() - 1;
        int numberofShipsLeft = game().nShips();
        int numberofShipsPlaced = 0;

        if (placementHelper(b, numberofShipsLeft, id, c, numberofShipsPlaced)) //if success then return true.
        {
            b.unblock();
            return true;
        }

        b.unblock();

        //backup plan
        int k = 0;
        for (int r = 0; r < game().rows(); r++) {
            for (int c = 0; c < game().rows(); c++) {
                if (randInt(2) == 0) {
                    if (b.placeShip(Point(r, c), k, HORIZONTAL)) {
                        k++;
                    }

                }
                else {
                    if (b.placeShip(Point(k, 0), k, VERTICAL)) {
                        k++;
                    }

                }
                if (k >= game().nShips())//this means all placed
                    return true;
            }
        }
    }
    return false;

}

Point GoodPlayer::recommendAttack() //returns a point
{
    if (chooseRandomly)
    {
        bool attackedBefore = true;
        while (attackedBefore) {
            lastAttackedPoint = game().randomPoint();
            if (attackedCells.size() == 0) {
                break;
            }
            for (int i = 0; i < attackedCells.size(); i++) {
                if (pointComparison(attackedCells[i], lastAttackedPoint)) {
                    break;
                }
                if (i == attackedCells.size() - 1) {
                    if (lastAttackedPoint.r == 0 || attackedCells[i].c == 0) {
                        if(randInt(4) == 0) {
                            break;
                            //On edge, 25% chance of trying again
                            //because running around the edges is inefficient
                        }
                    }
                    attackedBefore = false;
                }
            }
        }
    }
    else
    {
        if (queuedCells.size() > 0)
        {
            int randomPosition = randInt(queuedCells.size());
            lastAttackedPoint = queuedCells[randomPosition];
            queuedCells.erase(queuedCells.begin() + randomPosition);
        }
        else {
            chooseRandomly = true;
            return recommendAttack();
        }
    }
    return lastAttackedPoint;
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    attackedCells.push_back(p);
    bool shotFoundTarget = false;
    if (chooseRandomly)
    {
        if (shotHit && !shipDestroyed)
        {
            chooseRandomly = false;
            shotFoundTarget = true;
        }
    }
    if (!chooseRandomly)
    {
        //if (shotFoundTarget)
        //{
        /*
        for (int i = 0; i < queuedCells.size(); i++)
        {
            //empty queued cells before continue
            queuedCells.pop_back();
        }*/
        if (shotHit) {
            if (wideSearch) {
                wideSearch = false;
                for (int i = 0; i < queuedCells.size(); i++)
                {
                    queuedCells.pop_back();
                }
            }
            PointofInterest = p;
            for (int i = 1; i < 2; i++) {//range of 4 is too big
                Point potentialPoint = Point(p.r + i, p.c);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r - i, p.c);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r, p.c + i);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }

                potentialPoint = Point(p.r, p.c - i);
                if (game().isValid(potentialPoint) && !containsPoint(attackedCells, potentialPoint)) {
                    queuedCells.push_back(potentialPoint);
                }
            }
        }
        if (queuedCells.size() == 0) {
            chooseRandomly = true;
        }
        //When we missed, remove them because it is unlikely that there's any more ships here
        /*
        if (!shotHit) {
            if (PointofInterest.r == p.r && PointofInterest.c == p.c) {
                for (int i = queuedCells.size() - 1; i >= 0; i--)
                {
                    if (p.r > PointofInterest.r) {
                        queuedCells.erase(queuedCells.begin() + i);
                    }
                    if (p.r < PointofInterest.r) {
                        queuedCells.erase(queuedCells.begin() + i);
                    }
                    if (p.c > PointofInterest.c) {
                        queuedCells.erase(queuedCells.begin() + i);
                    }
                    if (p.c < PointofInterest.c) {
                        queuedCells.erase(queuedCells.begin() + i);
                    }
                }
            }
        }*/
    }


}

void GoodPlayer::recordAttackByOpponent(Point /* p */)
{
    //Ignore
    //I have no idea how to use this
}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };

    int pos;
    for (pos = 0; pos != sizeof(types) / sizeof(types[0]) &&
        type != types[pos]; pos++)
        ;
    switch (pos)
    {
        case 0:  return new HumanPlayer(nm, g);
        case 1:  return new AwfulPlayer(nm, g);
        case 2:  return new MediocrePlayer(nm, g);
        case 3:  return new GoodPlayer(nm, g);
        default: return nullptr;
    }
}
