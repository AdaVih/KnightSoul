//
//  SpriteRenderer.cpp
//  KnightSoul
//
//  Created by Knight on 2017/3/16.
//  Copyright © 2017年 Knight. All rights reserved.
//

#include "SpriteRenderer.hpp"
#include "glm.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D &texture,
                                glm::vec2 position,
                                glm::vec2 size,
                                GLfloat rotate,
                                glm::vec3 color,
                                glm::vec4 spriteFrame)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));
    
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    
    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    this->shader.SetVector4f("spriteFrame", spriteFrame);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(glm::vec2 position, Sprite* sprite)
{
    
}
