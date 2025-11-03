#include "game.h"

void winResize(GLFWwindow* win, int width, int height)
{
    Game* game_ptr = (Game*) glfwGetWindowUserPointer(win);
    game_ptr->winSize.x = width;
    game_ptr->winSize.y = height;
    glViewport(0, 0, width, height);
}

Game::Game() {
    this->winSize = glm::ivec2(960, 549);
}

int Game::init() {
    if (!glfwInit()) {
        std::cout << "GLFW INIT FAILED" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->win = glfwCreateWindow(winSize.x, winSize.y, "Voxel game", NULL, NULL);

    if (this->win == NULL) {
        std::cout << "WINDOW CREATE FAILED" << std::endl;
        return 2;
    }

    glfwMakeContextCurrent(this->win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD LOAD FAILED" << std::endl;
        return 1;
    }

    glViewport(0, 0, winSize.x, winSize.y);

    glfwSetWindowUserPointer(win, this);
    glfwSetFramebufferSizeCallback(win, winResize);

    glClearColor(0.0f, 0.5f, 0.6f, 1.0f);

    return 0;
}

int Game::run() {

    while (!glfwWindowShouldClose(win)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    return 0;
}

Game::~Game() {;
    std::cout << "game destructor called\n";
    glfwTerminate();
}