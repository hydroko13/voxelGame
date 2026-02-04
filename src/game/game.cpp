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
    bool > stopGe
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



    blockAtlas.init();


    for (auto f : std::filesystem::recursive_directory_iterator("resources/textures/blocks/")) {
        if (f.is_regular_file()) {
            std::filesystem::path fp = f.path();
            if (fp.extension().string() == std::string(".png")) {
                std::cout << "Adding image " << fp.filename() << " to block texture atlas...\n";
                Image image;

                image.initFromFile(fp);

                blockAtlas.addImg(image, fp.filename().string());
            }
            
        }
    }


    

    tex.init();

    glActiveTexture(GL_TEXTURE1);
    this->tex.bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    tex.fromImage(blockAtlas.img);

    blockRegistry.registerBlock(1, Block(blockAtlas, "debug_block_top.png", "debug_block_bottom.png", "debug_block_north.png", "debug_block_south.png", "debug_block_west.png", "debug_block_east.png"));
    blockRegistry.registerBlock(2, Block(blockAtlas, "grass_block_top.png", "grass_block_bottom.png", "grass_block_side.png", "grass_block_side.png", "grass_block_side.png", "grass_block_side.png"));
    blockRegistry.registerBlock(3, Block(blockAtlas, "dirt.png", "dirt.png", "dirt.png", "dirt.png", "dirt.png", "dirt.png"));
    blockRegistry.registerBlock(4, Block(blockAtlas, "stone.png", "stone.png", "stone.png", "stone.png", "stone.png", "stone.png"));



    //this->vertices[3] = std::get<0>(coords);
    //this->vertices[4] = std::get<1>(coords);

    //this->vertices[8] = std::get<0>(coords);
    //this->vertices[9] = std::get<3>(coords);

    //this->vertices[13] = std::get<2>(coords);
    //this->vertices[14] = std::get<3>(coords);

    //this->vertices[18] = std::get<2>(coords);
    //this->vertices[19] = std::get<1>(coords);

    

    this->shaderProgram1.setInt("tex1", 1);
    this->shaderProgram1.setFloat("drawBlack", 0.0f);

    /*this->VBO.init(GL_STATIC_DRAW);

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

    this->VAO.doneAttribs();*/



    
    //this->VAO.unbind();

    //std::cout << tex.getHandle() << std::endl;

   
    this->proj = glm::mat4(1.0f);


    this->camera = Camera();

  

    this->shaderProgram1.use();

    
    this->proj = glm::perspective(glm::radians(90.0f), ((float)winSize.x) / ((float)winSize.y), 0.1f, 800.0f);


    this->camera.pos = glm::vec3(0.0f, 70.0f, 5.0f);

    //this->camera.pos = glm::vec3(0.0f, 0.0f, 3.0f);

    this->shaderProgram1.setMat4f("proj", proj);
    this->mx = 0.0;
    this->my = 0.0;

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->level.stopGen = false;
    this->level.startChunkGenerationThread();

    blockSelectorBox.init(blockAtlas);

    return 0;
}


int Game::run() {

    this->time = glfwGetTime();

    while (!glfwWindowShouldClose(win)) {


        double now = glfwGetTime();
        dt = (float)(now - this->time);
        this->time = now;


        glCheckErrorBefore("glClear");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCheckErrorAfter("glClear");



        this->shaderProgram1.use();

        
       

        //this->model = glm::rotate(this->model, glm::radians(15.0f * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));


      


        
        
        

        double nx;
        double ny;

        glfwGetCursorPos(win, &nx, &ny);

        float relX = nx - mx;
        float relY = ny - my;

        mx = nx;
        my = ny;




        if (glfwGetKey(win, GLFW_KEY_S))
        {
            this->camera.pos -= this->camera.directionVec * 15.0f * dt;
        }
        if (glfwGetKey(win, GLFW_KEY_W))
        {
            this->camera.pos += this->camera.directionVec * 15.0f * dt;
        }
        if (glfwGetKey(win, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(win, 1);
        }
        // if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
        // {
        //     blockDestroyTick += dt;
        //     if (blockDestroyTick > 0.04f) {
        //         this->blockDestroyProgress++;
        //         if (blockDestroyProgress > 8) {
        //             this->level.setBlockAt(blockLookingAtPos, 0, blockRegistry);
        //             this->blockDestroyProgress = 0;
        //             blockDestroyTick = 0.0f;
        //             this->blockSelectorBox.destroy_progress = 0;
        //             this->blockSelectorBox.updateFrame(blockAtlas);
        //         }
        //         else {
        //             this->blockSelectorBox.destroy_progress = blockDestroyProgress;
        //             this->blockSelectorBox.updateFrame(blockAtlas);
        //         }
                
        //         this->blockDestroyTick = 0.0f;
        //     }
        // }
        // else {
        //     this->blockDestroyProgress = 0;
        //     blockDestroyTick = 0.0f;
        //     this->blockSelectorBox.destroy_progress = 0;
        //     this->blockSelectorBox.updateFrame(blockAtlas);
        // }

        // bool foundBlock = false;
        // for (float step = 0; step < 10; step+=0.02) {
        //     glm::fvec3 rayPos = this->camera.pos + this->camera.directionVec * step;

        //     glm::ivec3 blockPos = glm::round(rayPos);

        //     if (level.getBlockAt(blockPos) != 0) {
        //         this->blockLookingAtPos = blockPos;
        //         lookingAtABlock = true;
        //         foundBlock = true;
        //         break;
        //     }
            


            
            

        // }
        // if (!foundBlock) {

        // }

        this->level.chunkGenOrigin = glm::ivec2((int)(camera.pos.x / 16.0f), (int)(camera.pos.z / 16.0f));





        this->camera.pitch -= relY * 0.2;
        this->camera.yaw += relX * 0.2;
        this->camera.pitch = std::clamp(this->camera.pitch, -89.0f, 89.0f);
        

        this->camera.updateViewMat();

        this->shaderProgram1.setMat4f("view", this->camera.viewMat);

        

        this->tex.bind();

        

        this->level.drawChunks(shaderProgram1, blockRegistry);

        blockSelectorBox.goTo(this->blockLookingAtPos);

        blockSelectorBox.draw(shaderProgram1);


        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    
   

    return 0;
}

Game::~Game() {;
    std::cout << "game destructor called\n";

    this->level.stopGen = true;

    for (std::thread& t : level.chunkGenThreads) {
        if (t.joinable()) {
            t.join();
        }
        
    }
    


    for (auto& p : this->level.chunks) {
        p.second.destroy();
    }


    this->shaderProgram1.destroy();


    glfwTerminate();
}