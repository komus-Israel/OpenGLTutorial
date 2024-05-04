#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


class GraphicsPipeline {

    //  The graphics pipeline converts a set of 3D co-ordinates into
    //  2D pixels that fits in the screen
    //  First, 3D co-ordinates are converted to 2D co-ordinates
    //  Secondly, the 2D co-ordinates are converted into colored pixels

public:
    uint VBO;

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

        //  Bind buffer
        //  Buffer type for VBO is `GL_ARRAY_BUFFER`
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //  copy the defined vertex into buffer's memory
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    }


    //  write the vertex shader in the vertex language (GLSL)
    //  Takes as input a single vertex
    //  Transforms 3D co-ordinates into different 3D co-ordinates
    void vertexShader() {

        //  With the vertex data defined, it will be sent as the input to the first process
        //  of the Graphics pipelin: the vertex shader
        //  This is done by creating memory on the GPU where we store the vertex data
        //  This memory is handled by the VBO


    }


};

