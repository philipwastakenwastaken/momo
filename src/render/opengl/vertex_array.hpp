#pragma once

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include <glad/gl.h>


namespace momo {

    class VertexArray {

    public:
        VertexArray() {
            glGenVertexArrays(1, &render_id);
        }

        ~VertexArray() {
            glDeleteVertexArrays(1, &render_id);
        }

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

        void bind() const;
        void unbind() const;

        [[nodiscard]] unsigned get_render_id() const {return render_id;}
    private:
        unsigned render_id = 0;


    };

}