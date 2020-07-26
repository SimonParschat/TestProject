#include "TestMesh.h"
#include "LogFunc.h"

namespace test {

    TestMesh::TestMesh()
        :   plotEnabled( false ), m_NumberQuads( 101 ),
            m_Proj( glm::perspective( glm::radians( 45.0f ), 480.0f / 300.0f, 0.1f, 1000.0f ) ),
            m_View( glm::mat4( 1.0f ) ), m_Model( glm::mat4( 1.0f ) ), m_Translation( 0.0f, 100.0f, 0.0f ),
            m_ViewDirection(0.0f, 0.0f, -1.0f), m_CameraRight(1.0f,0.0f,0.0f), m_CameraUP(0.0f,1.0f,0.0f),
            m_RotateX(0.8f), m_RotateY(-0.7f), m_RotationVelocity(0.05f), m_Velocity(0.5f), m_RotAngle(0.01f),
            m_Wireframe( false ), m_HeightMult( 1.0f), m_UpdateDelay( 2.0f ), m_MeshPosition(0.0f)
    {
        TEST_INFO("TestMesh Constructed");
        m_Timer = glfwGetTime();

        m_Shader = std::make_unique< test::Shader >( "/Users/Simon/Desktop/TestProject/graphics/shaders/basic.shader" );

        GenVertices m_VertexList( m_NumberQuads, m_MeshPosition, m_HeightMult );

        m_LandMesh.push_back( std::make_unique<test::Mesh>( m_VertexList.m_Indices, ((m_NumberQuads-1)*(m_NumberQuads-1)/4 )*24 ) );
        m_LandMesh.back()->Update( m_VertexList.m_Vertices, m_VertexList.m_Indices );

        m_Texture = m_VertexList.m_PerlinTexture;
        
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_NumberQuads+2, m_NumberQuads+2, 0, GL_RED, GL_FLOAT, &m_Texture );
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void TestMesh::OnUpdate( glm::vec3 direction, glm::vec2 rotation )
    {
        if( glfwGetTime() >= m_Timer+2.0f ) {
            TEST_INFO("TestMesh On Update");
            m_Timer = glfwGetTime();
        }

    //************************************ CAMERA STUFF ************************************
    
        float deltaTime = 100.0f / ImGui::GetIO().Framerate;
        
        float xAngVelocity = rotation.x * m_RotationVelocity * deltaTime;
        float yAngVelocity = rotation.y * m_RotationVelocity * deltaTime;
        float maxRot = ( 4.0f / 180.0f ) * test::m_PI;
        m_RotateY -= (abs(xAngVelocity) > maxRot) ? maxRot * rotation.x : xAngVelocity;
        m_RotateX += (abs(yAngVelocity) > maxRot) ? maxRot * rotation.y : yAngVelocity;
        float minRad = -2.0f*test::m_PI;
        float maxRad = 2.0f*test::m_PI;
        
        if ( m_RotateY >= maxRad)
            m_RotateY = minRad;
        else if ( m_RotateY <= minRad)
            m_RotateY = maxRad;
        if ( m_RotateX >= maxRad)
            m_RotateX = minRad;
        else if ( m_RotateX <= minRad)
            m_RotateX = maxRad;
        
        glm::vec3 dir;
        dir.x = cos( m_RotateX ) * cos( m_RotateY );
        dir.y = sin( m_RotateY );
        dir.z = sin( m_RotateX ) * cos( m_RotateY );
        m_ViewDirection = glm::normalize( dir );
        
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_CameraRight = glm::cross( m_ViewDirection, up );
        m_CameraRight = (abs(m_RotateY) > test::m_PI/2.0f) ? -m_CameraRight : m_CameraRight;
        m_CameraUP = glm::cross( m_CameraRight, m_ViewDirection );
        
        glm::vec3 xzDirection = glm::normalize(glm::vec3(m_ViewDirection.x, 0.0, m_ViewDirection.z));
        glm::vec3 rightDirection = glm::normalize(glm::vec3(m_CameraRight.x, 0.0, m_CameraRight.z));
        
        m_Translation.x += m_Velocity * deltaTime * (xzDirection.x * direction.z + rightDirection.x * direction.x);
        m_Translation.y += m_Velocity * 2.0f * direction.y * deltaTime;
        m_Translation.z += m_Velocity * deltaTime * (xzDirection.z * direction.z + rightDirection.z * direction.x);
        
    //**************************************************************************************
    }

    void TestMesh::OnRender()
    {
        glClearColor( 0.0f, 0.3f, 0.7f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        if( glfwGetTime() >= m_Timer+m_UpdateDelay ) {
            TEST_INFO("TestMesh Updated");

            GenVertices m_VertexList( m_NumberQuads, m_MeshPosition, m_HeightMult );
            m_LandMesh.back()->Update( m_VertexList.m_Vertices, m_VertexList.m_Indices );
            m_Texture = m_VertexList.m_PerlinTexture;
        }

        glm::vec3 lightDirection = glm::vec3( 0.0f, 1.0f, 0.0f );
        
        m_View = glm::lookAt(   m_Translation,
                                m_Translation + m_ViewDirection,
                                m_CameraUP     );
            
        m_View *= glm::mat4( glm::rotate( glm::mat4(1.0f), glm::radians( m_RotateY ), glm::vec3( 0.0f, 1.0f, 0.0f ) ) );
            
        m_Shader->Bind();
        m_Shader->SetUniformMatrix4fv("projectionMat", 1, GL_FALSE, glm::value_ptr( m_Proj ) );
        m_Shader->SetUniformMatrix4fv("viewMat", 1, GL_FALSE, glm::value_ptr( m_View ) );
        m_Shader->SetUniformMatrix4fv("modelMat", 1, GL_FALSE, glm::value_ptr( m_Model ) );
        m_Shader->SetUniform3fv ("u_LightDirection", 1, glm::value_ptr( lightDirection ) );
            
        if ( m_Wireframe ) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (auto &i : m_LandMesh ) {
            m_Shader->Bind();
            glBindTexture(GL_TEXTURE_2D, m_textureID);
            i->Draw( *m_Shader );
        }
        if ( m_Wireframe ) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void TestMesh::OnImGuiRender()
    {
        ImGui::Text( "Position: %.1f, %.1f, %.1f", m_Translation.x, m_Translation.y, m_Translation.z );
        ImGui::Text( "Rotation X: %.1f, Y: %.1f ", m_RotateX, m_RotateY );

        ImGui::SliderFloat3("Mesh Pos", &m_MeshPosition.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Height Mult:", &m_HeightMult, 0.f, 100.f);
        ImGui::InputFloat("Update delay", &m_UpdateDelay);

        if ( ImGui::Button("Wireframe") ) {
        if ( m_Wireframe ) { m_Wireframe = false; }
        else { m_Wireframe = true; }
    }
    }

    void TestMesh::OnImGuiPlot()
    {}

}