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
    std::vector<MeshInstance*> meshInstances;
public:
    std::string getName();
    Mesh* setName(std::string name);
    std::string getFile();
    Mesh* setFile(std::string file);
};


#endif /* defined(__EngineBase__Mesh__) */
