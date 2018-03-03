// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Include GLAD
#include <GLAD/glad.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include custom headers
#include "../Shaders/Shaders.h"
#include "../Util/Util.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(){

    printf("STARTING!!!!!\n");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        fprintf(stderr, "Failed to create GLFW window!\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        fprintf(stderr, "Failed to initiate GLAD!\n");
        return 1;
    }

    const char* vertexShaderSource = readFileToString(VERTEX_SHADER_PATH);
    const char* fragmentShaderSource = readFileToString(FRAGMENT_SHADER_PATH);
    unsigned int shaderProgram = loadShaders(vertexShaderSource, fragmentShaderSource);

    if(shaderProgram == -1) {
        fprintf(stderr, "Shaders failed to load.\n");
        return 1;
    }

    //Create Triangle Vertex
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.0f, 0.0f,     0.0f, 0.0f, 1.0f  
    };

    unsigned int VBOs[1], VAOs[1], EBO;
    glGenBuffers(1, VBOs);
    //glGenBuffers(1, &EBO);
    glGenVertexArrays(1, VAOs);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);



    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0 , width, height);
}