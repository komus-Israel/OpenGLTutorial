#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

//  The graphics pipeline converts a set of 3D co-ordinates into
//  2D pixels that fits in the screen
//  First, 3D co-ordinates are converted to 2D co-ordinates
//  Secondly, the 2D co-ordinates are converted into colored pixels
class GraphicsPipeline {

    //  Vertex Shader
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    ;

    //  Fragment Shader
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    ;

private:

     void compileShader(const char *shaderSource, unsigned int shaderType) {
       
        //  In order for opengl to use the shader, it has to dynamically compile it at run-time from its
        //  source code
        //  the type of shader being created is passed to function below (vertex, fragment, etc)
        unsigned int shader = glCreateShader(shaderType);
        
        // Attach the shader source code to the shader object and compile the shader
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;

            if (shaderType == GL_VERTEX_SHADER) {

                throw std::runtime_error("Vertex Shader compilation failed");

            } else if (shaderType == GL_FRAGMENT_SHADER) {

                throw std::runtime_error("Fragment Shader compilation failed");

            }
            
        }
    }   


public:
    unsigned int VBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;

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

        //  compile vertex shader
        compileShader(vertexShaderSource, GL_VERTEX_SHADER);

    }

    //  Fragment shader is about calculating the color output of the pixels
    //  Colors are represented as an array of 4 values (RGBA)
    //  The strenth of each component is a value between 0.0 and 1.0
    void compileFragmentShader() {

       //   compile fragment shader
       compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    }


};

