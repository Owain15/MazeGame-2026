#version 300 es
// Fragment shader
precision mediump float;

uniform vec4 uColor;
out vec4 color;

void main() { color = uColor; }