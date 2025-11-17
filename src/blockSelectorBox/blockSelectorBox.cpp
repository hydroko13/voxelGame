#include "blockSelectorBox.h"



BlockSelectorBox::BlockSelectorBox() {
	model = glm::mat4(1.0f);
}

void BlockSelectorBox::destroy() {
    this->ebo.destroy();
    this->vbo.destroy();
    this->vao.destroy();
}

void BlockSelectorBox::draw(ShaderProgram& shaderProgram) {

    shaderProgram.setFloat("drawBlack", 0.0f);

    
    shaderProgram.setMat4f("model", this->model);

    this->vao.bind();


    glCheckErrorBefore("glDrawElements");
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glCheckErrorAfter("glDrawElements");


    shaderProgram.setFloat("drawBlack", 0.0f);


}

void BlockSelectorBox::goTo(glm::ivec3 blockPos) {


    model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::fvec3(blockPos) - glm::fvec3(0.01f, 0.01f, 0.01f));

    model = glm::scale(model, glm::fvec3(1.02f, 1.02f, 1.02f));

}


void BlockSelectorBox::updateFrame(ImageAtlas& blockAtlas) {
    std::string imgId = "";
    if (this->destroy_progress == 0) {
        imgId = "block_overlay0.png";
    }
    else {
        imgId = "destroy_block_" + std::to_string(destroy_progress) + ".png";
        

    }
    std::tuple<float, float, float, float> texCoords = blockAtlas.getTexCoords(imgId);
    this->vbo.bind();

    this->ebo.bind();




    for (int i = 0; i < 6; i++) {
        this->vertices[i * 20 + 3] = std::get<0>(texCoords);
        this->vertices[i * 20 + 4] = std::get<1>(texCoords);

        this->vertices[i * 20 + 8] = std::get<0>(texCoords);
        this->vertices[i * 20 + 9] = std::get<3>(texCoords);

        this->vertices[i * 20 + 13] = std::get<2>(texCoords);
        this->vertices[i * 20 + 14] = std::get<3>(texCoords);

        this->vertices[i * 20 + 18] = std::get<2>(texCoords);
        this->vertices[i * 20 + 19] = std::get<1>(texCoords);
    }


    this->vbo.setData((void*)this->vertices, sizeof(float) * 120);

    this->ebo.setData((void*)this->indices, sizeof(unsigned int) * 36);

    
}

void BlockSelectorBox::init(ImageAtlas& blockAtlas) {




    std::tuple<float, float, float, float> texCoords = blockAtlas.getTexCoords("block_overlay0.png");

    

    this->vao.init();

    this->vao.bind();



    this->vbo.init(GL_STATIC_DRAW);
    this->ebo.init(GL_STATIC_DRAW);

    this->vbo.bind();

    this->ebo.bind();




    for (int i = 0; i < 6; i++) {
        this->vertices[i * 20 + 3] = std::get<0>(texCoords);
        this->vertices[i * 20 + 4] = std::get<1>(texCoords);

        this->vertices[i * 20 + 8] = std::get<0>(texCoords);
        this->vertices[i * 20 + 9] = std::get<3>(texCoords);

        this->vertices[i * 20 + 13] = std::get<2>(texCoords);
        this->vertices[i * 20 + 14] = std::get<3>(texCoords);
            
        this->vertices[i * 20 + 18] = std::get<2>(texCoords);
        this->vertices[i * 20 + 19] = std::get<1>(texCoords);
    }
   

    this->vbo.setData((void*)this->vertices, sizeof(float) * 120);

    this->ebo.setData((void*)this->indices, sizeof(unsigned int) * 36);

    this->vao.beginAttribs();




    this->vao.attrib(GL_FLOAT, 3, sizeof(float) * 3);
    this->vao.attrib(GL_FLOAT, 2, sizeof(float) * 2);

    this->vao.doneAttribs();

    this->vao.unbind();



}