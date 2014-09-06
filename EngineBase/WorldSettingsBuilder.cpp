//
//  WorldSettingsBuilder.cpp
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "WorldSettingsBuilder.h"
#include <fstream>
#include <streambuf>
#include <string>

// Constructor that demands a file name and will read the json later...
WorldSettingsBuilder::WorldSettingsBuilder()
{
};

WorldSettingsBuilder::WorldSettingsBuilder(json11::Json* json)
{
    this->json = json;
};

// Method to read the json from a file and set it to our junk
json11::Json* WorldSettingsBuilder::readJsonFromFile(std::string fileName)
{
    std::ifstream t(fileName);
    std::string jsonString((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
    std::string errorString;
    
    // Deferencing the pointer so we can use the overloaded operator method provided
    // by our json11::Json method
    json11::Json* readJson = new json11::Json(json11::Json::parse(jsonString, errorString));
    this->json = new json11::Json((*readJson)["worldSettings"]);
    
    // Deallocating memory
    delete readJson;
    readJson = NULL;
    
    return this->json;
};

// Getter/Setter for json pointer
json11::Json* WorldSettingsBuilder::getJson()
{
    return this->json;
};
void WorldSettingsBuilder::setJson(json11::Json* json)
{
    this->json = json;
};

// Creates a WorldSettings object based off of the json file
// also deletes our json pointer
WorldSettings* WorldSettingsBuilder::forgeWorldSettings()
{
    WorldSettings* worldSettings = new WorldSettings();

    // Grabbing data about world settings
    json11::Json::object worldSettingsJson = this->json->object_items();
    
    int width = worldSettingsJson["width"].int_value();
    int height = worldSettingsJson["height"].int_value();
    int spp = worldSettingsJson["spp"].int_value();
    std::string backgroundMusic = worldSettingsJson["backgroundMusic"].string_value();
    std::string windowTitle = worldSettingsJson["windowTitle"].string_value();
    
    std::cout << "Width      : " << width << std::endl;
    std::cout << "Height     : " << height << std::endl;
    std::cout << "Spp        : " << spp << std::endl;
    std::cout << "Music      : " << backgroundMusic << std::endl;
    std::cout << "WindowTitle: " << windowTitle << std::endl;
    
    // Grabbing all the colors
    glm::vec4 backgroundColor;
    json11::Json::array backgroundColorArray = worldSettingsJson["backgroundColor"].array_items();
    
    // If the value exists, then we know it is the x, and so on.
    if(backgroundColorArray.size() > 0) {
        backgroundColor.r= backgroundColorArray[0].number_value();
    } else {
        backgroundColor.r = 1;
    }
    if(backgroundColorArray.size() > 1) {
        backgroundColor.g = backgroundColorArray[1].number_value();
    } else {
        backgroundColor.g = 1;
    }
    if(backgroundColorArray.size() > 2) {
        backgroundColor.b = backgroundColorArray[2].number_value();
    } else {
        backgroundColor.b = 1;
    }
    if(backgroundColorArray.size() > 3) {
        backgroundColor.a = backgroundColorArray[3].number_value();
    } else {
        backgroundColor.a = 1;
    }
    std::cout << "music file" << backgroundMusic << std::endl;
    worldSettings->setHeight(height)
        ->setWidth(width)
        ->setSpp(spp)
        ->setBackgroundColor(backgroundColor)
        ->setBackgroundMusic(backgroundMusic)
        ->setWindowTitle(windowTitle);
    
    return worldSettings;
};