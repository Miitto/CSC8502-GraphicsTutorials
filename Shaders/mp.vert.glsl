#version 330 core

in vec3 position;
in vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out Vertex {
  vec4 color;
} OUT;

void main() {
  mat4 mvp = projMatrix * viewMatrix * modelMatrix;
  gl_Position = mvp * vec4(position, 1.0);
  OUT.color = color;
}