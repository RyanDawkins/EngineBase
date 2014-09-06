//
//  Mesh.h
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__Mesh__
#define __EngineBase__Mesh__

#include <iostream>
#include "MeshInstance.h"
#include <vector>

class Mesh
{
private:
    std::string name;
    std::string file;
    std::vector<MeshInstance*>* meshInstances;
public:

    // Constructor stuff
    void constructor(long meshInstancesSize);
    Mesh();
    Mesh(long meshInstancesSize);

    // Getters and setters
    std::string getName();
    Mesh* setName(std::string name);
    std::string getFile();
    Mesh* setFile(std::string file);

    // Adding MeshInstances
    Mesh* addInstance(MeshInstance* meshInstance);
    std::vector<MeshInstance*>* getInstances();
};


#endif /* defined(__EngineBase__Mesh__) */
