#include "windowHandler.hpp"





class App {


private:
    
    GraphicsPipeline pipeline;
    WindowHandler windowHandler;
    

public:

    Shader shader;

    App(const char* vertexPath, const char* fragmentPath)
        :shader(vertexPath, fragmentPath), windowHandler(shader)
    {}
    
    void run() {

        initWindow();
        initGlad();
        handlePipeline();
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
        windowHandler.renderLoop(pipeline);
    }

    //  clean GLFW resources upon render loop exit
    void clean() {
     
        glfwTerminate();
    }

    void handlePipeline() {

        shader.processShaders();
        pipeline.generateVAO();
        pipeline.handleVBO();
        // // pipeline.handleEBO();
        pipeline.setVertexAttribute();
        
        
    }


};

int main() {

    App app("shaders/shader.vs", "shaders/shader.fs");
    
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