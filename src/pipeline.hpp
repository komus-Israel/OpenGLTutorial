#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


class GraphicsPipeline {

    //  vertex shader
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}\0";
    ;

    //  The graphics pipeline converts a set of 3D co-ordinates into
    //  2D pixels that fits in the screen
    //  First, 3D co-ordinates are converted to 2D co-ordinates
    //  Secondly, the 2D co-ordinates are converted into colored pixels

public:
    unsigned int VBO;
    unsigned int vertexShader;

    //  vertices data for the triangle
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    //  Vertex buffer objects
    //  Memory handler to store the vertex data on the GPU
    //  VBO can store a large numer of vetices in the GPU's memory
    void handleVBO() {

        //  Generate a buffer with an ID
        glGenBuffers(1, &VBO);

        // std::cout << "VBO: " << VBO << std::endl;

        //  Bind buffer
        //  Buffer type for VBO is `GL_ARRAY_BUFFER`
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //  copy the defined vertex into buffer's memory
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    }


    //  write the vertex shader in the vertex language (GLSL)
    //  Takes as input a single vertex
    //  Transforms 3D co-ordinates into different 3D co-ordinates
    void compileVertexShader() {

        //  With the vertex data defined, it will be sent as the input to the first process
        //  of the Graphics pipelin: the vertex shader
        //  This is done by creating memory on the GPU where we store the vertex data
        //  This memory is handled by the VBO

        //  In order for opengl to use the shader, it has to dynamically compile it at run-time from its
        //  source code
        //  since a vertex shader is being created, it is passed as a shader type to the function below
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        //  Next attach the shader source code to the shader object and compile the shader
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;
            throw std::runtime_error("Vertex Shader compilation failed");
        }

    }


};

