//
//  MeshInstance.h
//  EngineBase
//
//  Created by Dawkins on 9/2/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__MeshInstance__
#define __EngineBase__MeshInstance__

#include <iostream>
#include <glm/glm.hpp>

class MeshInstance
{
private:
    std::string name;
    glm::vec4 scale;
    std::string vertexShader;
    std::string fragmentShader;
    std::string diffuseTexture;
public:
    std::string getName();
    MeshInstance* setName(std::string name);
    
    glm::vec4 getScale();
    MeshInstance* setScale(glm::vec4 scale);
    
    std::string getVertexShader();
    MeshInstance* setVertexShade(std::string vertexShader);
    
    std::string getFragmentShader();
    MeshInstance* setFragmentShader(std::string fragmentShader);
    
    std::string getDiffuseTexture();
    MeshInstance* setDiffuseTexture(std::string diffuseTexture);
};

#endif /* defined(__EngineBase__MeshInstance__) */
