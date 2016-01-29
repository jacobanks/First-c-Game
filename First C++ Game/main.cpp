
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
#include <math.h>

#include "AnimatedSprite.hpp"
#include "ResourcePath.hpp"
#include "TileMap.cpp"
#include "Collision.hpp"

sf::RenderWindow window(sf::VideoMode(576, 576), "pacman");
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
        
        for(int i = 0; i < 4; ++i) //initialize all move booleans to false
            move[i] = false;
        
        walking = false;
        myrect.setScale(sf::Vector2f(1, 1));
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
    
    AnimatedSprite myrect;
    Animation walkingAnimationDown;
    Animation walkingAnimationUp;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationCenter;

    Animation* currentAnimation = &walkingAnimationCenter;
    
    bool noKeyWasPressed = true;

};

void character::keymove()
{
    /*keymove() and moving() functions are working together */
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(move[UP] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0)
        {
            int nextX = x / 32;
            int nextY = (y / 32) - 1;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else if (move[UP] != true){
                nextspot = y - tilesize;

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
        if(move[DOWN] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0)
        {
            int nextX = x / 32;
            int nextY = (y / 32) + 1;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                nextspot = y + tilesize;

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
        if(move[LEFT] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0)
        {
            int nextX = (x / 32) - 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                nextspot = x - tilesize;

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
        if(move[RIGHT] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0)
        {
            int nextX = (x / 32) + 1;
            int nextY = y / 32;
            int nextTile = tiles[nextX + nextY * 18];

            if (nextTile != 0) { /* do nothing */ }
            else {
                nextspot = x + tilesize;

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
            y -= movespeed;
            currentAnimation = &walkingAnimationUp;
            noKeyWasPressed = false;
            
            if (y <= nextspot) {
                
                y = nextspot;
                nextspot = y - tilesize;
                
                int nextX = x / 32;
                int nextY = (y / 32) - 1;
                int nextTile = tiles[nextX + nextY * 18];
                
                if (nextTile != 0)
                {
                    walking = false;
                    move[UP] = false;
                }
            }
        }
        
        if(move[DOWN] == true)
        {
            y += movespeed;
            currentAnimation = &walkingAnimationDown;
            noKeyWasPressed = false;

            if (y >= nextspot) {
                
                y = nextspot;
                nextspot = y + tilesize;
                
                int nextX = x / 32;
                int nextY = (y / 32) + 1;
                int nextTile = tiles[nextX + nextY * 18];

                if(nextTile != 0)
                {
                    walking = false;
                    move[DOWN] = false;
                }
            }
        }
        
        if(move[LEFT] == true)
        {
            x -= movespeed;
            currentAnimation = &walkingAnimationLeft;
            noKeyWasPressed = false;

            if (x <= nextspot) {

                x = nextspot;
                nextspot = x - tilesize;
                
                int nextX = (x / 32) - 1;
                int nextY = y / 32;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0)
                {
                    walking = false;
                    move[LEFT] = false;
                }
            }
        }
        
        if(move[RIGHT] == true)
        {
            x += movespeed;
            currentAnimation = &walkingAnimationRight;
            noKeyWasPressed = false;

            if (x >= nextspot) {
                
                x = nextspot;
                nextspot = x + tilesize;
                
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
}

int main()
{
    window.setVerticalSyncEnabled(true); // 60 fps
    character pacman; // a squared pacman
    
    sf::Texture pacmanSheet;
    if (!pacmanSheet.loadFromFile(resourcePath() + "pacmanSheet.png")) {
        std::cout << "broken" << std::endl;
    }
    
    sf::Texture Pacmantexture;
    if (!Pacmantexture.loadFromFile(resourcePath() + "pacman.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }
    
    // set up the animations for all four directions (set spritesheet and push frames)
    pacman.walkingAnimationDown.setSpriteSheet(pacmanSheet);
    pacman.walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));
    pacman.walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    
    pacman.walkingAnimationCenter.setSpriteSheet(Pacmantexture);
    pacman.walkingAnimationCenter.addFrame(sf::IntRect(0, 0, 32, 32));
    
    pacman.walkingAnimationLeft.setSpriteSheet(pacmanSheet);
    pacman.walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));
    pacman.walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    
    pacman.walkingAnimationRight.setSpriteSheet(pacmanSheet);
    pacman.walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));
    pacman.walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    
    pacman.walkingAnimationUp.setSpriteSheet(pacmanSheet);
    pacman.walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
    pacman.walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    
    sf::Clock frameClock;
    
    // create the tilemap from the tiles definition
    TileMap map;
    if (!map.load(resourcePath() + "tileset.png", sf::Vector2u(32, 32), tiles, 18, 18)) {
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
    winText.setString("You Win!");
    winText.setCharacterSize(45);
    winText.setColor(sf::Color::White);
    sf::FloatRect textRect = winText.getLocalBounds();
    winText.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    winText.setPosition(sf::Vector2f(576/2.0f, 544/2.0f));
    
    sf::CircleShape circle;
    std::vector<sf::CircleShape> dot(150, sf::CircleShape(circle));
    
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
            int tile = tiles[i + j * 18];
            
            sf::Vector2f point(i * 32 , j * 32);
            sf::Vector2f pacmanPosition(pacman.x, pacman.y);

            if (tile == 0 && point != pacmanPosition) {
                int xCord = i * 32;
                int yCord = j * 32;
                static int x = 1;
                
                x++;
                
                dot[x].setRadius(4);
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
        
        
        sf::Time frameTime = frameClock.restart();
        
        pacman.myrect.play(*pacman.currentAnimation);
        
        // if no key was pressed stop the animation
        if (pacman.noKeyWasPressed)
        {
            pacman.myrect.stop();
        }
        pacman.noKeyWasPressed = true;
        
        // update AnimatedSprite
        pacman.myrect.update(frameTime);

        
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
        if (scoreInt == 1420) {
            window.draw(winText);
        }
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}

