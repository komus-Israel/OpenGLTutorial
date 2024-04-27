#include <GLFW/glfw3.h>



class WindowHandler {

public:
    GLFWwindow* window;

    void createWindow() {
        window = glfwCreateWindow(700, 700, "Learn OpenGL", NULL, NULL);

        if (window == NULL) {
            throw std::runtime_error("Failed To Create GLFW Window");
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);
    }

};