#include "objects.h"



Object::Object(std::string name,int stack, sf::Vector2f skinEmplacement) : m_name(name),m_stack(stack),
     m_use(HEAL), sf::Sprite()
{
    sf::Image img;
    img.loadFromFile("objets.png");
    img.createMaskFromColor(sf::Color(img.getPixel(0,0)));
    m_texture.loadFromImage(img,sf::IntRect(skinEmplacement.x*32,skinEmplacement.y*32,32,32));
    setTexture(m_texture);
    if(m_stack > 99)
    {
        m_stack = 99;
    }

}

Object::~Object()
{

}


int Object::getStack() const
{
    return m_stack;
}

use Object::getUse() const
{
    return m_use;
}
std::string Object::getmName() const
{
    return m_name;
}

void Object::upStack(int i)
{
    if(m_stack + i > 99 )
        m_stack = 99;
    else
        m_stack += i;

}
