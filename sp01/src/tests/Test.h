#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

class Renderer;

namespace test
{
    class Test
    {
    protected:
        Renderer* m_Renderer;
    public:
        Test() :m_Renderer(nullptr) {}
        virtual ~Test() {}

        void set_renderer(Renderer* renderer) { m_Renderer = renderer; }

        virtual void on_update(float deltatime) {}
        virtual void on_render() {}
        virtual void on_render_imgui() {}
    };

    class TestMenu : public Test
    {
    private:
        Test*& m_Current;
        std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
    public:
        TestMenu(Test*& current) :m_Current(current) {}

        template<typename T>
        void register_test(std::string name)
        {
            std::cout << "register test: " << name << '\n';

            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }

        void on_render_imgui();
    };
}


