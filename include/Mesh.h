#pragma once

#include "Test.h"
#include "Shader.h"
#include "PerlinNoise.h"

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace test {

class Mesh
{
private:
    int m_MaxIndices;
    bool m_Updated;
    
    unsigned int VAO, VBO, EBO;
    
    void setupMesh();
    
public:
    
    std::vector<test::Vertex> vertices;
    std::vector<unsigned int> indices;
    
    Mesh( const std::vector<unsigned int>&, const int& );
    ~Mesh() {};
    
    void Draw(const Shader &shader);
    void Update( const std::vector<test::Vertex>&, const std::vector<unsigned int>& );
};

}

