#pragma once
#include "shader.h"
using namespace std;

//each vertex has position vector, normal vector and texture coordinate vector
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};


// id of the texture and its type (diffuse or specular texture)
struct Texture {
    unsigned int id;
    string type;
    string path;
};
class Mesh {
public:
    // Mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader& shader);
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};