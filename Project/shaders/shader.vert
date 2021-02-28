#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texUV;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 textureCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

    textureCoord = texUV;

    normal = mat3(transpose(inverse(model))) * norm;

    fragPos = (model * vec4(pos, 1.0f)).xyz;
}
