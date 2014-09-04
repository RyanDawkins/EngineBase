//
//  MeshInstance.cpp
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "MeshInstance.h"

std::string MeshInstance::getName()
{
    return this->name;
}
MeshInstance* MeshInstance::setName(std::string name)
{
    this->name = name;
    return this;
}

glm::vec4 MeshInstance::getScale()
{
    return this->scale;
}
MeshInstance* MeshInstance::setScale(glm::vec4 scale)
{
    this->scale = scale;
    return this;
}

std::string MeshInstance::getVertexShader()
{
    return this->vertexShader;
}
MeshInstance* MeshInstance::setVertexShade(std::string vertexShader)
{
    this->vertexShader = vertexShader;
    return this;
}

std::string MeshInstance::getFragmentShader()
{
    return this->fragmentShader;
}
MeshInstance* MeshInstance::setFragmentShader(std::string fragmentShader)
{
    this->fragmentShader = fragmentShader;
    return this;
}

std::string MeshInstance::getDiffuseTexture()
{
    return this->diffuseTexture;
}
MeshInstance* MeshInstance::setDiffuseTexture(std::string diffuseTexture)
{
    this->diffuseTexture = diffuseTexture;
    return this;
}