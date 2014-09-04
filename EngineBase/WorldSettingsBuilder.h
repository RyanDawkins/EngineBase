//
//  WorldSettingsBuilder.h
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__WorldSettingsBuilder__
#define __EngineBase__WorldSettingsBuilder__

#include <iostream>
#include "lib/json11.hpp"
#include "WorldSettings.h"

class WorldSettingsBuilder
{
private:
    json11::Json* json;
public:
    WorldSettingsBuilder();
    WorldSettingsBuilder(json11::Json* json);
    std::string getFileName();
    void setFileName(std::string fileName);
    json11::Json* getJson();
    void setJson(json11::Json* json);
    json11::Json* readJsonFromFile(std::string fileName);
    WorldSettings* forgeWorldSettings();
};

#endif /* defined(__EngineBase__WorldSettingsBuilder__) */