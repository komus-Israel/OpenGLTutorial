#include "glad/glad.h"
#include <GLFW/glfw3.h>


class WindowHandler {

public:
    GLFWwindow* window;
    
    void createWindow() {

        glfwInit();

        //   first argument tells what option to configure from a large enum of options
        //   prefixed with GLFW_
        //   second argument is an integer that sets the value of the option
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        window = glfwCreateWindow(700, 700, "Learn OpenGL", NULL, NULL);

        if (window == NULL) {
            throw std::runtime_error("Failed To Create GLFW Window");
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        //  Register the callback for window resize
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
    }

    //  Tell openGL the size of the rendering window so 
    //  openGL knows how the data and coordinates will be displayed
    //  with respect to the window. This gets call every time the window is 
    //  resized
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    //  Keep the application running until user stops the application
    void renderLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    
  

};