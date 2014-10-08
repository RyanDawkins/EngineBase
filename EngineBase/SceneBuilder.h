//
//  SceneBuilder.h
//  EngineBase
//
//  Created by Dawkins on 9/3/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__SceneBuilder__
#define __EngineBase__SceneBuilder__

#include <iostream>
#include <fstream>
#include <fstream>
#include <streambuf>
#include <string>
#include "json11.hpp"
#include "SceneStruct.h"
#include "WorldSettingsBuilder.h"
#include "WorldSettings.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "PovBuilder.h"
#include "Pov.h"

class SceneBuilder
{
private:
    json11::Json* json;
public:
    
    // Constructor, along with default one
    void constructor(json11::Json* json);
    SceneBuilder();
    SceneBuilder(json11::Json* json);
    
    // Method to read json from file, sets json in the thing
    void jsonFromFile(std::string fileName);
    
    // Getter/setters for junk
    json11::Json* getJson();
    SceneBuilder* setJson(json11::Json* json);
    
    // Method to forge a Scene based off of the data we sent earlier
    SceneStruct* forge();
};

#endif /* defined(__EngineBase__SceneBuilder__) */
