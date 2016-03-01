
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
#include "Monster.hpp"
#include "Pacman.hpp"

using namespace std;

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

int main()
{
    window.setVerticalSyncEnabled(true); // 60 fps

    Pacman pacman; // create pacman object
    pacman.setupTexturesAndAnimations();
    
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
    scoreText.setString(to_string(scoreInt));
    scoreText.setCharacterSize(30);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(32, 0));
    
    sf::Text winText;
    winText.setFont(arcadeFont);
    winText.setString("You Win!");
    winText.setCharacterSize(45);
    winText.setColor(sf::Color::White);
    sf::FloatRect textRect = winText.getLocalBounds();
    winText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    winText.setPosition(sf::Vector2f(576 / 2.0f, 544 / 2.0f));
    
    // create dots for pacman to eat
    sf::CircleShape circle;
    vector<sf::CircleShape> dot(150, sf::CircleShape(circle));
    
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
            int tile = tiles[i + j * 18];
            
            sf::Vector2f point(i * 32 , j * 32);
            sf::Vector2f pacmanPosition(pacman.getX(), pacman.getY());

            if (tile == 0 && point != pacmanPosition) {
                int xCord = i * 32;
                int yCord = j * 32;
                static int x = 1;
                
                x++;
                
                dot[x].setRadius(4);
                dot[x].setOrigin(sf::Vector2f(-10, -10));
                dot[x].setPosition(xCord, yCord);
                dot[x].setFillColor(sf::Color(212, 161, 144));
                
                if (dot[x].getPosition() == sf::Vector2f(32, 32) || dot[x].getPosition() == sf::Vector2f(32, 512) || dot[x].getPosition() == sf::Vector2f(512, 32)
                    || dot[x].getPosition() == sf::Vector2f(512, 512)) {
                    dot[x].setRadius(8);
                }
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
        pacman.movingAnimations();
        
        window.clear();
        
        // draw tilemap
        window.draw(map);

        // draw dots to collect
        for(int i = 0; i < dot.size(); i++)
        {
            if (Collision::intersects(pacman.getGlobalBounds(), dot[i].getGlobalBounds())) {
                if (dot[i].getFillColor() != sf::Color::Transparent) {
                    if (dot[i].getRadius() == 8) {
                        scoreInt += 50;
                    } else {
                        scoreInt += 10;
                    }

                    scoreText.setString(to_string(scoreInt));
                }
                dot[i].setFillColor(sf::Color::Transparent);
            }
            
            window.draw(dot[i]);
        }
        
        
        // draw pacman
        window.draw(pacman.getPacmanRect());

        // draw text
        window.draw(scoreText);
        
        // draw winText if everything is collected
        if (scoreInt == 1580) {
            window.draw(winText);
        }
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}

