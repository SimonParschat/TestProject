#pragma once

#include "Test.h"
#include "PerlinNoise.h"
 
namespace test {

class GenVertices : public Test
{
public:
    std::vector<test::Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<float> m_PerlinTexture;
    PerlinNoise pn;
    
    int m_NumQuads, m_Octaves;
    float m_TextureScale, m_Persistance, m_Lacunarity;
    double m_FuncTimer;
    glm::vec3 m_Offset;
    
    GenVertices(    int nQuads, glm::vec3 offset, float heightMult = 1.0f, float angThreshold = 10.0f, int seed = 13, int octaves = 6,
                    float texscale = 25.0f, float persistance = 0.54f, float lacunarity = 2.2f )
        :   pn(seed), m_NumQuads(nQuads), m_Octaves(octaves), m_TextureScale(texscale), m_Persistance(persistance),
            m_Lacunarity(lacunarity), m_FuncTimer(0), m_Offset(offset)
    {
        float m_QuadSize = 1.0f;
        
        GeneratePerlinValue(offset);
        
        for ( int row = 0; row < m_NumQuads; row++ ) {
            for (int col = 0; col < m_NumQuads; col++ ) {
                
                int perlinRow = m_NumQuads+2;
                int perlinIndex = (row+1)*perlinRow + (col+1);
                                
                Vertex v0;
                v0.position = { col*m_QuadSize + m_Offset.x, HeightCurve(m_PerlinTexture[perlinIndex]) * heightMult, row*m_QuadSize + m_Offset.z  };
                v0.normal = glm::vec3(0.0f);
                
                if ((col-1+(row % 2)) % 2 == 0){
                    if ( row % 2 ) {
                        
                        float steep = Steepness( HeightCurve( m_PerlinTexture[perlinIndex-perlinRow] ) * heightMult,
                                                 HeightCurve( m_PerlinTexture[perlinIndex] ) * heightMult,
                                                 HeightCurve( m_PerlinTexture[perlinIndex+perlinRow] ) * heightMult);
                        
                        v0.enabled = steep >= glm::radians( angThreshold );
                        
                    } else {
                        float steep = Steepness( HeightCurve( m_PerlinTexture[perlinIndex-1] ) * heightMult,
                                                 HeightCurve( m_PerlinTexture[perlinIndex] ) * heightMult,
                                                 HeightCurve( m_PerlinTexture[perlinIndex+1] ) * heightMult);
                        
                        v0.enabled = steep >= glm::radians( angThreshold );
                    }
                } else {
                    v0.enabled = true;
                }
                v0.texCoordinates = glm::vec2((float)col / (float)nQuads, (float)row / (float)nQuads);
                m_Vertices.push_back(v0);
            }
        }
        
        for (int row = 1; row < m_NumQuads; row += 2) {
            for (int col = 1; col < m_NumQuads; col+=2) {
                                
                bool aboveV = m_Vertices[(row-1)*m_NumQuads + col].enabled;
                bool rightV = m_Vertices[(row)*m_NumQuads + col+1].enabled;
                bool leftV = m_Vertices[(row)*m_NumQuads + col-1].enabled;
                bool belowV = m_Vertices[(row+1)*m_NumQuads + col].enabled;
                
                glm::vec3 centerVertexP = m_Vertices[(row)*m_NumQuads + col].position;
                
                if (aboveV) {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col-1);
                    m_Indices.push_back((row-1)*m_NumQuads + col);
                    
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col+1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row-1)*m_NumQuads + col].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row-1)*m_NumQuads + col-1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col-1].normal);
                    m_Vertices[(row-1)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col].normal);
                    
                    glm::vec3 normal2 = glm::normalize( glm::cross( m_Vertices[(row-1)*m_NumQuads + col+1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row-1)*m_NumQuads + col].position -
                                                                   centerVertexP) );
                                                                               
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row-1)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col+1].normal = glm::normalize( normal2 + m_Vertices[(row-1)*m_NumQuads + col+1].normal);
                    
                    
                } else {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col-1);
                    m_Indices.push_back((row-1)*m_NumQuads + col+1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row-1)*m_NumQuads + col+1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row-1)*m_NumQuads + col-1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col-1].normal);
                    m_Vertices[(row-1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col+1].normal);
                }
                
                if (rightV) {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col+1);
                    m_Indices.push_back((row)*m_NumQuads + col+1);
                    
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row)*m_NumQuads + col+1);
                    m_Indices.push_back((row+1)*m_NumQuads + col+1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row)*m_NumQuads + col+1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row-1)*m_NumQuads + col+1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col+1].normal);
                    m_Vertices[(row)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col+1].normal);
                    
                    glm::vec3 normal2 = glm::normalize( glm::cross( m_Vertices[(row+1)*m_NumQuads + col+1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row)*m_NumQuads + col+1].position -
                                                                   centerVertexP) );
                                                                               
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row)*m_NumQuads + col+1].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col+1].normal);
                    m_Vertices[(row+1)*m_NumQuads + col+1].normal = glm::normalize( normal2 + m_Vertices[(row+1)*m_NumQuads + col+1].normal);
                    
                } else {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row-1)*m_NumQuads + col+1);
                    m_Indices.push_back((row+1)*m_NumQuads + col+1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row+1)*m_NumQuads + col+1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row-1)*m_NumQuads + col+1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row-1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col+1].normal);
                    m_Vertices[(row+1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col+1].normal);
                }
                
                if (belowV) {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col+1);
                    m_Indices.push_back((row+1)*m_NumQuads + col);
                    
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col-1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row+1)*m_NumQuads + col].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row+1)*m_NumQuads + col+1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col+1].normal);
                    m_Vertices[(row+1)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col].normal);
                    
                    glm::vec3 normal2 = glm::normalize( glm::cross( m_Vertices[(row+1)*m_NumQuads + col-1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row+1)*m_NumQuads + col].position -
                                                                   centerVertexP) );
                                                                               
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row+1)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col-1].normal = glm::normalize( normal2 + m_Vertices[(row+1)*m_NumQuads + col-1].normal);
                    
                } else {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col+1);
                    m_Indices.push_back((row+1)*m_NumQuads + col-1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row+1)*m_NumQuads + col-1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row+1)*m_NumQuads + col+1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col+1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col+1].normal);
                    m_Vertices[(row+1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col-1].normal);
                }

                if (leftV) {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col-1);
                    m_Indices.push_back((row)*m_NumQuads + col-1);
                    
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row)*m_NumQuads + col-1);
                    m_Indices.push_back((row-1)*m_NumQuads + col-1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross( m_Vertices[(row)*m_NumQuads + col-1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row+1)*m_NumQuads + col-1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col-1].normal);
                    m_Vertices[(row)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col-1].normal);
                    
                    glm::vec3 normal2 = glm::normalize( glm::cross(m_Vertices[(row-1)*m_NumQuads + col-1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row)*m_NumQuads + col-1].position -
                                                                   centerVertexP) );
                                                                               
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row)*m_NumQuads + col-1].normal = glm::normalize( normal2 + m_Vertices[(row)*m_NumQuads + col-1].normal);
                    m_Vertices[(row-1)*m_NumQuads + col-1].normal = glm::normalize( normal2 + m_Vertices[(row-1)*m_NumQuads + col-1].normal);
                    
                } else {
                    m_Indices.push_back((row)*m_NumQuads + col);
                    m_Indices.push_back((row+1)*m_NumQuads + col-1);
                    m_Indices.push_back((row-1)*m_NumQuads + col-1);
                    
                    glm::vec3 normal1 = glm::normalize( glm::cross(m_Vertices[(row-1)*m_NumQuads + col-1].position -
                                                                   centerVertexP,
                                                                   m_Vertices[(row+1)*m_NumQuads + col-1].position -
                                                                   centerVertexP) );
                    
                    m_Vertices[(row)*m_NumQuads + col].normal = glm::normalize( normal1 + m_Vertices[(row)*m_NumQuads + col].normal);
                    m_Vertices[(row+1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row+1)*m_NumQuads + col-1].normal);
                    m_Vertices[(row-1)*m_NumQuads + col-1].normal = glm::normalize( normal1 + m_Vertices[(row-1)*m_NumQuads + col-1].normal);
                }
            }
        }
    }
    
    ~GenVertices() {};
    
    float SinContent( const float& piMult, const int& row, const int& col, const int& quadSize, const int& numQuads, const int& yesX, const int& yesZ ) {
        return  glm::sin( piMult*test::m_PI*(float)(row*quadSize+yesX)/(float)(numQuads) ) +
                glm::cos(piMult*test::m_PI*(float)(col*quadSize+yesZ)/(float)(numQuads) );
    }
    
    float MengerCurvature( const float& x, const float& y, const float& z ) {
        
        glm::vec3 f_BehindVec = glm::normalize( glm::vec3( -1.0f, x - y, 0.0f ) );
        glm::vec3 f_FrontVec = glm::normalize( glm::vec3( 1.0f, z - y, 0.0f ) );
        
        float dotVec = glm::dot( f_FrontVec, f_BehindVec );
        float absA = glm::length( f_FrontVec );
        float absB = glm::length( f_BehindVec );
        float angle = glm::acos( dotVec / (absA * absB) );
                
        float xMinz = ( glm::abs(x - z) > 0.1f ) ? glm::abs(x - z) : 0.1f;
        float curvature = 2.0f * glm::sin( angle ) / xMinz;
        
        float radius = ( curvature > 0.1f ) ? ( 1.0f / curvature ) : 10.0f;
                
        return 1.0f - ( (radius - 1.0f) / ( 10.0f - 1.0f) );
    }
    
    float Steepness( const float& x, const float& y, const float& z) {
        
        glm::vec3 upVec = glm::normalize( glm::vec3(-1.0f, x - y, 0.0f) );
        glm::vec3 forwardVec = glm::normalize( glm::vec3(1.0f, z - y, 0.0f) );
                               
        return (glm::abs( glm::dot(forwardVec, upVec) ) > 0.99) ? 0.0f : glm::acos( glm::abs( glm::dot(forwardVec, upVec) ) );
    }
    
    float HeightCurve( float height )
    {
        return glm::exp(2.0f*height - 2.0f);
    }
    
    void GeneratePerlinValue(glm::vec3 f_Offset)
    {
        double start = glfwGetTime();
        
        for ( int row = 0; row < m_NumQuads+2; row++ ){
            for ( int col = 0; col < m_NumQuads+2; col++ ) {
                float m_MaxNoiseHeight = 1.0f;
                float m_MinNoiseHeight =  -1.0f;
                
                if (m_TextureScale <= 0.00001f)
                {
                    m_TextureScale = 0.00001f;
                }
                
                float amplitude = 1.0f ;
                float frequency = 1.0f;
                float noiseHeight = 0.0f;
                
                for (int oct = 0; oct < m_Octaves; oct++)
                {
                    float sampleX = ( ((float)col+f_Offset.x) / m_TextureScale * frequency);
                    float sampleY = ( ((float)row+f_Offset.z)  / m_TextureScale * frequency);
                    double perlinValue =  pn.noise( sampleX, sampleY, 0.0f ) * 2.0f - 1.0f;
                    noiseHeight += perlinValue * amplitude;
                    
                    amplitude *= m_Persistance;
                    frequency *= m_Lacunarity;
                }
                m_PerlinTexture.push_back( ( noiseHeight - m_MinNoiseHeight ) / ( m_MaxNoiseHeight - m_MinNoiseHeight ) );
            }
        }
        m_FuncTimer += glfwGetTime() - start;
    }
};

}
