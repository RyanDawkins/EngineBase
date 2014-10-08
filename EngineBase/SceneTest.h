//
//  SceneTest.h
//  EngineBase
//
//  Created by Dawkins on 9/6/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__SceneTest__
#define __EngineBase__SceneTest__

#include <iostream>
#include "SceneBuilder.h"
#include "SceneStruct.h"
#include "WorldSettings.h"
#include "Pov.h"
#include <string>
#include <assert.h>

class SceneTest
{
private:
    bool testsPassed;
    void checkWorldSettings(WorldSettings* worldSettings);
    void checkCamera(Pov* pov);
    bool compareVector(glm::vec3 a, glm::vec3 b);
public:
    SceneTest();
    bool runTests();
};

#endif /* defined(__EngineBase__SceneTest__) */
