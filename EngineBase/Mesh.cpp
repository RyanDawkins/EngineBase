//
//  Mesh.cpp
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh()
{
    this->constructor(0);
};

Mesh::Mesh(long meshInstancesSize)
{
    this->constructor(meshInstancesSize);
};

void Mesh::constructor(long meshInstancesSize)
{
    //if(meshInstancesSize > 0) {
    this->meshInstances = new std::vector<MeshInstance*>();
    //}
};

Mesh* Mesh::addInstance(MeshInstance *meshInstance) {

    // Dynamically resizing incase we add too much baloney.
    if(this->meshInstances == NULL) {
        std::cout << "WHAT THE HECK" << std::endl;
        exit(0);
    }
    
    if(this->meshInstances->max_size() == this->meshInstances->size()) {
        this->meshInstances->resize(this->meshInstances->max_size() * 2);
    }
//    this->meshInstances->insert(meshInstance);
    this->meshInstances->push_back(meshInstance);
    return this;
}

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

std::vector<MeshInstance*>* Mesh::getInstances()
{
    return this->meshInstances;
}