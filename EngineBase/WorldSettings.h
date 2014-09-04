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
#include <glm/glm.hpp>

class WorldSettings
{
private:
    int width;
    int height;
    int spp;
    glm::vec4 backgroundColor;
    std::string backgroundMusic;
    std::string windowTitle;
public:
    int getWidth();
    WorldSettings* setWidth(int width);
    int getHeight();
    WorldSettings* setHeight(int height);
    int getSpp();
    WorldSettings* setSpp(int spp);
    glm::vec4 getBackgroundColor();
    WorldSettings* setBackgroundColor(glm::vec4 backgroundcolor);
    std::string getBackgroundMusic();
    WorldSettings* setBackgroundMusic(std::string);
    std::string getWindowTitle();
    WorldSettings* setWindowTitle(std::string windowTitle);
};

#endif /* defined(__EngineBase__WorldSettings__) */