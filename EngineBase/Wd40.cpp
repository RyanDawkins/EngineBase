//
//  Wd40.cpp
//  EngineBase
//
//  Created by Dawkins on 9/4/14.
//  Copyright (c) 2014 dave. All rights reserved.
//

#include "Wd40.h"

Wd40::Wd40()
{
    this->gWindow = NULL;
    this->scene = NULL;
    this->gCamera = new Camera();
    this->meshMap = new map<std::string, TriMesh*>();
}

void Wd40::render()
{
    // clear color and depth buffer
    glm::vec4 backgroundColor = this->scene->getWorldSettings()->getBackgroundColor();
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// draw scene
	for(int i = 0; i < this->instances.size(); i++)
    {
        TriMeshInstance* gMeshInstance = this->instances[i];
        gMeshInstance->draw(this->gCamera);
    }
};

void Wd40::update()
{
    static float dScale = 0.0005f;
    
    for(int i = 0; i < this->instances.size(); i++)
    {
        TriMeshInstance gMeshInstance = *(this->instances[i]);
        float scale = gMeshInstance.T.scale[0];
        scale += dScale;
        if (scale > 1.25f) dScale = -0.0005f;
        if (scale < 0.25f) dScale = 0.0005f;
        gMeshInstance.setScale(glm::vec3(scale));
        
        // rotate mesh
        glm::quat r = glm::quat(glm::vec3(0.0f, 0.0051f, 0.00f));
        gMeshInstance.T.rotation *= r;
	
        gMeshInstance.diffuseColor += glm::vec4(0.0013f, 0.000921f, 0.00119f, 0.0f);
        if (gMeshInstance.diffuseColor[0] > 1.0f) gMeshInstance.diffuseColor[0] = 0.25f;
        if (gMeshInstance.diffuseColor[1] > 1.0f) gMeshInstance.diffuseColor[1] = 0.25f;
        if (gMeshInstance.diffuseColor[2] > 1.0f) gMeshInstance.diffuseColor[2] = 0.25f;
    }
};

void Wd40::loadScene(const char* sceneFile)
{
    SceneBuilder* sceneBuilder = new SceneBuilder();
    sceneBuilder->jsonFromFile(sceneFile);
    this->scene = sceneBuilder->forge();
};

void Wd40::loadWorldSettings()
{
    WorldSettings* worldSettings = this->scene->getWorldSettings();
    int gSPP = worldSettings->getSpp();
    int gHeight = worldSettings->getHeight();
    int gWidth = worldSettings->getWidth();
    std::string gWindowTitle = worldSettings->getWindowTitle();
    
	// Initialize the window with OpenGL context
	this->gWindow = createOpenGLWindow(gWidth, gHeight, gWindowTitle.c_str(), gSPP);
	glfwSetKeyCallback(this->gWindow, keyCallback);
};

void Wd40::loadMeshes()
{
    vector<Mesh*>* meshes = this->scene->getMeshes();
    
    for(int i = 0; i < meshes->size(); i++)
    {
        Mesh* mesh_i = (*meshes)[i];
        if(mesh_i == NULL) {
            continue;
        }
        TriMesh* triMesh = new TriMesh();
        triMesh->readFromPly(mesh_i->getFile());
        triMesh->sendToOpenGL();
        this->meshMap->insert(make_pair(mesh_i->getName(), triMesh));
    }
};

void Wd40::loadMeshInstances()
{
    vector<Mesh*>* meshes = this->scene->getMeshes();
    for(int i = 0; i < meshes->size(); i++)
    {
        Mesh* temp = (*meshes)[i];
        if(temp == NULL) {
            continue;
        }
        vector<MeshInstance*>* instances = temp->getInstances();
        
        for(int j = 0; j < instances->size(); j++)
        {
            MeshInstance* meshInstance = (*instances)[j];
            
            std::cout << "Mesh name:" <<  temp->getName() << std::endl;
            
            TriMeshInstance* gMeshInstance = new TriMeshInstance();
            GLuint vertexShader = loadShader(meshInstance->getVertexShader().c_str(), GL_VERTEX_SHADER);
            GLuint fragmentShader = loadShader(meshInstance->getFragmentShader().c_str(), GL_FRAGMENT_SHADER);
            GLuint shaderProgram;
            
            // Mesh Instance load to OpenGL
            std::cout << "Vertex Shader: " << meshInstance->getVertexShader() << std::endl;
            std::cout << "Diffuse secture: " << meshInstance->getDiffuseTexture() << std::endl;
            std::cout << "Fragment shader: " << meshInstance->getFragmentShader() << std::endl;
            gMeshInstance->diffuseTexture.loadPNG(meshInstance->getDiffuseTexture());
            gMeshInstance->diffuseTexture.sendToOpenGL();
            
            TriMesh* triMesh = this->meshMap->at(temp->getName());
            std::cout << "Trimesh: " << temp->getName() << std::endl;
            
            gMeshInstance->setMesh(triMesh);
            if(triMesh != NULL) {
                std::cout << "Trimesh is not null" << std::endl;
            }
            
            shaderProgram = createShaderProgram(vertexShader, fragmentShader);
            gMeshInstance->setShader(shaderProgram);
            
            this->instances.push_back(gMeshInstance);
        }
    }
};

