//
//  Sprite.hpp
//  KnightSoul
//
//  Created by Knight on 2017/3/19.
//  Copyright © 2017年 Knight. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include "SpriteSheet.hpp"
#include <map>

class Sprite
{
public:
    static Sprite* Create();
    static Sprite* Create(std::string jsonPath);
    void Update(float dt);
    void SetFrame(int imageIndex, std::string imageName);
    std::map<int, std::string> SpriteFrames;
    SpriteSheet* SpriteSheetGroup;
    float ImageSpeed;
    float ImageIndex;
    float ImageNumber;
};

#endif /* Sprite_hpp */
