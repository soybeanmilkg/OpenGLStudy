#pragma once
#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    private:
        float m_Color[4];
    public:
        TestClearColor();

        void on_render();
        void on_render_imgui();
    };
}

