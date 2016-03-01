//
//  Pacman.cpp
//  First C++ Game
//
//  Created by Jacob Banks on 3/1/16.
//  Copyright © 2016 Jacob Banks. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <cstdlib>

#include "Pacman.hpp"
#include "ResourcePath.hpp"
#include "AnimatedSprite.hpp"

using namespace std;

float Pacman::getX()
{
    return x;
}

float Pacman::getY()
{
    return y;
}

bool Pacman::checkKeyPressed()
{
    return noKeyWasPressed;
}

sf::FloatRect Pacman::getGlobalBounds()
{
    return pacmanRect.getGlobalBounds();
}

AnimatedSprite Pacman::getPacmanRect()
{
    return pacmanRect;
}

void Pacman::setupTexturesAndAnimations()
{
    // load textures
    sf::Texture pacmanSheet;
    if (!pacmanSheet.loadFromFile(resourcePath() + "pacmanSheet.png")) {
        cout << "broken" << endl;
    }
    
    sf::Texture Pacmantexture;
    if (!Pacmantexture.loadFromFile(resourcePath() + "pacman.png"))
    {
        cout << "Failed to load player spritesheet!" << endl;
    }
    
    // set up the animations for all four directions
    walkingAnimationDown.setSpriteSheet(pacmanSheet);
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    
    walkingAnimationCenter.setSpriteSheet(Pacmantexture);
    walkingAnimationCenter.addFrame(sf::IntRect(0, 0, 32, 32));
    
    walkingAnimationLeft.setSpriteSheet(pacmanSheet);
    walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    
    walkingAnimationRight.setSpriteSheet(pacmanSheet);
    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    
    walkingAnimationUp.setSpriteSheet(pacmanSheet);
    walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
}

void Pacman::keymove()
{
    // keymove() and moving() functions are working together
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // checks if pacman is all the way on a tile before moving (needs some work)
        if(move[UP] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0) {
            int nextX = x / 32;
            int nextY = (y / 32) - 1;
            int nextTile = tiles[nextX + nextY * 18];
            
            if (nextTile != 0) { /* don't move if the next tile is a wall */ }
            else if (move[UP] != true) {
                nextspot = y - tilesize;
                
                move[DOWN] = false;
                move[LEFT] = false;
                move[RIGHT] = false;
                move[UP] = true;
                walking = true;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(move[DOWN] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0) {
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
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(move[LEFT] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0) {
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
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(move[RIGHT] == false && fmod(x, 32) == 0 && fmod(y, 32) == 0) {
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

void Pacman::moving()
{
    
    if(walking == true) {
        
        if(move[UP] == true) {
            y -= movespeed;
            currentAnimation = &walkingAnimationUp;
            noKeyWasPressed = false;
            
            if (y <= nextspot) {
                
                y = nextspot;
                nextspot = y - tilesize;
                
                int nextX = x / 32;
                int nextY = (y / 32) - 1;
                int nextTile = tiles[nextX + nextY * 18];
                
                if (nextTile != 0) {
                    walking = false;
                    move[UP] = false;
                }
            }
        }
        
        if(move[DOWN] == true) {
            y += movespeed;
            currentAnimation = &walkingAnimationDown;
            noKeyWasPressed = false;
            
            if (y >= nextspot) {
                
                y = nextspot;
                nextspot = y + tilesize;
                
                int nextX = x / 32;
                int nextY = (y / 32) + 1;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0) {
                    walking = false;
                    move[DOWN] = false;
                }
            }
        }
        
        if(move[LEFT] == true) {
            x -= movespeed;
            currentAnimation = &walkingAnimationLeft;
            noKeyWasPressed = false;
            
            if (x <= nextspot) {
                
                x = nextspot;
                nextspot = x - tilesize;
                
                int nextX = (x / 32) - 1;
                int nextY = y / 32;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0) {
                    walking = false;
                    move[LEFT] = false;
                }
            }
        }
        
        if(move[RIGHT] == true) {
            x += movespeed;
            currentAnimation = &walkingAnimationRight;
            noKeyWasPressed = false;
            
            if (x >= nextspot) {
                
                x = nextspot;
                nextspot = x + tilesize;
                
                int nextX = (x / 32) + 1;
                int nextY = y / 32;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0) {
                    walking = false;
                    move[RIGHT] = false;
                }
            }
        }
    }
    
}

void Pacman::movingAnimations()
{
    pacmanRect.setPosition(x, y);
    
    sf::Time frameTime = frameClock.restart();
    
    pacmanRect.play(*currentAnimation);
    
    // if no key was pressed stop the animation
    if (noKeyWasPressed)
    {
        pacmanRect.stop();
    }
    noKeyWasPressed = true;
    
    // update AnimatedSprite
    pacmanRect.update(frameTime);
}
