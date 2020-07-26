#include "Test.h"
#include "Shader.h"
#include "Mesh.h"
#include "GenerateVertices.h"
#include "GeneratePerlinTexture.h"

namespace test {

    class TestMesh : public Test
    {
        public:

            TestMesh();
            ~TestMesh() {}
            virtual void OnUpdate( glm::vec3, glm::vec2 ) override;
            virtual void OnRender(  ) override;
            virtual void OnImGuiRender(  ) override;
            virtual void OnImGuiPlot(  ) override;

            virtual bool hasPlot(  ) override { return plotEnabled; }

        private:

            double m_Timer;
            bool plotEnabled;
            int m_NumberQuads;
            std::unique_ptr< test::Shader > m_Shader;
            std::vector< std::unique_ptr< test::Mesh > > m_LandMesh;
            std::vector< float > m_Texture;

            glm::mat4 m_Proj, m_View, m_Model;
            glm::vec3 m_Translation, m_ViewDirection, m_CameraRight, m_CameraUP;
            float m_RotateX, m_RotateY;
            float m_RotationVelocity, m_Velocity, m_RotAngle;
            bool m_Wireframe;
            float m_HeightMult, m_UpdateDelay;
            glm::vec3 m_MeshPosition;
            unsigned int m_textureID;
    };
}