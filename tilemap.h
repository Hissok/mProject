#ifndef TILEMAP_H
#define TILEMAP_H

#include "personnage.h"

enum TileProperty;

static int charaCounter;

class Tilemap : public sf::Drawable, public sf::Transformable
{
   public :

    Tilemap(int * IntMap, sf::Vector2u tileSize, int width, int height, std::vector<Object *> &Ovect, std::vector<Personnage*> &Cvect);
    bool load(std::string const path);
    virtual ~Tilemap();
    void controlIntMap();
    void returnAll();
    TileProperty getProperty(int i) const;
    bool isTileWall(Personnage *mover);
    bool isPathFree(Personnage* mover);
    bool noDetectCollision(Personnage*mover);
    int getWidth() const;

    Object*& getObject(int i);
    size_t getOArraySize() const;

    Personnage*& getCharacter(int i);
    size_t getCArraySize() const;

private :

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    int* m_IntMap;
    TileProperty* m_TileProperties;

    sf::Texture m_tileset;
    sf::VertexArray m_vertices;

    int m_width;
    int m_height;


    sf::Vector2u m_tileSize;

    std::vector<Object*> m_objectVector;
    std::vector<Personnage*> m_charaVector;



};

class ObjectArray
{
public :
    std::vector<Object*> mapObject0;
    std::vector<Personnage*> mapChara0;

    ObjectArray();
    ~ObjectArray();
};


#endif // TILEMAP_H
