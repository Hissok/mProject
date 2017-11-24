#ifndef PERSONNAGE_H
#define PERSONNAGE_H


#include "objects.h"
#include <cstdlib>
#include <ctime>


enum direction{DOWN = 0,LEFT = 1,RIGHT = 2,UP = 3};

class Personnage : public sf::Sprite
{
public :
    Personnage();
    Personnage(std::string name,float x, float y, std::string const path, int skin);
    virtual ~Personnage();
    std::string getName() const;
    std::string getID() const;
    int getSpeed() const;
    sf::Vector2i calculDestination() const;
    bool wantMove();
    void move(float offsetX, float offsetY);
    void actualize(sf::Time time);
    void setObstaclePosition(float px, float py);

    int getmID() const;
    std::string getmName() const;
    direction getDirection() const;
    int getInvSize() const;
    bool isHuman() const;
    bool isMoving() const;
    int getPvMax() const;
    int getPv() const;
    int getAtk() const;
    int getDef() const;
    bool isAlive() const;
    sf::FloatRect getObstaclePosition() const;

    void hurt(int damages);


    void setName(std::string &name);





protected :

    sf::Texture m_texture;

    std::string m_name;
    int m_speed;

    sf::Vector2u m_tileSize;
    direction m_direction;

    sf::FloatRect obstaclePosition;


    int m_anim;
    int m_ID;

    int m_pv;
    int m_pvMax;
    int m_atk;
    int m_def;

    int m_skin;

    bool human;
    bool m_movement;
    bool alive;

    sf::Time m_time;



};

class Player : public Personnage
{
public :
    Player();
    virtual ~Player();

    bool wantMove();

    void takeObject(Object* object, int nbObject);
    void clearInventory();
    int getInvSize() const;

private :
    std::vector<Object*> m_inventory;


};

#endif // PERSONNAGE_H
