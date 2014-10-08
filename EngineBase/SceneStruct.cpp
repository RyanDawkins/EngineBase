//
//  Scene.cpp
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "SceneStruct.h"

// Default constructor setting pointers to null else you will
// not know if they are set.
SceneStruct::SceneStruct()
{
    this->worldSettings = NULL;
};

// Deconstructor to deallocate the worldSettings memory
SceneStruct::~SceneStruct()
{
    if(this->worldSettings != NULL) {
        delete this->worldSettings;
        this->worldSettings = NULL;
    }
};

// Getter/Setter for world settings
WorldSettings* SceneStruct::getWorldSettings()
{
    return this->worldSettings;
};
SceneStruct* SceneStruct::setWorldSettings(WorldSettings* worldSettings)
{
    this->worldSettings = worldSettings;
    return this;
};

std::vector<Mesh*>* SceneStruct::getMeshes() {
    return this->meshes;
}
SceneStruct* SceneStruct::setMeshes(std::vector<Mesh*> *meshes) {
    this->meshes = meshes;
    return this;
}

void SceneStruct::addMesh(Mesh* mesh)
{
    if(this->meshes->max_size() > this->meshes->size())
    {
        this->meshes->resize(this->meshes->max_size() * 2);
    }
    this->meshes->push_back(mesh);
}

Pov* SceneStruct::getPov()
{
    return this->pov;
}
SceneStruct* SceneStruct::setPov(Pov* pov)
{
    this->pov = pov;
    return this;
}