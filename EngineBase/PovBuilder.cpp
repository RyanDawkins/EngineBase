//
//  PovBuilder.cpp
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "PovBuilder.h"

void PovBuilder::readFromFile(std::string fileName)
{
    std::ifstream t(fileName);
    std::string jsonString((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
    std::string errorString;
    
    // Deferencing the pointer so we can use the overloaded operator method provided
    // by our json11::Json method
    this->setJson(new json11::Json(json11::Json::parse(jsonString, errorString)));
}

PovBuilder* PovBuilder::setJson(json11::Json* json)
{
    this->json = json;
    return this;
};

Pov* PovBuilder::forge()
{
    Pov* pov = new Pov();
    json11::Json povJson = (*this->json);
    pov->setEye(this->readVector(povJson["eye"].array_items()));
    pov->setCenter(this->readVector(povJson["center"].array_items()));
    pov->setVup(this->readVector(povJson["vup"].array_items()));
    pov->setName(povJson["name"].string_value());
    pov->setFlovy(povJson["flovy"].number_value());
    pov->setZnear(povJson["znear"].number_value());
    pov->setZfar(povJson["zfar"].number_value());
    
    return pov;
}

glm::vec3 PovBuilder::readVector(json11::Json::array items)
{
    glm::vec3 scale;
    
    // If the value exists, then we know it is the x, and so on.
    if(items.size() > 0) {
        scale[0] = items[0].number_value();
    } else {
        scale[0] = 1;
    }
    if(items.size() > 1) {
        scale[1] = items[1].number_value();
    } else {
        scale[1] = 1;
    }
    if(items.size() > 2) {
        scale[2] = items[2].number_value();
    } else {
        scale[2] = 1;
    }
    
    return scale;
}