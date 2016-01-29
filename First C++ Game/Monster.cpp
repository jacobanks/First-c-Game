//
//  Monster.cpp
//  First C++ Game
//
//  Created by Jacob Banks on 1/29/16.
//  Copyright © 2016 Jacob Banks. All rights reserved.
//

#include "Monster.hpp"

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

void Monster::moving()
{
        if(move[UP] == true)
        {
            y -= movespeed;
            currentAnimation = &walkingAnimationUp;
            
            if (y <= nextspot) {
                
                y = nextspot;
                nextspot = y - 32;
                
                int nextX = x / 32;
                int nextY = (y / 32) - 1;
                int nextTile = tiles[nextX + nextY * 18];
                
                if (nextTile != 0)
                {
                    move[UP] = false;
                }
            }
        }
        
        if(move[DOWN] == true)
        {
            y += movespeed;
            
            if (y >= nextspot) {
                
                y = nextspot;
                nextspot = y + 32;
                
                int nextX = x / 32;
                int nextY = (y / 32) + 1;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0)
                {
                    move[DOWN] = false;
                }
            }
        }

        if(move[LEFT] == true)
        {
            x -= movespeed;
            currentAnimation = &walkingAnimationLeft;
            
            if (x <= nextspot) {
                
                x = nextspot;
                nextspot = x - 32;
                
                int nextX = (x / 32) - 1;
                int nextY = y / 32;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0)
                {
                    move[LEFT] = false;
                }
            }
        }
        
        if(move[RIGHT] == true)
        {
            x += movespeed;
            currentAnimation = &walkingAnimationRight;
            
            if (x >= nextspot) {
                
                x = nextspot;
                nextspot = x + 32;
                
                int nextX = (x / 32) + 1;
                int nextY = y / 32;
                int nextTile = tiles[nextX + nextY * 18];
                
                if(nextTile != 0)
                {
                    move[RIGHT] = false;
                }
            }
        }
}
