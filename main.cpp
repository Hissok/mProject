#include "tilemap.h"

int main()
{
    srand(std::time(0));
    sf::RenderWindow mainWindow(sf::VideoMode(640,320), "Fenetre de jeu");
    sf::Event event;
    mainWindow.setFramerateLimit(60);
    int tab[]{
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,
        1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
        1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1
    };

    ObjectArray objectArray;

    Player personnage;
    personnage.setPosition(sf::Vector2f(32,32));

    Tilemap map(tab,sf::Vector2u(32,32),20,10,objectArray.mapObject0,objectArray.mapChara0);
    const std::string path("tiles.png");

    if(!map.load(path))
        return 0;

    sf::Clock clock;
    sf::Time time;

    while(mainWindow.isOpen())
    {


        while(mainWindow.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed :
                mainWindow.close();
                break;

            default :
                break;
            }
        }




        if(personnage.wantMove())
        {
            if(map.noDetectCollision(&personnage))
            {
            switch (personnage.getDirection())
            {
            case UP : personnage.move(0,-personnage.getSpeed());
                break;

            case DOWN : personnage.move(0,personnage.getSpeed());
                break;

            case RIGHT : personnage.move(personnage.getSpeed(), 0);
                break;

            case LEFT :
                personnage.move(-personnage.getSpeed(),0);
                break;

            default : break;
            }
            }
            else if(map.isTileWall(&personnage))
            {
            int dx = personnage.getPosition().x;
            int dy = personnage.getPosition().y;
            std::cout << " PX : " << personnage.getPosition().x <<" , PY : " << personnage.getPosition().y << std::endl;
            switch(personnage.getDirection())
            {
            case UP :
                personnage.move(0,-dy%32);
                break;

            case DOWN : personnage.move(0,dy%32);
                break;

            case RIGHT : personnage.move(dx%32, 0);
                break;

            case LEFT :
                personnage.move(-dx%32,0);
                break;

            default : break;
            }

        }
        }


        mainWindow.clear(sf::Color::White);
        mainWindow.draw(map);        
        if(map.getOArraySize() > 0)
        {
            for(int i(0); i < map.getOArraySize(); ++i)
            {
                mainWindow.draw(*map.getObject(i));
            }
        }
        if(map.getCArraySize() > 0)
        {
            for(int i(0); i < map.getCArraySize(); ++i)
            {
                mainWindow.draw(*map.getCharacter(i));
            }
        }
        mainWindow.draw(personnage);    
        mainWindow.display();

        personnage.actualize(clock.getElapsedTime());
        clock.restart();


    }

    return 0;
}
