#include <glad/gl.h>
#include <vector>

namespace momo {

struct VertexBufferElement
{
    unsigned type; // primitive type of vertex data
    unsigned count; // how many primitives per vertex
    unsigned normalized;

    static unsigned get_sizeof_type(unsigned type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        case GL_UNSIGNED_INT:
            return 4;
        default:
            return 0;
        }
        return 0;
    }
};

class VertexBufferLayout
{

  public:
    VertexBufferLayout() = default;

    template<typename T>
    void push(unsigned count);

    template<>
    void push<float>(unsigned count)
    {
        elements.push_back({ GL_FLOAT, count, GL_FALSE });
        stride += count * VertexBufferElement::get_sizeof_type(GL_FLOAT);
    }

    template<>
    void push<unsigned>(unsigned count)
    {
        elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        stride += count * VertexBufferElement::get_sizeof_type(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned count)
    {
        elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        stride += count * VertexBufferElement::get_sizeof_type(GL_UNSIGNED_BYTE);
    }

    [[nodiscard]] const std::vector<VertexBufferElement>& get_elements() const { return elements; }
    [[nodiscard]] unsigned get_stride() const { return stride; }


  private:
    std::vector<VertexBufferElement> elements;
    unsigned stride = 0;
};


} // namespace momo