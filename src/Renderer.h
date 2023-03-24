#pragma once
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
//Error handling for every gl call.
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

