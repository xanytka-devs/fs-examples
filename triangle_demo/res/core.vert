#version 460 core
in vec3 aPos;
out vec3 pos;

void main() {
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   pos = aPos;
}