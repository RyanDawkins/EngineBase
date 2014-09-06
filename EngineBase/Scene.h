//
//  Scene.h
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__Scene__
#define __EngineBase__Scene__

#include <iostream>
#include "WorldSettings.h"
#include <vector>
#include "Mesh.h"
#include "Pov.h"

class Scene
{
private:
    std::vector<Mesh*>* meshes;
    WorldSettings* worldSettings;
    Pov* pov;
public:

    // Constructor junkkk
    Scene();
    ~Scene();

    // Getters/setters
    WorldSettings* getWorldSettings();
    Scene* setWorldSettings(WorldSettings* worldSettings);

    // Mesh junk
    std::vector<Mesh*>* getMeshes();
    Scene* setMeshes(std::vector<Mesh*>* meshes);
    void addMesh(Mesh* mesh);
    
    Pov* getPov();
    Scene* setPov(Pov* pov);
};

#endif /* defined(__EngineBase__Scene__) */