//
//  WorldSettings.h
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__WorldSettings__
#define __EngineBase__WorldSettings__

#include <iostream>

#endif /* defined(__EngineBase__WorldSettings__) */

class WorldSettings
{
private:
    int width;
    int height;
    int spp;
    float backgroundColor;
    std::string backgroundMusic;
public:
    int getWidth();
    WorldSettings* setWidth(int width);
    int getHeight();
    WorldSettings* setHeight(int height);
    int getSpp();
    WorldSettings* setSpp(int spp);
    float getBackgroundColor();
    WorldSettings* setBackgroundColor(float backgroundcolor);
    std::string getBackgroundMusic();
    WorldSettings* setBackgroundMusic(std::string);
};