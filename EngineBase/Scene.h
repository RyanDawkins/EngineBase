//
//  Scene.h
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__Scene__
#define __EngineBase__Scene__/Users/dawkins/XCode Projects/EngineBase/EngineBase/Scene.h

#include <iostream>
#include "WorldSettings.h"

#endif /* defined(__EngineBase__Scene__) */
class Scene
{
private:
    WorldSettings* worldSettings;
public:
    Scene();
    ~Scene();
    WorldSettings* getWorldSettings();
    Scene* setWorldSettings(WorldSettings* worldSettings);
};