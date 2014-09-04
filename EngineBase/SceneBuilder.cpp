//
//  SceneBuilder.cpp
//  EngineBase
//
//  Created by Dawkins on 9/3/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "SceneBuilder.h"

// Created default constructor
SceneBuilder::SceneBuilder()
{
    this->constructor(NULL);
};
SceneBuilder::SceneBuilder(json11::Json* json)
{
    this->constructor(json);
};
void SceneBuilder::constructor(json11::Json* json)
{
    this->setJson(json);
};

// Reads a file containing json text and stores that in our json variable to go through
// in our forge method
void SceneBuilder::jsonFromFile(std::string fileName)
{
    std::ifstream t(fileName);
    std::string jsonString((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
    std::string errorString;
    
    // Deferencing the pointer so we can use the overloaded operator method provided
    // by our json11::Json method
    this->setJson(new json11::Json(json11::Json::parse(jsonString, errorString)));
    std::cout << "Error string: '" << errorString << "'" << std::endl;
};

// Getters/Setters for json data
json11::Json* SceneBuilder::getJson()
{
    return this->json;
};
SceneBuilder* SceneBuilder::setJson(json11::Json* json)
{
    this->json = json;
    return this;
};

// Method to forge our junks
Scene* SceneBuilder::forge()
{
    Scene* scene = new Scene();
    
    // Grabbing all world settings
    json11::Json* wsJson = new json11::Json((*this->json)["worldSettings"]);
    json11::Json::object worldSettingsJson = wsJson->object_items();
    
    WorldSettingsBuilder* wsBuilder = new WorldSettingsBuilder(wsJson);
    scene->setWorldSettings(wsBuilder->forgeWorldSettings());
    
    // WorldSettingsBuilder deallocates the json so we will set it to null
    wsJson = NULL;
    return scene;
};