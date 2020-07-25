#include "Test.h"

namespace test {

    class TestMesh : public Test
    {
        public:

            TestMesh();
            ~TestMesh() {}
            virtual void OnUpdate( ) override;
            virtual void OnRender(  ) override;
            virtual void OnImGuiRender(  ) override;
            virtual void OnImGuiPlot(  ) override;

            virtual bool hasPlot(  ) override { return plotEnabled; }

        private:

            double m_Timer;
            bool plotEnabled;
    };
}