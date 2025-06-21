#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class Model
{
public:
    vector<Mesh> meshes;
    Model(const std::string& path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    // model data
    vector<Texture> textures_loaded;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
};
