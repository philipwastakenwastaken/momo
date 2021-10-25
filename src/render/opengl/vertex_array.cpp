#include "vertex_array.hpp"


namespace momo {


void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned offset = 0;

    for (u32 i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, i32(element.count), element.type, u8(element.normalized), i32(layout.get_stride()), (const void*)offset);
        offset += element.count * VertexBufferElement::get_sizeof_type(element.type);
    }
}

void VertexArray::bind() const { glBindVertexArray(render_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

} // namespace momo