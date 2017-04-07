// Version d'OpenGL
#version 330

in vec2 texcoord;

out vec4 frag_color;

uniform sampler2D texSampler;

void main() {
  frag_color = texture(texSampler,texcoord);
}
