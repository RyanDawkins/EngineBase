
//-------------------------------------------------------------------------//
// EngineUtil.h
// Some utility stuff - file reading and such
//
// David Cline
// 8/23/2014
//-------------------------------------------------------------------------//

#ifndef __EngineBase__EngineUtil__
#define __EngineBase__EngineUtil__

// Prevent visual studio warnings
#define _CRT_SECURE_NO_WARNINGS

// some standard includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
using namespace std;

// lodePNG stuff (image reading)
#include "lodepng.h"

// OpenGL related includes
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Sound (irrKlang)
#include <irrKlang.h>
using namespace irrklang;

//-------------------------------------------------------------------------//
// MISCELLANEOUS
//-------------------------------------------------------------------------//

void ERROR(const string &msg, bool doExit = true);
double TIME(void);
void SLEEP(int millis);

//-------------------------------------------------------------------------//
// TEMPLATES
//-------------------------------------------------------------------------//

template<class T> class NameVal
{
public:
	string name;
	T val;
	NameVal() { name = ""; }
	NameVal(string &n, T &v) { name = n; val = v; }
};

template<class T> class NameIdVal
{
public:
	string name;
	int id;
	T val;
	NameIdVal() { name = ""; id = -1; }
	NameIdVal(string &n, int i, T &v) { name = n; id = i; val = v; }
};

//-------------------------------------------------------------------------//
// OPENGL STUFF
//-------------------------------------------------------------------------//

#define MAJOR_VERSION 4
#define MINOR_VERSION 1
GLFWwindow* createOpenGLWindow(int width, int height, const char *title, int samplesPerPixel=0);

#define NULL_HANDLE 0
GLuint loadShader(const string &fileName, GLuint shaderType);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

//-------------------------------------------------------------------------//
// GLM UTILITY STUFF
//-------------------------------------------------------------------------//

inline void printVec(const glm::vec2 &v) { printf("[%1.3f %1.3f]\n", v[0], v[1]); }
inline void printVec(const glm::vec3 &v) { printf("[%1.3f %1.3f %1.3f]\n", v[0], v[1], v[2]); }
inline void printVec(const glm::vec4 &v) { printf("[%1.3f %1.3f %1.3f %1.3f]\n", v[0], v[1], v[2], v[3]); }
inline void printQuat(const glm::quat &q) { printf("[%1.3f %1.3f %1.3f %1.3f]\n", q[0], q[1], q[2], q[3]); }
void printMat(const glm::mat4x4 &m);

//-------------------------------------------------------------------------//
// FILE READING
//-------------------------------------------------------------------------//

void addToPath(const string &p);
void removeFromPath(const string &p);
void printPath();

bool getFullFileName(const string &fileName, string &fullName);
FILE *openFileForReading(const string &fileName);

bool getToken(FILE *f, string &token, const string &oneCharTokens);
int getFloats(FILE *f, float *a, int num);
int getInts(FILE *f, int *a, int num);

bool loadFileAsString(const string &fileName, string &buffer);

void replaceIncludes(string &src, string &dest, const string &directive, 
	string &alreadyIncluded, bool onlyOnce);

//-------------------------------------------------------------------------//
// SOUND
//-------------------------------------------------------------------------//

void initSoundEngine(void);
ISound *loadSound();

//-------------------------------------------------------------------------//
// IMAGE
//-------------------------------------------------------------------------//

class RGBAImage
{
public:
	string name;
	vector<unsigned char> pixels;
	unsigned int width, height;
	GLuint textureId;
	GLuint samplerId;

	RGBAImage(void) { width = 0; height = 0; textureId = NULL_HANDLE; samplerId = NULL_HANDLE; }
	~RGBAImage();
	bool loadPNG(const string &fileName, bool doFlipY = true);
	bool writeToPNG(const string &fileName);
	void flipY(void);
	void sendToOpenGL(GLuint magFilter, GLuint minFilter, bool createMipMap);

	unsigned int &operator()(int x, int y) {
		return pixel(x, y);
	}
	unsigned int &pixel(int x, int y) {
		unsigned int *A = (unsigned int*)&pixels[0];
		return A[y*width + x];
	}
	void sendToOpenGL(void) {
		sendToOpenGL(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true);
	}
};

//-------------------------------------------------------------------------//
// TRANSFORM
//-------------------------------------------------------------------------//

class Transform
{
public:
	// make transform class
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;

	glm::mat4x4 transform;
	glm::mat4x4 invTransform;

	void refreshTransform(void)
	{
		glm::mat4x4 Mtrans = glm::translate(translation);
		glm::mat4x4 Mscale = glm::scale(scale);
		glm::mat4x4 Mrot = glm::toMat4(rotation);
		transform = Mtrans * Mrot * Mscale;  // transforms happen right to left
		invTransform = glm::inverse(transform);
	}
};

//-------------------------------------------------------------------------//
// Camera
//-------------------------------------------------------------------------//

class Camera
{
public:
	// look from, look at, view up
	glm::vec3 eye, center, vup;

	float fovy; // vertical field of view
	float znear, zfar; // near and far clip planes

	glm::mat4x4 worldViewProject;

	void refreshTransform(float screenWidth, float screenHeight) {
		glm::mat4x4 worldView = glm::lookAt(eye, center, vup);
		glm::mat4x4 project = glm::perspective((float)fovy,
			(float)(screenWidth / screenHeight), (float)znear, (float)zfar);
		worldViewProject = project * worldView;
	}

