#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

enum use {HEAL, UPMANA};
class Object : public sf::Sprite
{
public:
    Object(std::string name, int stack, sf::Vector2f skinEmplacement);
    virtual ~Object();

    int getStack() const;
    use getUse() const;
    std::string getmName() const;

    void upStack(int i);

protected :
    std::string m_name;
    sf::Texture m_texture;
    int m_stack;
    use m_use;

};

#endif // OBJECTS_H
