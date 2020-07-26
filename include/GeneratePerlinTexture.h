#pragma once

#include "Test.h"
#include "PerlinNoise.h"

namespace test {

class GeneratePerlinTexture
{
public:
//    This is the main container for the texture.
    std::vector<float> m_PerlinTexture;
/*
m_MeshSize      : Specifies the number of dimensions for the texture.
m_PerlinSeed    : Sets the randomized seed for the noise generation.
m_Octaves       : How many harmonics used to generate the noise.
m_TextureScale  : Scaling the noise.
m_Persistance   : More noise details.
m_Lacunarity    : Final noise detail.
m_Offset        : For scrolling the texture.
*/
    GeneratePerlinTexture(  int m_MeshSize, int m_PerlinSeed = 11, int m_Octaves = 4, float m_TextureScale = 8.0f,
                            float m_Persistance = 0.5f, float m_Lacunarity = 2.0f, glm::vec2 m_Offset = glm::vec2(0.0f, 0.0f) )
    {
        PerlinNoise pn( m_PerlinSeed );
        m_MeshSize = m_MeshSize + 1;
        
        float m_MaxNoiseHeight = 1.0f;
        float m_MinNoiseHeight =  -1.0f;
        
        if (m_TextureScale <= 0.00001f)
        {
            m_TextureScale = 0.00001f;
        }
        
        for ( int y = 0; y < m_MeshSize; y++ ){
            for (int x = 0; x < m_MeshSize; x++) {
                
                float amplitude = 1.0f ;
                float frequency = 1.0f;
                float noiseHeight = 0.0f;
                
                for (int oct = 0; oct < m_Octaves; oct++)
                {
                    float sampleX = (( (float)x - (float)m_MeshSize/2.0f) / m_TextureScale * frequency) + (m_Offset.x - (float)m_MeshSize/2.0f) / m_TextureScale * frequency;
                    float sampleY = (( (float)y - (float)m_MeshSize/2.0f) / m_TextureScale * frequency) + (m_Offset.y - (float)m_MeshSize/2.0f) / m_TextureScale * frequency;
                    double perlinValue =  pn.noise( sampleX, sampleY, 0.0f ) * 2.0f - 1.0f;
                    noiseHeight += perlinValue * amplitude;
                    
                    amplitude *= m_Persistance;
                    frequency *= m_Lacunarity;
                }
                m_PerlinTexture.push_back( ( noiseHeight - m_MinNoiseHeight ) / ( m_MaxNoiseHeight - m_MinNoiseHeight ) );
            }
        }
    }
    
    ~GeneratePerlinTexture() {};
};

}

