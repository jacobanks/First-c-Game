
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

using namespace std;

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(576, 544), "My window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
    
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(resourcePath() + "tileset.png", sf::Vector2u(32, 32), level, 18, 17)) {
        return -1;
    }
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "sprite.png", sf::IntRect(30, 30, 30, 30))) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    int tileX = -8;
    int tileY = -4;
    sprite.setOrigin(tileX, tileY);
    
    sf::Sprite sprite2(texture);
    sprite2.setOrigin(sf::Vector2f(-256, -158));
    sprite2.setColor(sf::Color(255, 0, 0));
    
    // Create a graphical text to display
    sf::Font sansationFont;
    if (!sansationFont.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("First c++ Game", sansationFont, 30);
    text.setColor(sf::Color::White);

    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
//        return EXIT_FAILURE;
//    }

    // Play the music
//    music.play();
    
    window.setFramerateLimit(60);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
//                window.close();
//            }
        }
        
        // move player on button click
        switch (event.key.code) {
            case sf::Keyboard::Left:
                tileX -= 1;
                break;
            case sf::Keyboard::Right:
                tileX += 1;
                break;
            case sf::Keyboard::Down:
                tileY += 1;
                break;
            case sf::Keyboard::Up:
                tileY -= 1;
                break;
            default:
                break;
        }
        sprite.setPosition(tileX * 16, tileY * 16);

        
        int tileUnderPlayer = level[tileX + tileY * 16];
        cout << tileUnderPlayer << endl;
        
        // check if player hit another sprite
        if (Collision::BoundingBoxTest(sprite, sprite2)) {
            cout << "collided with another sprite" << endl;
        }

        // Clear screen
        window.clear();

        //Draw the map
        window.draw(map);

        // Draw the sprite
        window.draw(sprite);
        
        window.draw(sprite2);
        
        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


