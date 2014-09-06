//
// Created by Dawkins on 9/4/14.
// Copyright (c) 2014 dave. All rights reserved.
//


#include "json11.hpp"
#include "Mesh.h"
#include <vector>

#ifndef __MeshBuilder_H_
#define __MeshBuilder_H_


class MeshBuilder {
private:
    json11::Json* json;
    glm::vec4 readScale(json11::Json::array items);
public:
    MeshBuilder();
    MeshBuilder(json11::Json* json);
    void constructor(json11::Json* json);

    json11::Json* getJson();
    MeshBuilder* setJson(json11::Json* json);

    std::vector<Mesh*>* forgeMeshes();
};


#endif //__MeshBuilder_H_
