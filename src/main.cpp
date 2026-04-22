#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<GameState.h>

GameManager game;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 1. Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Create Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Horror Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. Initialize GLAD
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // 4. Game Loop
    float lastFrame = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        game.update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);

        switch(game.currentState){
            case GameState::MENU:
                glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
                break;
            case GameState::PLAYING:
                //Person 1 and 5 code enter here.
                glClearColor(0.0f,0.0f,0.0f,1.0f);
                break;
            case GameState::LOSE:
                glClearColor(0.5f,0.0f,0.0f,1.0f);
                break;
            //Enter win case here, not sure what.
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
