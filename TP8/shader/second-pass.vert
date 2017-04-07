#version 330

// input attributes 
layout(location = 0) in vec3 in_position;

out vec2 texcoord;

void main() {
  gl_Position = vec4(in_position,1.0);
  texcoord = in_position.xy*0.5+0.5;
}
