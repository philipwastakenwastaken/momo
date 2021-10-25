#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

namespace momo {

class VertexBuffer
{

  public:
    VertexBuffer(const void* data, unsigned count, unsigned type_size);
    ~VertexBuffer() = default;
    VertexBuffer() = default;

    void bind() const;
    void unbind() const;

    [[nodiscard]] unsigned get_render_id() const { return render_id; }
    [[nodiscard]] unsigned get_count() const { return count; }

  private:
    u32 render_id;
    u32 count;
};
} // namespace momo