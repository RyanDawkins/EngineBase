//
//  Pov.cpp
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "Pov.h"

std::string Pov::getName()
{
    return this->name;
};
Pov* Pov::setName(std::string name)
{
    this->name = name;
    return this;
};

glm::vec3 Pov::getEye()
{
    return this->eye;
};
Pov* Pov::setEye(glm::vec3 eye)
{
    this->eye = eye;
    return this;
};

glm::vec3 Pov::getCenter()
{
    return this->center;
};
Pov* Pov::setCenter(glm::vec3 center)
{
    this->center = center;
    return this;
};

glm::vec3 Pov::getVup()
{
    return this->vup;
};
Pov* Pov::setVup(glm::vec3 vup)
{
    this->vup = vup;
    return this;
};

float Pov::getFovy()
{
    return this->fovy;
};
Pov* Pov::setFlovy(float fovy)
{
    this->fovy = fovy;
    return this;
};

float Pov::getZnear()
{
    return this->znear;
};
Pov* Pov::setZnear(float znear)
{
    this->znear = znear;
    return this;
};

float Pov::getZfar()
{
    return this->zfar;
};
Pov* Pov::setZfar(float zfar)
{
    this->zfar = zfar;
    return this;
};

void Pov::translate(const glm::vec3 &t) {
    std::cout << "Translating" << std::endl;
    glm::vec3 zz = glm::normalize(this->eye - this->center);
    glm::vec3 xx = glm::normalize(glm::cross(this->vup, zz));
    glm::vec3 yy = glm::cross(zz, xx);
    glm::vec3 tt = t.x*xx + t.y*yy + t.z*zz;
    this->eye += tt; center += tt;
}

void Pov::rotate(glm::vec3 axis, float angle) {
    std::cout << "Rotating" << std::endl;
    glm::mat4x4 R = glm::axisAngleMatrix(axis, angle);
    glm::vec4 zz = glm::vec4(this->eye - this->center, 0);
    glm::vec4 Rzz = R*zz;
    this->center = this->eye - glm::vec3(Rzz);
    glm::vec4 up = glm::vec4(this->vup, 0);
    glm::vec4 Rup = R*up;
    this->vup = glm::vec3(Rup);
}