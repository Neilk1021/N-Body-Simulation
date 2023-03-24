#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderPipeline.h"
#include "Mass.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

VertexArray * m_va;
IndexBuffer * m_ib;
Shader * m_shader;
RenderPipeline * m_RP;

void SpawnI(GLFWwindow* window, int button, int action, int mods)
{
    double Xpos;
    double Ypos;

    float XVel = std::rand() % 3 - 1.5f;
    float YVel = std::rand() % 3 - 1.5f;

    glm::vec2 Pos(0, 0);
    glm::vec2 Vel(XVel, YVel);

    if (button != 0 || action != 0)
    {
        return;
    }

    GLCALL(glfwGetCursorPos(window, &Xpos, &Ypos))
        Pos.x = -640 + Xpos;
    Pos.y = 360 - Ypos;   

    std::cout << Xpos << "    " << Ypos << std::endl;

    new Mass(Pos, 1000, Vel, *m_va, *m_ib, *m_shader, *m_RP);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "N-Body Simulation -- Neil K.", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //set with vsync
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    float Points[] = {
        //verticies             colormap
        -4.0f,-4.0f, 0.0f,    1.0f, 0.0f, 0.0f,
        4.0f, -4.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        4.0f, 4.0f, 0.0f,     0.0f, 0.0f, 1.0f,
        -4.0f, 4.0f, 0.0f,    1.0f, 0.0f, 1.0f
    };

    unsigned int indicies[] = {
        0,1,2,
        2,3,0
    };

    VertexArray va;
    va.Bind();
    VertexBuffer vb(Points, 4 * 6 * sizeof(float));

    VertexBufferLayout layout;
    //push the first 3 vals per group in their own layout (can be accessed by shader)
    layout.Push<float>(3);
    //push the next 3 vals per group in their own layout (can be accessed by shader)
    layout.Push<float>(3);
    //compiles to a single VertexArray
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6);

    float X = -100;
    float iX = 0.5;
    float Y = 0;
    float iY = 0.5;

    glm::mat4 proj = glm::ortho(-640.f, 640.0f, -360.0f, 360.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 mvp = proj * view;

    Shader shader("res/shaders/basic.shader");
    shader.Bind();

    //uniform color shit
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    va.Unbind();
    shader.Unbind();
    ib.Unbind();
    RenderPipeline RP;
    glm::vec2 P1(0.0f, 0.0f);
    glm::vec2 P2(100.0f, -300.0f);
    glm::vec2 P3(-200.0f, 300.0f);

    glm::vec2 V1(0.0f, 0.0f);
    glm::vec2 V2(1.3f, 1.0f);
    glm::vec2 V3(-0.3f, -0.8f);

    Mass m1(P1, 10000000, V1, va, ib, shader, RP);

    m_va = &va;
    m_ib = &ib;
    m_shader = &shader;
    m_RP = &RP;

    glfwSetMouseButtonCallback(window, &SpawnI);
    //Mass m2(P2, 40, V2, va, ib, shader, RP);
    //Mass m4(P3, 80, V3, va, ib, shader, RP);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        RP.Clear();

        shader.Bind();

        for (unsigned int i = 0; i < m1.Bodies.size(); i++)
        {
            m1.Bodies[i]->RenderBody();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}