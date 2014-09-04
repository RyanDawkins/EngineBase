//
//  Mesh.cpp
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "Mesh.h"

std::string Mesh::getName()
{
    return this->name;
}
Mesh* Mesh::setName(std::string name)
{
    this->name = name;
    return this;
}

std::string Mesh::getFile()
{
    return this->file;
}
Mesh* Mesh::setFile(std::string file)
{
    this->file = file;
    return this;
}