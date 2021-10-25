#include "index_buffer.hpp"

#include <glad/gl.h>

namespace momo {


IndexBuffer::IndexBuffer(const unsigned* data, unsigned count) : count(count)
{
    glGenBuffers(1, &render_id); // gen vertex buffer id
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id); // bind the newly generated id
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW); // load data into buffer
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &render_id);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, render_id); // for rebinding VBO
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // for unbinding VBO
}

} // namespace momo