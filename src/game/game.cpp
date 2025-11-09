#include "game.h"

void winResize(GLFWwindow* win, int width, int height)
{
    Game* game_ptr = (Game*) glfwGetWindowUserPointer(win);
    game_ptr->winSize.x = width;
    game_ptr->winSize.y = height;
    glCheckErrorBefore("glViewport");
    glViewport(0, 0, width, height);
    glCheckErrorAfter("glViewport");
}

Game::Game() {
    this->winSize = glm::ivec2(960, 960);
    
}

int Game::init() {
    if (!glfwInit()) {
        std::cout << "GLFW INIT FAILED" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    

    this->win = glfwCreateWindow(winSize.x, winSize.y, "Voxel game", NULL, NULL);
    GLFWmonitor* mon = glfwGetPrimaryMonitor();

    const GLFWvidmode* monMode = glfwGetVideoMode(mon);
    
    glfwSetWindowMonitor(win, NULL, monMode->width / 2 - winSize.x / 2, monMode->height / 2 - winSize.y / 2, winSize.x, winSize.y, GLFW_DONT_CARE);

    

    


    if (this->win == NULL) {
        std::cout << "WINDOW CREATE FAILED" << std::endl;
        return 2;
    }

    glfwMakeContextCurrent(this->win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD LOAD FAILED" << std::endl;
        return 1;
    }

    glCheckErrorBefore("glViewport");
    glViewport(0, 0, winSize.x, winSize.y);
    glCheckErrorAfter("glViewport");

    

    glfwSetWindowUserPointer(win, this);
    glfwSetFramebufferSizeCallback(win, winResize);

    glCheckErrorBefore("glClearColor");
    glClearColor(0.0f, 0.5f, 0.6f, 1.0f);
    glCheckErrorAfter("glClearColor");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);




    Shader vertShader;
    Shader fragShader;


    if (vertShader.init(GL_VERTEX_SHADER, "shader_vertex.glsl") == ShaderStatus::FileOpenFailed) {
        return 1;
    }
    if (vertShader.compile() == ShaderStatus::CompileFailed) {
        return 1;

    }
    if (fragShader.init(GL_FRAGMENT_SHADER, "shader_fragment.glsl") == ShaderStatus::FileOpenFailed) {
        return 1;
    }
    if (fragShader.compile() == ShaderStatus::CompileFailed) {
        return 1;
    }

    this->shaderProgram1.init();

    this->shaderProgram1.attachShader(vertShader);
    this->shaderProgram1.attachShader(fragShader);
    if (this->shaderProgram1.link() == ShaderProgramStatus::LinkFailed) {
        return 1;
    }
   
    vertShader.destroy();
    fragShader.destroy();

    this->shaderProgram1.use();



    image1.initFromFile(std::filesystem::path("./resources/textures/mars_painting1.jpg"));

    tex.init();

    glActiveTexture(GL_TEXTURE1);
    this->tex.bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    tex.fromImage(image1);

    this->shaderProgram1.setInt("tex1", 1);
   

    this->VBO.init(GL_STATIC_DRAW);

    this->EBO.init(GL_STATIC_DRAW);

    this->VAO.init();

    this->VAO.bind();

    this->VBO.bind();

    this->EBO.bind();

    this->VBO.setData((void*) this->vertices, sizeof(this->vertices));

    this->EBO.setData((void*)this->indices, sizeof(this->indices));

    this->VAO.beginAttribs();
        
    this->VAO.attrib(GL_FLOAT, 3, sizeof(float)*3);

    this->VAO.attrib(GL_FLOAT, 2, sizeof(float) * 2);

    this->VAO.doneAttribs();



    
    this->VAO.unbind();

    std::cout << tex.getHandle() << std::endl;

   
    this->proj = glm::mat4(1.0f);
    this->model = glm::mat4(1.0f);


    this->camera = Camera();

  

    this->shaderProgram1.use();

    
    this->proj = glm::perspective(glm::radians(45.0f), ((float)winSize.x) / ((float)winSize.y), 0.1f, 100.0f);

    this->model = glm::translate(this->model, glm::vec3(0.0f, 0.0f, 0.5f));

    this->camera.pos = glm::vec3(0.0f, 0.0f, 5.0f);

    //this->camera.pos = glm::vec3(0.0f, 0.0f, 3.0f);

    this->shaderProgram1.setMat4f("proj", proj);


    return 0;
}


int Game::run() {

    while (!glfwWindowShouldClose(win)) {

        glCheckErrorBefore("glClear");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCheckErrorAfter("glClear");



        this->shaderProgram1.use();

        this->model = glm::mat4(1.0f);

        this->model = glm::translate(this->model, glm::vec3(0.0f, 0.0f, 0.5f));

        
       

        //this->model = glm::rotate(this->model, glm::radians(15.0f * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));


       


        
        if (glfwGetKey(win, GLFW_KEY_A)) {
            this->camera.yaw -= 1.0f;
        }
        if (glfwGetKey(win, GLFW_KEY_D)) {
            this->camera.yaw += 1.0f;
        }

        if (glfwGetKey(win, GLFW_KEY_S)) {
            this->camera.pitch -= 1.0f;
        }
        if (glfwGetKey(win, GLFW_KEY_W)) {
            this->camera.pitch += 1.0f;
        }



        this->camera.updateViewMat();

        this->shaderProgram1.setMat4f("view", this->camera.viewMat);

        this->shaderProgram1.setMat4f("model", model);

        this->tex.bind();

        this->VAO.bind();

        



        
        glCheckErrorBefore("glDrawArrays");
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckErrorAfter("glDrawArrays");





        glfwPollEvents();
        glfwSwapBuffers(win);
    }

   
    return 0;
}

Game::~Game() {;
    std::cout << "game destructor called\n";
    this->VAO.destroy();
    this->VBO.destroy();
    this->shaderProgram1.destroy();

    glfwTerminate();
}