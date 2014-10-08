//
//  Wd40.h
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#ifndef __EngineBase__Wd40__
#define __EngineBase__Wd40__

#include <iostream>
#include "EngineUtil.h"
#include "SceneBuilder.h"
#include "SceneStruct.h"
#include "WorldSettingsBuilder.h"
#include "WorldSettings.h"
#include "MeshInstance.h"
#include "SceneTest.h"
#include <map>

class Wd40
{
private:
    GLFWwindow* gWindow;
    SceneStruct* scene;
    ISoundEngine* soundEngine;
    ISound* music;
    Camera* gCamera;
    std::map<std::string,TriMesh*>* meshMap;
    std::vector<TriMeshInstance*> instances;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        if (action == GLFW_PRESS &&
            ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))) {
            printf("\n%c\n", (char)key);
        }
    };
public:
    Wd40();
    GLFWwindow* getWindow() {
        return this->gWindow;
    };
    void loadScene(const char *sceneFile);
    void loadWorldSettings();
    void loadMeshes();
    void loadMeshInstances();
    void loadPov();
    void loadSound();
    void update();
    void render();
    void controller();
};

#endif /* defined(__EngineBase__Wd40__) */