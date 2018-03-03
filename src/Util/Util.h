#ifndef UTIL_H
#define UTIL_H

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* VERTEX_SHADER_PATH = "./src/Shaders/VertexShader.txt";
const char* FRAGMENT_SHADER_PATH = "./src/Shaders/FragmentShader.txt";

const char* readFileToString(const char* filePath);

#endif