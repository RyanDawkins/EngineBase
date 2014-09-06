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
    double fovy;
    double znear;
    double zfar;
public:
    std::string getName();
    Pov* setName(std::string name);
    
    glm::vec3 getEye();
    Pov* setEye(glm::vec3 eye);
    
    glm::vec3 getCenter();
    Pov* setCenter(glm::vec3 center);
    
    glm::vec3 getVup();
    Pov* setVup(glm::vec3 vup);
    
    double getFovy();
    Pov* setFovy(double fovy);
    
    double getZnear();
    Pov* setZnear(double znear);
    
    double getZfar();
    Pov* setZfar(double zfar);
    
    void translateGlobal(glm::vec3 &t);
    void translateLocal(glm::vec3 &t);
    void rotateGlobal(glm::vec3 axis, float angle);
    void rotateLocal(glm::vec3 axis, float angle);
};

#endif /* defined(__EngineBase__Pov__) */