void Wd40::loadPov()
{
    Pov* pov = this->scene->getPov();
    this->gCamera->eye = pov->getEye();
    this->gCamera->center = pov->getCenter();
    this->gCamera->vup = pov->getVup();
    this->gCamera->znear = pov->getZnear();
    this->gCamera->zfar = pov->getZfar();
    this->gCamera->fovy = pov->getFovy();
    this->gCamera->refreshTransform((float)this->scene->getWorldSettings()->getWidth(), (float)this->scene->getWorldSettings()->getHeight());
};

void Wd40::loadSound()
{
    // Start sound engine
    this->soundEngine = createIrrKlangDevice();
	this->soundEngine->setListenerPosition(vec3df(0, 0, 0), vec3df(0, 0, 1));
	this->soundEngine->setSoundVolume(0.25f); // master volume control
    this->music = soundEngine->play3D(this->scene->getWorldSettings()->getBackgroundMusic().c_str(), vec3df(0, 0, 10), true);
    if(this->music) this->music->setMinDistance(5.0f);
    
    const char* soundfile = this->scene->getWorldSettings()->getBackgroundMusic().c_str();
    if(soundfile == NULL) {
        std::cout << "Sound file is totally null\n" << std::endl;
    }
    this->soundEngine->play2D(soundfile);
}

void Wd40::controller()
{
    float dx = 0.025f;
    float dy = 0.01f;
    glm::vec3 lookLeft(-dx, 0, 0);
    glm::vec3 lookRight(dx, 0, 0);
    glm::vec3 lookUp(0, dx, 0);
    glm::vec3 lookDown(0, -dx, 0);
    glm::vec3 forward(0, 0, dx);
    glm::vec3 back(0, 0, -dx);
    glm::vec3 spin(0, 0, 1);
    
    if(glfwGetKey(this->gWindow, 'W')){
        this->scene->getPov()->translate(lookUp);
    }
    if(glfwGetKey(this->gWindow, 'A')){
        this->scene->getPov()->translate(lookLeft);
    }
    if(glfwGetKey(this->gWindow, 'S')){
        this->scene->getPov()->translate(lookDown);
    }
    if(glfwGetKey(this->gWindow, 'D')){
        this->scene->getPov()->translate(lookRight);
    }
    if(glfwGetKey(this->gWindow, 'Q')){
        this->scene->getPov()->rotate(spin, -dy);
    }
    if(glfwGetKey(this->gWindow, 'E')){
        this->scene->getPov()->rotate(spin, dy);
    }
    if(glfwGetKey(this->gWindow, GLFW_KEY_UP)){
        this->scene->getPov()->translate(forward);
    }
    if(glfwGetKey(this->gWindow, GLFW_KEY_DOWN)){
        this->scene->getPov()->translate(back);
    }
}

int main(int numArgs, char **args)
{
    // check usage
	if (numArgs < 2) {
		cout << "Usage: Transforms sceneFile.scene" << endl;
		exit(0);
	}
    
    Wd40* w = new Wd40();
    w->loadScene(args[1]);
    w->loadWorldSettings();
    w->loadPov();
    w->loadSound();
    w->loadMeshes();
    w->loadMeshInstances();
    
    double startTime = TIME();
    while(true) {
        w->render();
        w->controller();
        w->loadPov();
        
        // handle input
		glfwPollEvents();
		//if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
		if (glfwWindowShouldClose(w->getWindow()) != 0) break;
        
		double xx, yy;
		glfwGetCursorPos(w->getWindow(), &xx, &yy);
		//printf("%1.3f %1.3f ", xx, yy);
        
		// print framerate
		double endTime = TIME();
		//printf("\rFPS: %1.0f  ", 1.0/(endTime-startTime));
		startTime = endTime;
        
		// swap buffers
        //SLEEP(1); // sleep 1 millisecond to avoid busy waiting
		glfwSwapBuffers(w->getWindow());
    }
    glfwTerminate();
    return 0;
};