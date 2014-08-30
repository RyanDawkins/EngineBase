//
//  WorldSettings.cpp
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "WorldSettings.h"

// Getter/Setter methods for width
int WorldSettings::getWidth()
{
    return this->width;
};
WorldSettings* WorldSettings::setWidth(int width)
{
    this->width = width;
    return this;
};

// Getter/Setter for height
int WorldSettings::getHeight()
{
    return this->height;
};
WorldSettings* WorldSettings::setHeight(int height)
{
    this->height = height;
    return this;
};

// Getter/Setter for Spp
int WorldSettings::getSpp()
{
    return this->spp;
};
WorldSettings* WorldSettings::setSpp(int spp)
{
    this->spp = spp;
    return this;
}

// Getter/Setter for background color
float WorldSettings::getBackgroundColor()
{
    return this->backgroundColor;
}
WorldSettings* WorldSettings::setBackgroundColor(float backgroundColor)
{
    this->backgroundColor = backgroundColor;
    return this;
};

// Getter/Setter for background music
std::string WorldSettings::getBackgroundMusic()
{
    return this->backgroundMusic;
}
WorldSettings* WorldSettings::setBackgroundMusic(std::string)
{
    this->backgroundMusic = backgroundMusic;
    return this;
}