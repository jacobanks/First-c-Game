//
//  Monster.hpp
//  First C++ Game
//
//  Created by Jacob Banks on 1/29/16.
//  Copyright © 2016 Jacob Banks. All rights reserved.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"

class Monster
{
public:
    Monster()
    {
        x = 256;
        y = 32;
        
        movespeed = 80.0 / 32;
        
        for(int i = 0; i < 4; ++i) //initialize all move booleans to false
            move[i] = false;
        
        sprite.setScale(sf::Vector2f(1, 1));
    }
    
    void moving(); //moving if "walking" boolean is true
    
    float x;
    float y;
    float movespeed; //sets the movespeed
    
    enum MOVE {UP,DOWN,LEFT,RIGHT}; //enums instead of remember numbers
    bool move[4]; //deciding if u move up/down/left/right
    bool walking;
    int nextspot; //the next tilespot of the map
    
    AnimatedSprite sprite;
    Animation walkingAnimationDown;
    Animation walkingAnimationUp;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationCenter;
    
    Animation* currentAnimation = &walkingAnimationDown;
};

