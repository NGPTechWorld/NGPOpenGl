include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h" 
#include "VAO.h"
#include "VBO.h"
#include <Shapes/Shape.h>

class Square : Shape {
public:
    Square();
    Square(float width,float height, const std::string& vertexPath, const std::string& fragPath, glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f));
    ~Square();

    void draw();
    void updateUniforms();
    void Translate(glm::vec3& translate);
    void Scale(glm::vec3 scale);
    void Scale(float scale);
    void Rotate(float angle, glm::vec3 axis); // تابع التدوير الجديد
    void SetView(glm::mat4 view);
    void SetProj(glm::mat4 proj);

private:
    std::unique_ptr<VAO> m_VAO;
    std::unique_ptr<VBO> m_VBO;
    std::unique_ptr<Shader> m_Shader;
   
    float m_height,m_width, m_FScale;
    glm::mat4 m_Proj, m_View, m_Model;
    glm::vec3 m_Pos, m_Translate, m_Scale, m_SquareColor;
};

Square::Square() :
    m_height(1.0f),
    m_width(1.0f),
    m_FScale(1.0f),
    m_Translate(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_SquareColor(glm::vec3(1.0f, 0.5f, 0.31f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)) {
}

Square::Square(float width,float height, const std::string& vertexPath, const std::string& fragPath, glm::vec3 trans) :
    m_height(height),
    m_width(width),
    m_FScale(1.0f),
    m_Translate(trans),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_SquareColor(glm::vec3(1.0f, 0.0f, 0.0f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)) 
{
    int widthA, heightA;

    glfwGetWindowSize(glfwGetCurrentContext(), &widthA, &heightA);
    m_Proj = glm::perspective(glm::radians(45.0f), (float)widthA / heightA, 0.1f, 2000.0f);
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f , -1.0f , 0.0f,  1.0f, 1.0f,

        1.0f , -1.0f , 0.0f,  1.0f, 1.0f,
       -1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f , 0.0f,  0.0f, 1.0f
    };

    m_VBO = std::make_unique<VBO>(vertices, sizeof(vertices));
    VBOLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO = std::make_unique<VAO>();
    m_VAO->AddBuffer(*m_VBO, layout);
    Scale(glm::vec3(width,height,1));
    m_Shader = std::make_unique<Shader>(vertexPath, fragPath);
    m_Shader->Bind();
    updateUniforms();
    m_VAO->Unbind();
    m_Shader->Unbind();
}

Square::~Square() {
}

void Square::draw() {
    m_VAO->Bind();
    m_Shader->Bind();
    updateUniforms();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Square::updateUniforms() {
    m_Shader->Bind();
    m_Shader->SetUniform3fv("setColor", m_SquareColor);
    m_Shader->setUniformMat4f("model", m_Model);
    m_Shader->setUniformMat4f("view", m_View);
    m_Shader->setUniformMat4f("projection", m_Proj);
}

void Square::Translate(glm::vec3& translate) {
    m_Model = glm::translate(m_Model, -m_Translate);
    m_Pos -= m_Translate;
    m_Translate = translate;
    m_Pos += m_Translate;
    m_Model = glm::translate(m_Model, m_Translate);
}

void Square::Scale(glm::vec3 scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f) / m_Scale);
    m_Scale = scale;
    m_Model = glm::scale(m_Model, m_Scale);
}

void Square::Scale(float scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f / m_FScale));
    m_FScale = scale;
    m_Scale = glm::vec3(m_FScale);
    m_Model = glm::scale(m_Model, m_Scale);
}

void Square::Rotate(float angle, glm::vec3 axis) {
    m_Model = glm::rotate(m_Model, glm::radians(angle), axis);
}

void Square::SetView(glm::mat4 view) {
    m_View = view;
}

void Square::SetProj(glm::mat4 proj) {
    m_Proj = proj;
}
