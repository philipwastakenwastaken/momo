#shader vertex
#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_col;
uniform mat4 proj;

out vec3 v_col;

void main() {
    gl_Position = proj * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
    v_col = a_col;
}

#shader fragment
#version 330 core
out vec4 frag_color;
in vec3 v_col;

void main() {
    frag_color = vec4(v_col.x, v_col.y, v_col.z, 1.0f);
}
