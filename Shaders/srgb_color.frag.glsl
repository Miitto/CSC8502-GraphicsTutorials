#version 330 core

in Vertex {
  vec4 color;
} IN;

out vec4 fragColor;

void main() {
  fragColor = IN.color;
  fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2));
}
