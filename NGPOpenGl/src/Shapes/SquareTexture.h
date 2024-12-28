#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include <Shapes/Shape.h>

class SquareTexture :public Shape {
public:
    SquareTexture();
    SquareTexture(float width, float height, const std::string& vertexPath, const std::string& fragPath, const std::string& texturePath, glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f), int mode=0);
    ~SquareTexture();

    void draw() override;
    void updateUniforms()override;
    void Translate(glm::vec3& translate)override;
    void Scale(glm::vec3 scale)override;
    void Scale(float scale)override;
    void Rotate(float angle, glm::vec3 axis)override;
    void SetView(glm::mat4 view)override;
    void SetProj(glm::mat4 proj)override;
    void SetDimensions(float width, float height)override;
    void setModeTexture(int mode)override;

private:
    std::unique_ptr<VAO> m_VAO;
    std::unique_ptr<VBO> m_VBO;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    float m_height, m_width, m_FScale, rotationAngle;
    glm::mat4 m_Proj, m_View, m_Model;

    glm::vec3 m_Pos, m_Translate, m_Scale, m_SquareColor, rotationAxis;
};

SquareTexture::SquareTexture() :
    m_height(1.0f),
    m_width(1.0f),
    m_FScale(1.0f),
    m_Translate(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_SquareColor(glm::vec3(1.0f, 0.5f, 0.31f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)) {}

SquareTexture::SquareTexture(float width, float height, const std::string& vertexPath, const std::string& fragPath, const std::string& texturePath, glm::vec3 trans, int mode) :
    m_height(height),
    m_width(width),
    m_FScale(1.0f),
    m_Translate(trans),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_SquareColor(glm::vec3(1.0f, 0.0f, 0.0f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)),
    rotationAxis(glm::vec3(0.0f, 0.0f, 1.0f)),
    rotationAngle(0.0f)
    
{
    int widthA, heightA;
    glfwGetWindowSize(glfwGetCurrentContext(), &widthA, &heightA);
    m_Proj = glm::perspective(glm::radians(45.0f), (float)widthA / heightA, 0.1f, 20000.0f);

    std::vector<float> vertices;

    if (mode == 1) {
        vertices = {
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
             1.0f, -1.0f, 0.0f,  1.0f, 0.0f,

             1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
             1.0f,  1.0f, 0.0f,  1.0f, 1.0f
        };
    }
    else {
        vertices = {
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,  0.0f, m_height,
             1.0f, -1.0f, 0.0f,  m_width, 0.0f,

             1.0f, -1.0f, 0.0f,  m_width, 0.0f,
            -1.0f,  1.0f, 0.0f,  0.0f, m_height,
             1.0f,  1.0f, 0.0f,  m_width, m_height
        };
    }


    m_Texture = std::make_unique<Texture>(texturePath);
    m_VBO = std::make_unique<VBO>(vertices.data(), vertices.size() * sizeof(float));
    VBOLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO = std::make_unique<VAO>();
    m_VAO->AddBuffer(*m_VBO, layout);

    m_Shader = std::make_unique<Shader>(vertexPath, fragPath);
    m_Shader->Bind();
    SetDimensions(width, height);
    m_VAO->Unbind();
    m_Shader->Unbind();
}

SquareTexture::~SquareTexture() {}

void SquareTexture::draw()  {
    m_VAO->Bind();
    m_Shader->Bind();
    updateUniforms();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void SquareTexture::updateUniforms() {
    m_Model = glm::mat4(1.0f);
    m_Model = glm::translate(m_Model, m_Translate);
    m_Model = glm::rotate(m_Model, glm::radians(rotationAngle), rotationAxis);
    m_Model = glm::scale(m_Model, glm::vec3(m_width, m_height, 1.0f));
   
  
    m_Shader->Bind();
    m_Shader->SetUniform3fv("setColor", m_SquareColor);
    m_Shader->setUniformMat4f("model", m_Model);
    m_Shader->setUniformMat4f("view", m_View);
    m_Shader->setUniformMat4f("projection", m_Proj);
    m_Shader->SetUniform1i("isColor", 0);
    m_Shader->SetUniform1i("tex0", 0);
    m_Texture->Bind();
}

void SquareTexture::Translate(glm::vec3& translate) {
    m_Model = glm::translate(m_Model, -m_Translate);
    m_Pos -= m_Translate;
    m_Translate = translate;
    m_Pos += m_Translate;
    m_Model = glm::translate(m_Model, m_Translate);
}

void SquareTexture::Scale(glm::vec3 scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f) / m_Scale);
    m_Scale = scale;
    m_Model = glm::scale(m_Model, m_Scale);
}

void SquareTexture::Scale(float scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f / m_FScale));
    m_FScale = scale;
    m_Scale = glm::vec3(m_FScale);
    m_Model = glm::scale(m_Model, m_Scale);
}

void SquareTexture::Rotate(float angle, glm::vec3 axis) {
    rotationAngle = angle;
    rotationAxis = axis;
}

void SquareTexture::SetView(glm::mat4 view) {
    m_View = view;
}

void SquareTexture::SetProj(glm::mat4 proj) {
    m_Proj = proj;
}

void SquareTexture::SetDimensions(float width, float height) {
    m_width = width;
    m_height = height;
}

void SquareTexture::setModeTexture(int mode) {
    m_Texture->setMode(mode);
    
}