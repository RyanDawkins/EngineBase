//
//  PovBuilder.h
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__PovBuilder__
#define __EngineBase__PovBuilder__

#include <iostream>
#include <fstream>
#include <fstream>
#include <streambuf>
#include <string>
#include "json11.hpp"
#include "Pov.h"

class PovBuilder
{
private:
    json11::Json* json;
    glm::vec3 readVector(json11::Json::array items);
public:
    void readFromFile(std::string fileName);
    json11::Json* getJson();
    PovBuilder* setJson(json11::Json* json);
    Pov* forge();
};

#endif /* defined(__EngineBase__PovBuilder__) */
