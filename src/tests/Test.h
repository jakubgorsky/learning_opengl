//
// Created by kubag on 10/06/2022.
//

#ifndef OPENGL_TEST_H
#define OPENGL_TEST_H

namespace test {
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };
}


#endif //OPENGL_TEST_H
