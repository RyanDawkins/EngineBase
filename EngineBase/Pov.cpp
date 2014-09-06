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

double Pov::getFovy()
{
    return this->fovy;
};
Pov* Pov::setFovy(double fovy)
{
    this->fovy = fovy;
    return this;
};

double Pov::getZnear()
{
    return this->znear;
};
Pov* Pov::setZnear(double znear)
{
    this->znear = znear;
    return this;
};

double Pov::getZfar()
{
    return this->zfar;
};
Pov* Pov::setZfar(double zfar)
{
    this->zfar = zfar;
    return this;
};

void Pov::translateGlobal(glm::vec3 &t) { eye += t; center += t; }
void Pov::translateLocal(glm::vec3 &t) {
    glm::vec3 zz = glm::normalize(eye - center);
    glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
    glm::vec3 yy = glm::cross(zz, xx);
    glm::vec3 tt = t.x*xx + t.y*yy + t.z*zz;
    eye += tt; center += tt;
}
void Pov::rotateGlobal(glm::vec3 axis, float angle) {
    glm::mat4x4 R = glm::axisAngleMatrix(axis, angle);
    glm::vec4 zz = glm::vec4(eye - center, 0);
    glm::vec4 Rzz = R*zz;
    center = eye - glm::vec3(Rzz);
    //
    glm::vec4 up = glm::vec4(vup, 0);
    glm::vec4 Rup = R*up;
    vup = glm::vec3(Rup);
}
void Pov::rotateLocal(glm::vec3 axis, float angle) {
    glm::vec3 zz = glm::normalize(eye - center);
    glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
    glm::vec3 yy = glm::cross(zz, xx);
    glm::vec3 aa = xx*axis.x + yy*axis.y + zz*axis.z;
    this->rotateGlobal(aa, angle);
}