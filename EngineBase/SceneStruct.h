//
//  Scene.h
//  EngineBase
//
//  Created by Dawkins on 8/30/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__SceneStruct__
#define __EngineBase__SceneStruct__

#include <iostream>
#include "WorldSettings.h"
#include <vector>

#include <map>
#include "Mesh.h"
#include "Pov.h"

class SceneStruct
{
private:
    std::vector<Mesh*>* meshes;
    WorldSettings* worldSettings;
    Pov* pov;
    std::map<std::string, RGBAImage*> textures;
public:

    // Constructor junkkk
    SceneStruct();
    ~SceneStruct();

    // Getters/setters
    WorldSettings* getWorldSettings();
    SceneStruct* setWorldSettings(WorldSettings* worldSettings);

    // Mesh junk
    std::vector<Mesh*>* getMeshes();
    SceneStruct* setMeshes(std::vector<Mesh*>* meshes);
    void addMesh(Mesh* mesh);
    
    void addTexture(std::string s, RGBAImage* texture){
        this->textures[s] = texture;
    }
    
    RGBAImage* getTexture(std::string string) {
        return this->textures[string];
    }
    
    Pov* getPov();
    SceneStruct* setPov(Pov* pov);
};

#endif /* defined(__EngineBase__SceneStruct__) */