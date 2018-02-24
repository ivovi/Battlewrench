// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Include GLEW
//#include <GLEW/glew.h>

//Include GLAD
#include <GLAD/glad.h>

//Include GLFW
#include <GLFW/glfw3.h>

//function to read files and return their contents as a string
/*
static char* readFile(const char* filename) {
    //open a file
    FILE *fp;
    fp = fopen(filename, "r");

    //move the file pointer to the end of the file and determine it's length
    fseek(fp, 0, SEEK_END);
    long file_length = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    char* contents = malloc(sizeof(contents[0]) * (file_length + 1));

    //zero memory
    for (int i=0; i < file_length + 1; i++){
        contents[i] = 0;
    }
    //read the file
    fread(contents, 1, file_length, fp);

    //add end of string
    contents[file_length + 1] = '\0';
    fclose(fp);

    return contents;
}
*/

/*
GLunit LoadShaders(const char* vertexFilePath, const char* fragmentFilePath){

    GLunit VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLunit FragmenShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char* VertexShaderCode = readFile("SimpleVertexShader.fsh");
    char* FragmentShaderCode = readFile("simpleVertexShader.vsh");

    glShaderSource(VertexShaderID, 1, &VertexShaderCode, NULL);

    return 0;
}
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



const char *vertexShaderSource = "#version 400 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "layout (location=1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main(){\n"
    "gl_Position = vec4(aPos, 1.0);\n"
    "ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 400 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main(){\n"
    "FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

   
int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        printf("Failed to create GLFW window!!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initiate GLAD!!\n");
        return -1;
    }

    //Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }

    //Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }


    //Link shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    //Delete shaders once linked and verified
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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