	void translateGlobal(glm::vec3 &t) { eye += t; center += t; }
	void translateLocal(glm::vec3 &t) {
		glm::vec3 zz = glm::normalize(eye - center);
		glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
		glm::vec3 yy = glm::cross(zz, xx);
		glm::vec3 tt = t.x*xx + t.y*yy + t.z*zz;
		eye += tt; center += tt;
	}

	void rotateGlobal(glm::vec3 axis, float angle) {
		glm::mat4x4 R = glm::axisAngleMatrix(axis, angle);
		glm::vec4 zz = glm::vec4(eye - center, 0);
		glm::vec4 Rzz = R*zz;
		center = eye - glm::vec3(Rzz);
		//
		glm::vec4 up = glm::vec4(vup, 0);
		glm::vec4 Rup = R*up;
		vup = glm::vec3(Rup);
	}
	void rotateLocal(glm::vec3 axis, float angle) { 
		glm::vec3 zz = glm::normalize(eye - center);
		glm::vec3 xx = glm::normalize(glm::cross(vup, zz));
		glm::vec3 yy = glm::cross(zz, xx);
		glm::vec3 aa = xx*axis.x + yy*axis.y + zz*axis.z;
		rotateGlobal(aa, angle);
	}
};

//-------------------------------------------------------------------------//
// MATERIAL
//-------------------------------------------------------------------------//

class Material
{
public:
	GLuint shaderProgram;
	vector< NameIdVal<glm::vec4> > colors;
	vector< NameIdVal<RGBAImage*> > textures;
	void bindMaterial(Transform &T, Camera &camera);
};

//-------------------------------------------------------------------------//
// TRIANGLE MESH
//-------------------------------------------------------------------------//

class TriMesh
{
public:
	string name;
	vector<string> attributes;
	vector<float> vertexData;
	vector<int> indices;
	int numIndices;
    
	GLuint vao; // vertex array handle
	GLuint ibo; // index buffer handle
	
	bool readFromPly(const string &fileName, bool flipZ = false);
	bool sendToOpenGL(void);
	void draw(void);
};

class TriMeshInstance 
{
public:
	TriMesh *triMesh;
	Transform T;
	Material mat;
	
public:
	TriMeshInstance(void);
    
	void setMesh(TriMesh *mesh) { triMesh = mesh; }
	void setScale(const glm::vec3 &s) { T.scale = s; }
	void setRotation(const glm::quat &r) { T.rotation = r; }
	void setTranslation(const glm::vec3 &t) { T.translation = t; }
    
	void refreshTransform(void);
    
	void draw(Camera *camera);
};

//-------------------------------------------------------------------------//
// Lights
//-------------------------------------------------------------------------//

class Light
{
public:
	// type is in attenuation.w
	glm::vec4 position, direction, color, attenuation, coneAngles;

	Light(const Light &L)
	{
		position = L.position; 
		direction = L.direction;
		color = L.color;
		attenuation = L.attenuation;
		coneAngles = L.coneAngles;
	}

	Light()
	{
		position = glm::vec4(0, 0, 0, 1);
		direction = glm::vec4(0, 1, 0, 0);
		color = glm::vec4(0, 0, 0, 0);
		attenuation = glm::vec4(0, 0, 0, 0);
		coneAngles = glm::vec4(0.5, 0.55, 0, 0);
	}
};

#define NO_LIGHT 0
#define AMBIENT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define POINT_LIGHT 3
#define SPOT_LIGHT 4
#define HEAD_LIGHT 5
#define RIM_LIGHT 6

#define MAX_LIGHTS 10
#define LIGHT_BUFFER_ID 1
extern GLuint gLightBufferObject;
extern int gNumLights;
extern Light gLights[MAX_LIGHTS];

void initLightBuffer(void);

//-------------------------------------------------------------------------//
// Scene
//-------------------------------------------------------------------------//

class Scene
{
public:
	// Global properties
	glm::vec3 backgroundColor;
	string backgroundMusic;

	// Object pools
	map<string, TriMesh*> meshes;
	map<string, RGBAImage*> textures;

	// Scene graph
	Camera camera;
	vector<TriMeshInstance*> meshInstances;

	// getters and setters
	void addMesh(TriMesh* mesh) { meshes[mesh->name] = mesh; }
	TriMesh *getMesh(string &n) {
		if (meshes.find(n) != meshes.end()) return meshes[n];
		else return NULL;
	}
	void addTexture(RGBAImage *tex) {
		textures[tex->name] = tex;
	}
	RGBAImage *getTexture(string &n) {
		if (textures.find(n) != textures.end()) return textures[n];
		else return NULL;
	}
	void addMeshInstance(TriMeshInstance *instance) {
		meshInstances.push_back(instance);
	}

	void updateLights(void)
	{
		// Update global lights
		glBindBuffer(GL_UNIFORM_BUFFER, gLightBufferObject);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light) * MAX_LIGHTS, gLights);
		//glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * MAX_LIGHTS, gLights, GL_STREAM_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0); // unbind buffer
	}

	void render(void) {
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateLights();

		for (int i = 0; i < (int)meshInstances.size(); i++) {
			meshInstances[i]->draw(&camera);
		}
	}
};

//-------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------//

#endif /* defined(__EngineBase__EngineUtil__) */