#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
        Player(int health);
        virtual ~Player();

        void onHit();
    protected:
    private:
        int hp;
};

#endif // PLAYER_H
