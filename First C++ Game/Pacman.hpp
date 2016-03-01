//
//  Pacman.hpp
//  First C++ Game
//
//  Created by Jacob Banks on 3/1/16.
//  Copyright © 2016 Jacob Banks. All rights reserved.
//

#ifndef Pacman_hpp
#define Pacman_hpp

#include "AnimatedSprite.hpp"
#include "ResourcePath.hpp"

using namespace std;

extern int tilesize;
extern const int tiles[];

class Pacman
{
public:
    Pacman()
    {
        x = 256;
        y = 288;
        
        movespeed = 80.0 / tilesize;
        
        for(int i = 0; i < 4; ++i) // initialize all move booleans to false
            move[i] = false;
        
        walking = false;
        pacmanRect.setScale(sf::Vector2f(1, 1));
        
        noKeyWasPressed = true;
        
    }
    
    void keymove(); // keypress detection
    void moving();  // moving if "walking" boolean is true
    void movingAnimations();
    
    void setupTexturesAndAnimations();
    
    float getX();
    float getY();
    
    bool checkKeyPressed();
    
    sf::FloatRect getGlobalBounds();
    
    AnimatedSprite getPacmanRect();
    
private:
    float x;
    float y;
    float movespeed; //sets the movespeed
    
    enum MOVE {UP,DOWN,LEFT,RIGHT}; //enums instead of remember numbers
    bool move[4]; //deciding if u move up/down/left/right
    bool walking;
    int nextspot; //the next tilespot of the map
    
    AnimatedSprite pacmanRect;
    
    Animation walkingAnimationDown;
    Animation walkingAnimationUp;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationCenter;
    
    Animation* currentAnimation = &walkingAnimationCenter;
    
    bool noKeyWasPressed;
    
    sf::Clock frameClock;
};

#endif /* Pacman_hpp */
