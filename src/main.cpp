#include <iostream>
#include "windowHandler.h"

class App {

    
    WindowHandler windowHandler;
    
public:


    void run() {

        initWindow();
        initGlad();
        handleLoop();
        clean();

        
    }

    void initWindow() {

        windowHandler.createWindow();

    }

    //  manage function pointers
    void initGlad() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to Initialize GLAD");
        }
    }

    //  keep application alive    
    void handleLoop() {
        windowHandler.renderLoop();
    }

    //  clean GLFW resources upon render loop exit
    void clean() {
        glfwTerminate();
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