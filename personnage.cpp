#include "personnage.h"



static int charaCounter(0);

Personnage::Personnage() : sf::Sprite(), m_name("Villageois"), m_speed(1), m_tileSize(sf::Vector2u(32,32)), m_direction(DOWN),m_anim(0),m_skin(0),
    m_time(sf::seconds(0)), m_ID(charaCounter), human(false), m_pvMax(100), m_pv(m_pvMax), m_atk(10), m_def(4), alive(true), obstaclePosition(sf::FloatRect(0,0,m_tileSize.x,m_tileSize.y))
{

    ++charaCounter;
    sf::Image image;
    if(image.loadFromFile("persos2.png"))
    {
        image.createMaskFromColor(sf::Color(image.getPixel(0,0)));
        m_texture.loadFromImage(image);

    }

    setTexture(m_texture);
    setTextureRect(sf::IntRect(0,0,m_tileSize.x,m_tileSize.y));


}
Personnage::Personnage(std::string name, float x, float y, std::string const path, int skin) : sf::Sprite(), m_name(name), m_speed(1), m_tileSize(sf::Vector2u(32,32)), m_direction(DOWN),m_anim(0),
    m_time(sf::seconds(0)), m_ID(charaCounter), m_skin(skin)
{

    ++charaCounter;
    sf::Image image;
    if(image.loadFromFile(path))
    {
        image.createMaskFromColor(sf::Color(image.getPixel(0,0)));
        m_texture.loadFromImage(image);

    }


    setTexture(m_texture);
    setTextureRect(sf::IntRect(x,y,m_tileSize.x*skin,m_tileSize.y));


}
Personnage::~Personnage()
{

}




sf::Vector2i Personnage::calculDestination() const
{
    switch (m_direction)
    {
    case DOWN :
        return sf::Vector2i (getPosition().x, getPosition().y + m_tileSize.y );
        break;

    case LEFT :
        return sf::Vector2i(getPosition().x - m_speed, getPosition().y);
        break;

    case RIGHT :
        return sf::Vector2i(getPosition().x  + m_tileSize.x, getPosition().y);
        break;

    case UP :
        return sf::Vector2i(getPosition().x , getPosition().y - m_speed);
        break;

    default :
        return sf::Vector2i(getPosition().x,getPosition().y);
        break;

    }
}
bool Personnage::wantMove()
{
    int aleaRotation(rand()%4);
    switch (aleaRotation)
    {
    case 0 :
        m_direction = DOWN;
        return true;
        break;

    case 1 :
        m_direction = LEFT;
        return true;
        break;

    case 2 :
        m_direction = RIGHT;
        return true;
        break;

    case 3 :
        m_direction = UP;
        return true;
        break;

    default :
        return false;
        break;
    }
}
void Personnage::move(float offsetX, float offsetY)
{

    if(m_time.asSeconds() >= 0.20)
    {
        if(m_anim < 2)
            ++m_anim;
        else
            m_anim = 0;



        m_time = sf::seconds(0);
    }

    setTextureRect(sf::IntRect(m_anim*(m_tileSize.x*m_skin), (m_tileSize.x*m_skin)*m_direction,m_tileSize.x,m_tileSize.y));


    setPosition(sf::Vector2f(getPosition().x + offsetX,getPosition().y + offsetY));

}

void Personnage::setObstaclePosition(float px, float py)
{
    obstaclePosition.top = px;
    obstaclePosition.left = py;
}

sf::FloatRect Personnage::getObstaclePosition() const
{
    return obstaclePosition;
}


int Personnage::getSpeed() const
{
    return m_speed;
}
int Personnage::getmID() const
{
    return m_ID;
}
std::string Personnage::getmName() const
{
    return m_name;
}
direction Personnage::getDirection() const
{
    return m_direction;
}




void Personnage::actualize(sf::Time time)
{
    m_time += time;
}
void Personnage::setName(std::string& name)
{
    m_name = name;
}



bool Personnage::isHuman() const
{
    return human;
}

bool Personnage::isMoving() const
{
    return m_movement;
}

int Personnage::getPv() const
{
    return m_pv;
}

int Personnage::getPvMax() const
{
    return m_pvMax;
}

int Personnage::getAtk() const
{
    return m_atk;
}

int Personnage::getDef() const
{
    return m_def;
}

bool Personnage::isAlive() const
{
    return alive;
}

void Personnage::hurt(int damages)
{
    if(damages >= m_pv)
    {
        m_pv = 0;
        alive = false;
    }
    else
        m_pv -= damages;
}

//______________________________________________________________________________________

Player::Player() : Personnage("",0,0,"persos2.png",1),m_inventory()
{
    human = true;
}

Player::~Player()
{
    while(!m_inventory.empty())
    {
        delete m_inventory.back();
        m_inventory.pop_back();
    }
}

void Player::takeObject(Object* object, int nbObject)
{
    int ramass = nbObject;

    if(m_inventory.empty())
    {
        m_inventory.push_back(new Object(*object));
        std::cout << "Vous ramassez " << ramass << " " << object->getmName() <<std::endl;
        delete object;
    }
    else
    {
        int sameSlot(0);
        for(int i(0); i < m_inventory.size(); ++i)
        {
            if(m_inventory[i]->getmName() == object->getmName())
                ++sameSlot;
        }

        int slotCounter(0);
        while(slotCounter < sameSlot && object->getStack() > 0)
        {
            for(int i(0); i < m_inventory.size(); ++i)
            {
                if(m_inventory[i]->getmName() == object->getmName())
                {
                    if(m_inventory[i]->getStack() + object->getStack() <= 99)
                    {
                        m_inventory[i]->upStack(object->getStack());
                        object->upStack(object->getStack()*-1);
                    }
                    else if(m_inventory[i]->getStack() < 99)
                    {
                        int stackable(99 - m_inventory[i]->getStack());
                        if (stackable > object->getStack())
                            stackable = object->getStack();

                        m_inventory[i]->upStack(stackable);
                        object->upStack(-stackable);

                    }
                    else if(m_inventory[i]->getStack() == 99)
                        ++slotCounter;
                }
            }

            if(slotCounter < sameSlot)
                slotCounter = 0;
        }

        if(object->getStack() > 0)
            m_inventory.push_back(new Object(*object));

        std::cout << "Vous ramassez " << ramass << " " << object->getmName() <<std::endl;
        delete object;
    }

}

void Player::clearInventory()
{
    for(int i(0);i < m_inventory.size(); ++i)
    {
        if(m_inventory[i]->getStack() <= 0)
        {
            delete m_inventory[i];
            m_inventory.erase(m_inventory.begin()+i);
        }
    }
}

bool Player::wantMove()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        m_speed = 2;
    else
        m_speed = 1;


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_direction = DOWN;
            return true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_direction = UP;
            return true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_direction = LEFT;
            return true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_direction = RIGHT;
            return true;
        }
        else return false;

}

int Player::getInvSize() const
{
    return m_inventory.size();
}
