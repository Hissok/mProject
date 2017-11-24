#include "tilemap.h"

enum TileProperty {FREE, OBSTACLE, OCCUPED};


Tilemap::Tilemap(int *IntMap, sf::Vector2u tileSize, int  width, int height, std::vector<Object*> &Ovect, std::vector<Personnage *> &Cvect) : sf::Drawable() , sf::Transformable(),
    m_IntMap(IntMap), m_tileSize(tileSize), m_width(width), m_height(height)
{
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width*height*4);
    m_TileProperties = new TileProperty[width*height];

    for(int i(0); i < Ovect.size(); ++i)
    {
        m_objectVector.push_back(Ovect[i]);
    }

    for(int i(0); i < Cvect.size(); ++i)
    {
        m_charaVector.push_back(Cvect[i]);
    }


}

Tilemap::~Tilemap()
{
    delete[] m_TileProperties;

}

bool Tilemap::load(const std::string path)
{
    if(!m_tileset.loadFromFile(path))
        return false;


    for(int i(0); i < m_width; ++i)
    {
        for(int j(0); j < m_height; ++j)
        {
            sf::Vertex* quad = &m_vertices[(i+j*m_width)*4];

            int tileNumber = m_IntMap[i+j*m_width];

            int tx = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
            int ty = tileNumber / (m_tileset.getSize().x / m_tileSize.x);



            quad[0].position = sf::Vector2f(i*m_tileSize.x, j*m_tileSize.y);
            quad[1].position = sf::Vector2f((i+1)* m_tileSize.x, j*m_tileSize.y);
            quad[2].position = sf::Vector2f((i+1)* m_tileSize.x , (j+1)*m_tileSize.y);
            quad[3].position = sf::Vector2f(i*m_tileSize.x, (j+1)* m_tileSize.y);

            quad[0].texCoords = sf::Vector2f(tx*m_tileSize.x, ty*m_tileSize.y);
            quad[1].texCoords = sf::Vector2f((tx+1)* m_tileSize.x, ty*m_tileSize.y);
            quad[2].texCoords = sf::Vector2f((tx+1)* m_tileSize.x , (ty+1)*m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(tx*m_tileSize.x, (ty+1)* m_tileSize.y);

            switch(tileNumber)
            {
            case 0 :
                m_TileProperties[i+j*m_width] = FREE;
                break;

            default :
                m_TileProperties[i+j*m_width] = OBSTACLE;
                break;
            }
        }
    }

    return true;
}
void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

void Tilemap::returnAll()
{
    std::cout << "largeur = " << m_width << std::endl;
    std::cout << "hauteur = " << m_height << std::endl << std::endl;

    std::cout << "Taille X du tileset : " << m_tileset.getSize().x << std::endl;
    std::cout << "Taille Y du tileset : " << m_tileset.getSize().y << std::endl << std::endl;

}

void Tilemap::controlIntMap()
{
    for(int i (0); i < m_width*m_height; ++i)
    {
        std::cout <<i << std::endl;
        std::cout << m_IntMap[i] << std::endl;
    }
}

TileProperty Tilemap::getProperty(int i) const
{
    return m_TileProperties[i];
}

bool Tilemap::isTileWall(Personnage* mover)
{
    sf::Vector2i destination = mover->calculDestination();

    if(destination.x < 0 || destination.y < 0 || destination.x > m_width*m_tileSize.x || destination.y > m_height*m_tileSize.x)
        return true;

    int destinationTile = (destination.x/m_tileSize.x) + (destination.y/m_tileSize.y*m_width);
    int posX = mover->getPosition().x;
    int posY = mover->getPosition().y;



    switch(mover->getDirection())
    {
    case DOWN :
    case UP :
        if(posX % 32 == 0)
            return !m_TileProperties[destinationTile] == FREE;


        else
        {


            return (!m_TileProperties[destinationTile] == FREE || !m_TileProperties[destinationTile+1] == FREE);

        }
        break;

    case LEFT :
    case RIGHT :
        if(posY % 32 == 0)
            return !m_TileProperties[destinationTile] == FREE;

        else
        {
            return (!m_TileProperties[destinationTile] == FREE || !m_TileProperties[destinationTile+m_width] == FREE);
        }
        break;

    default : break;


    }
    return true;






}

int Tilemap::getWidth() const
{
    return m_width;
}
Object*& Tilemap::getObject(int i)
{
    return m_objectVector[i];
}

size_t Tilemap::getOArraySize() const
{
    return m_objectVector.size();
}
Personnage*& Tilemap::getCharacter(int i)
{
    return m_charaVector[i];
}

size_t Tilemap::getCArraySize() const
{
    return m_charaVector.size();
}

bool Tilemap::isPathFree(Personnage* mover)
{
    sf::FloatRect destRect(mover->calculDestination().x, mover->calculDestination().y, 32,32);
    for(int i(0); i < m_charaVector.size(); ++i)
    {
        if(destRect.intersects(m_charaVector[i]->getGlobalBounds()))
            if(mover != m_charaVector[i])
            {
                mover->setObstaclePosition(m_charaVector[i]->getPosition().x,m_charaVector[i]->getPosition().y);
                return false;

            }

    }
    return true;
}

bool Tilemap::noDetectCollision(Personnage* mover)
{
    return isPathFree(mover) && !isTileWall(mover);
}


//______________________________________________________________________________________

ObjectArray::ObjectArray()
{
    mapObject0.push_back(new Object("Potion",5,sf::Vector2f(0,0)));
    mapObject0.push_back(new Object("Potion",5,sf::Vector2f(0,0)));
    mapObject0[0]->setPosition(224,256);
    mapObject0[1]->setPosition(64,32);

    mapChara0.push_back(new Personnage());
    mapChara0.push_back(new Personnage());
    mapChara0[0]->setPosition(96,96);
    mapChara0[1]->setPosition(96,64);

}

ObjectArray::~ObjectArray()
{
    for(int i(0); i < mapChara0.size(); ++i)
    {
        delete mapChara0.back();
        mapChara0.pop_back();
    }

    for(int i(0); i < mapObject0.size(); ++i)
    {
        delete mapObject0.back();
        mapObject0.pop_back();
    }
}
