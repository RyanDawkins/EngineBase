//
//  Pov.h
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__Pov__
#define __EngineBase__Pov__

#include <iostream>
#include "glm.hpp"
#include "ext.hpp"

class Pov
{
private:
    std::string name;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 vup;
    float fovy;
    float znear;
    float zfar;
public:
    std::string getName();
    Pov* setName(std::string name);
    
    glm::vec3 getEye();
    Pov* setEye(glm::vec3 eye);
    
    glm::vec3 getCenter();
    Pov* setCenter(glm::vec3 center);
    
    glm::vec3 getVup();
    Pov* setVup(glm::vec3 vup);
    
    float getFovy();
    Pov* setFlovy(float fovy);
    
    float getZnear();
    Pov* setZnear(float znear);
    
    float getZfar();
    Pov* setZfar(float zfar);
    
    void translate(const glm::vec3 &t);
    
    void rotate(glm::vec3 axis, float angle);
};

#endif /* defined(__EngineBase__Pov__) */
