//
//  SceneTest.cpp
//  EngineBase
//
//  Created by Dawkins on 9/6/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "SceneTest.h"

SceneTest::SceneTest()
{
    this->testsPassed = true;
};

bool SceneTest::runTests()
{
    SceneBuilder* builder = new SceneBuilder();
    builder->jsonFromFile("monkeyScene.json");
    SceneStruct* scene = builder->forge();
    if(scene == NULL) {
        return false;
    }
    
    this->checkWorldSettings(scene->getWorldSettings());
    this->checkCamera(scene->getPov());
    
    return this->testsPassed;
};

void SceneTest::checkCamera(Pov* pov) {
    std::string name = "camera1";
    double flovy = 0.4;
    double znear = 0.1;
    double zfar = 1000;
    glm::vec3 eye;
    eye[0] = 0;
    eye[1] = -1;
    eye[2] = 4;
    glm::vec3 center;
    center[0] = 0;
    center[1] = 0.1;
    center[2] = 0;
    glm::vec3 vup;
    vup[0] = 0;
    vup[1] = 1;
    vup[2] = 0;
    
    if(name.compare(pov->getName()) != 0) {
        this->testsPassed = false;
        std::cout << "name is wrong" << std::endl;
    }
    if(flovy != pov->getFovy()) {
        this->testsPassed = false;
        std::cout << "fovy is wrong" << std::endl;
        std::cout << "Real: " << flovy << ", read: " << pov->getFovy() << std::endl;
    }
    if(znear != pov->getZnear()) {
        this->testsPassed = false;
        std::cout << "znear is wrong" << std::endl;
    }
    if(zfar != pov->getZfar()) {
        this->testsPassed = false;
        std::cout << "zfar is wrong" << std::endl;
    }
    if(!this->compareVector(eye, pov->getEye())) {
        this->testsPassed = false;
        std::cout << "Eye is wrong" << std::endl;
    }
    if(!this->compareVector(center, pov->getCenter())) {
        this->testsPassed = false;
        std::cout << "Center is wrong" << std::endl;
    }
    if(!this->compareVector(vup, pov->getVup())) {
        this->testsPassed = false;
        std::cout << "Vup is wrong" << std::endl;
    }
}

void SceneTest::checkWorldSettings(WorldSettings* worldSettings)
{
    std::string worldWindowTitle = "Test Scene";
    int worldWidth = 800;
    int worldHeight = 600;
    int worldSpp = 4;
    glm::vec3 backgroundColor;
    backgroundColor.r = 0.4;
    backgroundColor.g = 0.4;
    backgroundColor.b = 0.4;
    std::string backgroundMusic = "avemaria.wav";
    if(worldWindowTitle.compare(worldSettings->getWindowTitle()) != 0) {
        this->testsPassed = false;
    }
    if(worldWidth != worldSettings->getWidth()) {
        this->testsPassed = false;
    }
    if(worldHeight != worldSettings->getHeight()) {
        this->testsPassed = false;
    }
    if(worldSpp != worldSettings->getSpp()) {
        this->testsPassed = false;
    }
    if(backgroundColor.r != worldSettings->getBackgroundColor().r
       || backgroundColor.g != worldSettings->getBackgroundColor().g
       || backgroundColor.b != worldSettings->getBackgroundColor().b) {
        this->testsPassed = false;
    }
    if(backgroundMusic.compare(worldSettings->getBackgroundMusic()) != 0) {
        this->testsPassed = false;
    }
};

bool SceneTest::compareVector(glm::vec3 a, glm::vec3 b) {
    
    if(a[0] != b[0]) {
        return false;
    }
    if(a[1] != b[1]) {
        return false;
    }
    if(a[2] != b[2]) {
        return false;
    }
    
    return true;
}
