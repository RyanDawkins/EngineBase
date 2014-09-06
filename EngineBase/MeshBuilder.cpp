//
// Created by Dawkins on 9/4/14.
// Copyright (c) 2014 dave. All rights reserved.
//

#include "MeshBuilder.h"

MeshBuilder::MeshBuilder()
{
    this->constructor(NULL);
}

MeshBuilder::MeshBuilder(json11::Json* json)
{
    this->constructor(json);
}

void MeshBuilder::constructor(json11::Json* json)
{
    this->setJson(json);
}

json11::Json* MeshBuilder::getJson()
{
    return this->json;
}

MeshBuilder* MeshBuilder::setJson(json11::Json* json) {
    this->json = json;
    return this;
}

std::vector<Mesh*>* MeshBuilder::forgeMeshes()
{
    if(!(*this->json).is_array()) {
        std::cout << "HOLY CRAP";
        exit(1);
    }
    std::vector<json11::Json> jitems = (*this->json).array_items();

    std::vector<Mesh*>* meshes = new std::vector<Mesh*>(jitems.size());
    for(int i = 0; i < jitems.size(); i++) {

        // Creating our Mesh with the correct instances size.
        Mesh* mesh = new Mesh(jitems[i]["instances"].array_items().size());
        mesh->setFile(jitems[i]["file"].string_value());
        mesh->setName(jitems[i]["name"].string_value());

        std::vector<json11::Json> meshInstances = jitems[i]["instances"].array_items();
        for(int j = 0; j < meshInstances.size(); j++) {

            // Forging our mesh instance
            MeshInstance* meshInstance = new MeshInstance();
            meshInstance->setName(meshInstances[i]["name"].string_value());
            meshInstance->setScale(this->readScale(meshInstances[i]["scale"].array_items()));
            meshInstance->setVertexShade(meshInstances[i]["vertexShader"].string_value());
            meshInstance->setFragmentShader(meshInstances[i]["fragmentShader"].string_value());
            meshInstance->setDiffuseTexture(meshInstances[i]["diffuseTexture"].string_value());
            if(mesh != NULL)
                mesh->addInstance(meshInstance);
        }

        // Adding our mesh to the junk
        meshes->push_back(mesh);
    }

    return meshes;
};

glm::vec4 MeshBuilder::readScale(json11::Json::array items)
{
    glm::vec4 scale;

    // If the value exists, then we know it is the x, and so on.
    if(items.size() > 0) {
        scale.x= items[0].number_value();
    } else {
        scale.x = 1;
    }
    if(items.size() > 1) {
        scale.y = items[1].number_value();
    } else {
        scale.y = 1;
    }
    if(items.size() > 2) {
        scale.z = items[2].number_value();
    } else {
        scale.z = 1;
    }
    
    return scale;
}