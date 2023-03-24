#include "RenderPipeline.h"

void RenderPipeline::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const 
{
    shader.Bind();

    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void RenderPipeline::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
