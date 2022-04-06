#ifndef GAME
#define GAME

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Gark declaration.


class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

private:
    Mesa* m_mesa;
};

#endif GAME