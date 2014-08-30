//
//  Scene.cpp
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "Scene.h"

// Default constructor setting pointers to null else you will
// not know if they are set.
Scene::Scene()
{
    this->worldSettings = NULL;
};

// Deconstructor to deallocate the worldSettings memory
Scene::~Scene()
{
    if(this->worldSettings != NULL) {
        delete this->worldSettings;
        this->worldSettings = NULL;
    }
};

// Getter/Setter for world settings
WorldSettings* Scene::getWorldSettings()
{
    return this->worldSettings;
};
Scene* Scene::setWorldSettings(WorldSettings* worldSettings)
{
    this->worldSettings = worldSettings;
    return this;
};