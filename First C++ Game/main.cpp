
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

sf::RenderWindow window(sf::VideoMode(576, 544), "pacman");
sf::Event event;

int tilesize = 32;
const int tiles[] =
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
        x = 256;
        y = 288;
        
        movespeed = 80.0 / tilesize;
        
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(move[UP] == false)
        {
            int nextX = x / 32;
            int nextY = (y / 32) - 1;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else if (move[UP] != true){
                move[DOWN] = false;
                move[LEFT] = false;
                move[RIGHT] = false;
                move[UP] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(move[DOWN] == false)
        {
            int nextX = x / 32;
            int nextY = (y / 32) + 1;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[LEFT] = false;
                move[RIGHT] = false;
                move[UP] = false;
                move[DOWN] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(move[LEFT] == false)
        {
            int nextX = (x / 32) - 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[RIGHT] = false;
                move[UP] = false;
                move[DOWN] = false;
                move[LEFT] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(move[RIGHT] == false)
        {
            nextspot = x + tilesize;
            
            int nextX = (x / 32) + 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                move[UP] = false;
                move[DOWN] = false;
                move[LEFT] = false;
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
            
            if (move[UP] == false) {
                y = nextspot;
            }
            
            nextspot = y - tilesize;
            y -= movespeed;

            int nextX = x / 32;
            int nextY = (y / 32) - 1;
            int nextTile = tiles[nextX + nextY * 18];
            
            if (nextTile != 0)
            {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }
        
        if(move[DOWN] == true)
        {
            nextspot = y + tilesize;
            y += movespeed;
            
            int nextX = x / 32;
            int nextY = (y / 32) + 1;
            int nextTile = tiles[nextX + nextY * 18];

            if(nextTile != 0)
            {
                walking = false;
                move[DOWN] = false;
            }
        }
        if(move[LEFT] == true)
        {
            nextspot = x - tilesize;
            x -= movespeed;
            
            int nextX = (x / 32) - 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];

            if(nextTile != 0)
            {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }
        if(move[RIGHT] == true)
        {
            nextspot = x + tilesize;
            x += movespeed;
            
            int nextX = (x / 32) + 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];
            
            if(nextTile != 0)
            {
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
    
    sf::RectangleShape rectangle;
    std::vector<sf::RectangleShape> dot(150, sf::RectangleShape(rectangle));
    
    // create the tilemap from the tiles definition
    TileMap map;
    if (!map.load(resourcePath() + "tileset.png", sf::Vector2u(32, 32), tiles, 18, 17)) {
        return -1;
    }
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int scoreInt = 0;
    
    // Create score text
    sf::Font arcadeFont;
    if (!arcadeFont.loadFromFile(resourcePath() + "ARCADECLASSIC.TTF")) {
        return EXIT_FAILURE;
    }
    sf::Text scoreText;
    scoreText.setFont(arcadeFont);
    scoreText.setString(std::to_string(scoreInt));
    scoreText.setCharacterSize(30);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(32, 0));
    
    sf::Text winText;
    winText.setFont(arcadeFont);
    winText.setString("Game Over! You Win!");
    winText.setCharacterSize(45);
    winText.setColor(sf::Color::White);
    sf::FloatRect textRect = winText.getLocalBounds();
    winText.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    winText.setPosition(sf::Vector2f(576/2.0f, 544/2.0f));
    
    int x = 1;
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 17; j++) {
            int tile = tiles[i + j * 18];
            
            sf::Vector2f point(i * 32 , j * 32);
            sf::Vector2f pacmanPosition(pacman.x, pacman.y);

            if (tile == 0 && point != pacmanPosition) {
                int xCord = i * 32;
                int yCord = j * 32;
                x++;
                
                dot[x].setSize(sf::Vector2f(10, 10));
                dot[x].setOrigin(sf::Vector2f(-10, -10));
                dot[x].setPosition(xCord, yCord);
                dot[x].setFillColor(sf::Color(212, 161, 144));
            }
        }
    }
    
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

        // draw dots to collect
        for(int i = 0; i < dot.size(); i++)
        {
            if (Collision::intersects(pacman.myrect.getGlobalBounds(), dot[i].getGlobalBounds())) {
                if (dot[i].getFillColor() != sf::Color::Transparent) {
                    scoreInt += 10;
                    scoreText.setString(std::to_string(scoreInt));
                }
                dot[i].setFillColor(sf::Color::Transparent);
            }
            
            window.draw(dot[i]);
        }
        
        // draw pacman
        window.draw(pacman.myrect);

        // draw text
        window.draw(scoreText);
        
        // draw winText if everything is collected
        if (scoreInt == 1350) {
            window.draw(winText);
        }
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}

