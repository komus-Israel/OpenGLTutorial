#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

//  The graphics pipeline converts a set of 3D co-ordinates into
//  2D pixels that fits in the screen
//  First, 3D co-ordinates are converted to 2D co-ordinates
//  Secondly, the 2D co-ordinates are converted into colored pixels
class GraphicsPipeline {

private:


public:

    // unsigned int vertexShader;
    // unsigned int fragmentShader;
    // unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    

    //  vertices data for the triangle
    //  Vertex data is a collection of vertices
    std::vector<float> vertices = {

        //  positions           //  colors
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
    };

    //  Unique Vertices for rectangle (to be used for EBO)
    // float vertices[12] = {
    //     0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f
    // };

    //  note that indices starts from 0 (to be used for EBO)
    // unsigned int indices[6] = {
    //     0, 1 , 3,
    //     1, 2, 3
    // };

    void bindVAO() {
        glBindVertexArray(VAO);
    }

    //  Vertex buffer objects
    //  Memory handler to store the vertex data on the GPU
    //  VBO can store a large numer of vetices in the GPU's memory
    void handleVBO() {

        bindVAO();

        //  Generate a buffer with an ID
        glGenBuffers(1, &VBO);

        // std::cout << "VBO: " << VBO << std::endl;

        //  Bind buffer to the `GL_ARRAY_BUFFER`
        //  Buffer type for VBO is `GL_ARRAY_BUFFER`
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //  copy the defined vertex into memory of the buffer currently binded, in 
        //  this case, the VBO
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    }

    // void handleEBO() {

    //     //  Generate buffer with an ID
    //     glGenBuffers(1, &EBO);

    //     //  Bind EBO
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //     //  copy indices into the buffer
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // }

    //  Instruct OPENGL on how it should interpret the vertex data (per vertex attribute)
    //  using `glVertexAttribPointer`
    //  float size is 4 bytes, this represents the size of each position in a vertex
    //  The stride for a single 3D vertex will be 3 * 4 =  12. 
    //  A 3D vertex will have 12bytes by implication
    void setVertexAttribute() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //    stride 24, offset 0
        glEnableVertexAttribArray(0);       //  Enable the above attribute for the attribute at position 0 (position)

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float))); //    stride 24, offset 12
        glEnableVertexAttribArray(1);       //  Enable the above attribute for the attribute at position 1 (color)

    }

    //  To use a VAO, bind it using `glBindVertexArray`
    void generateVAO() {

        //  Generate VAO
        glGenVertexArrays(1, &VAO);
 
    }

    void drawTriangle(uint32_t numOfVertices) {
        glDrawArrays(GL_TRIANGLES, 0, numOfVertices); // for vertices

        //  For EBO
        //  First argument specifies the mode to draw in
        //  Second: the total number of vertices, since 6 indices were to be drawn
        //  Third: The type of the indices
        //  Fourth: Offset in the EBO
        // glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, 0);
    }


};