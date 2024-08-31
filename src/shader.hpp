// #ifndef SHADER_H
// #define SHADER_H

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    /// program id
    unsigned int shaderProgram;
    const char* vShaderCode; 
    const char* fShaderCode;
    std::string vertexCode;
    std::string fragmentCode;

    /// constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath) {

        /// retrive the vertex/fragment source code from file path
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        /// ensure ifstream objects can throw exceptions
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            /// open files
            vShaderFile.open(vertexPath, std::ifstream::in);
            fShaderFile.open(fragmentPath, std::ifstream::in);

            std::stringstream vShaderStream, fShaderStream;

            /// read file's buffer content into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            /// close file handlers
            vShaderFile.close();
            fShaderFile.close();

            /// convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }

        catch (std::ifstream::failure err) 
        {
            std::cout << vertexPath << std::endl;
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
            throw err;
        }

    }

    void processShaders() {

        vShaderCode = vertexCode.c_str();
        fShaderCode = fragmentCode.c_str();
        
        unsigned int vertexShader =  compileShader(vShaderCode, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader(fShaderCode, GL_FRAGMENT_SHADER);

        createShaderProgram(vertexShader, fragmentShader);

        /// delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    unsigned int compileShader(const char *shaderSource, unsigned int shaderType) {
       
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

                throw std::runtime_error("Vertex Shader compilation failed!");

            } else if (shaderType == GL_FRAGMENT_SHADER) {

                throw std::runtime_error("Fragment Shader compilation failed!");

            }
            
        }

        return shader;
    }

    //  Shader Program object is the final linked version of multiple shaders combined
    //  To use the compiled shaders, they need to be linked to a shader program object
    //  Afterwards, the shader program is activated when rendering objects
    //  When linking the shaders into a program, it links the output of each shader to the inputs of the next shader
    void createShaderProgram(unsigned int vtxShader, unsigned int fragShader) {

        //  create shader program
        shaderProgram = glCreateProgram();

        //  attach the compiled shaders to the program
        glAttachShader(shaderProgram, vtxShader);
        glAttachShader(shaderProgram, fragShader);
        
        //  link the shaders via the shaderProgram
        glLinkProgram(shaderProgram);

        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;
            throw std::runtime_error("Shader Program Linking Failed!");
    
        }

    }

    /// use/activate the shader
    void useProgram() {
        glUseProgram(shaderProgram);
    }

    void changeColorUsingUniform() {
        float timeValue = glfwGetTime();
        float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        float blueValue = (std::sin(timeValue) / 6.0f) + 0.6f;
        float redValue = blueValue + greenValue;

        /// Query the uniform's location using the name
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        
        /// set the uniform value
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
    }

    /// utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

};

// #endif 