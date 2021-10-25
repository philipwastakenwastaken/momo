#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include <glm/glm.hpp>

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

namespace momo {

struct ShaderProgramSource
{
    std::string vertex_source;
    std::string fragment_source;
};

class Shader
{

  public:
    explicit Shader(std::string path) : file_path(std::move(path)), render_id(create_shader()) {}
    //Shader() = default;

    ~Shader();


    void bind() const;
    void unbind() const;

    void set_uniform1i(const std::string& name, int v1);
    void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

    [[nodiscard]] const std::string& get_file_path() const { return file_path; }
    [[nodiscard]] unsigned get_render_id() const { return render_id; }

  private:
    std::string file_path;
    unsigned render_id = 0;
    std::unordered_map<std::string, int> uniform_location_cache;


    unsigned compile_shader(unsigned type, const std::string& source);
    unsigned create_shader();
    ShaderProgramSource parse_shader();
    [[nodiscard]] int get_uniform_location(const std::string& name);
};

} // namespace momo