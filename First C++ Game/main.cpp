
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "ResourcePath.hpp"
#include "TileMap.cpp"
#include "Collision.hpp"

sf::RenderWindow window(sf::VideoMode(576, 544),"title");
sf::Event event;

int tilesize = 32;
const int level[] =
{
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0,10, 0, 1, 2, 0,10, 0, 1, 2, 0,10, 0, 1, 2, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0,11, 0, 4, 3, 0,11, 0, 4, 3, 0,11, 0, 4, 3, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 0,10, 0, 1, 2, 0,10, 0, 1, 2, 0,10, 0, 1, 2, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 0, 9,
    9, 0,11, 0, 4, 3, 0,11, 0, 4, 3, 0,11, 0, 4, 3, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
};

class character
{
public:
    character()
    {
        x = 32;
        y = 32;
        
        // in this case, every loop, it will walk 2 pixels.
        //if u put 50 as movespeed, it will walk 1 pixel each loop
        movespeed = 50.0 / tilesize;
        
        for(int i = 0; i < 4; ++i) //initialize the all move booleans to false
            move[i] = false;
        
        walking = false;
        myrect.setSize(sf::Vector2f(32, 32));
    }
    
    void keymove(); //keypress detection
    void moving(); //moving if "walking" boolean is true
    
    float x;
    float y;
    float movespeed; //sets the movespeed
    
    enum MOVE {UP,DOWN,LEFT,RIGHT}; //enums instead of remember numbers
    bool move[4]; //deciding if u move up/down/left/right
    bool walking;
    int nextspot; //the next tilespot of the map
    
    sf::RectangleShape myrect;
};

void character::keymove()
{
    /*keymove() and moving() functions are working together*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(walking == false)
        {
            /*if you click up, the the nextspot will of course be 32
             pixels above yourself, so thats why nextspot = y - tilsize*/
            nextspot = y - tilesize;
            
            int nextX = x / 32;
            int nextY = (y / 32) - 1;
            int nextTile = level[nextX + nextY * 18];
            std::cout << nextTile << std::endl;

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[UP] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(walking == false)
        {
            nextspot = y + tilesize;
            
            int nextX = x / 32;
            int nextY = (y / 32) + 1;
            int nextTile = level[nextX + nextY * 18];
            std::cout << nextTile << std::endl;

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[DOWN] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(walking == false)
        {
            nextspot = x - tilesize;
            
            int nextX = (x / 32) - 1;
            int nextY = y / 32;
            int nextTile = level[nextX + nextY * 18];
            std::cout << nextTile << std::endl;

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[LEFT] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(walking == false)
        {
            nextspot = x + tilesize;
            
            int nextX = (x / 32) + 1;
            int nextY = y / 32;
            int nextTile = level[nextX + nextY * 18];
            std::cout << nextTile << std::endl;

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[RIGHT] = true;
                walking = true;
            }

        }
    }
}
void character::moving()
{
    if(walking == true)
    {
        if(move[UP] == true)
        {
            y -= movespeed;
            
            /* i do <= and not just == because maybe your movespeed has a
             decimalpoint and then it wont become the same number as nextspot*/
            if(y <= nextspot)
            {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }
        
        if(move[DOWN] == true)
        {
            y += movespeed;
            if(y >= nextspot)
            {
                y = nextspot;
                walking = false;
                move[DOWN] = false;
            }
        }
        if(move[LEFT] == true)
        {
            x -= movespeed;
            if(x <= nextspot)
            {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }
        if(move[RIGHT] == true)
        {
            x += movespeed;
            if(x >= nextspot)
            {
                x = nextspot;
                walking = false;
                move[RIGHT] = false;
            }
        }
    }
}
int main()
{
    window.setVerticalSyncEnabled(true); // 60 fps
    character pacman; // a squared pacman
    pacman.myrect.setFillColor(sf::Color(255,255,0));
    
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(resourcePath() + "tileset.png", sf::Vector2u(32, 32), level, 18, 17)) {
        return -1;
    }
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        
        pacman.keymove();
        pacman.moving();
        pacman.myrect.setPosition(pacman.x, pacman.y);
        
        window.clear();
        
        // draw tilemap
        window.draw(map);

        // draw pacman
        window.draw(pacman.myrect);
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}

