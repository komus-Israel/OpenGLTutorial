#include <iostream>
#include "glad/glad.h"
#include "windowHandler.h"

class App {

    
    WindowHandler windowHandler;
    
public:

    void run() {

        initWindow();

    }

    void initWindow() {

        glfwInit();

        //   first argument tells what option to configure from a large enum of options
        //   prefixed with GLFW_
        //   second argument is an integer that sets the value of the option
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        windowHandler.createWindow();

    }


};

int main() {

    App app;

    
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
}