//
// Created by kubag on 10/06/2022.
//

#ifndef OPENGL_TEST_H
#define OPENGL_TEST_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace test {
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu : public Test{
    public:
        explicit TestMenu(Test*& currentTestPtr);
        ~TestMenu() {}

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registerign test " << name << '\n';

            m_Tests.push_back(std::make_pair(name, [](){ return new T();}));
        }
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}


#endif //OPENGL_TEST_H
