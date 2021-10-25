#include "vertex_buffer.hpp"
#include <glad/gl.h>

#include <cstddef>

namespace momo {


VertexBuffer::VertexBuffer(const void* data, unsigned count, unsigned type_size) : count(count)
{
    glGenBuffers(1, &render_id); // gen vertex buffer id
    glBindBuffer(GL_ARRAY_BUFFER, render_id); // bind the newly generated id
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(count) * type_size, data, GL_STATIC_DRAW); // load data into buffer
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, render_id); // for rebinding VBO
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // for unbinding VBO
}

} // namespace momo