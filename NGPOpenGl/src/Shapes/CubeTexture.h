#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

class CubeTexture {
public:
    CubeTexture();
    CubeTexture(float width, float height, float depth, const std::string& vertexPath, const std::string& fragPath, const std::vector<std::string>& texturePaths, glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f));
    ~CubeTexture();

    void draw();
    void updateUniforms();
    void Translate(glm::vec3& translate);
    void Scale(glm::vec3 scale);
    void Scale(float scale);
    void Rotate(float angle, glm::vec3 axis);
    void SetView(glm::mat4 view);
    void SetProj(glm::mat4 proj);
    void SetDimensions(float width, float height, float depth);

private:
    std::unique_ptr<VAO> m_VAO;
    std::unique_ptr<VBO> m_VBO;
    std::unique_ptr<Shader> m_Shader;
    std::vector<std::unique_ptr<Texture>> m_Textures;
    float m_height, m_width, m_depth, m_FScale, rotationAngle;
    glm::mat4 m_Proj, m_View, m_Model;

    glm::vec3 m_Pos, m_Translate, m_Scale, m_CubeColor, rotationAxis;
};

CubeTexture::CubeTexture() :
    m_height(1.0f),
    m_width(1.0f),
    m_depth(1.0f),
    m_FScale(1.0f),
    m_Translate(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_CubeColor(glm::vec3(1.0f, 0.5f, 0.31f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)) {}

CubeTexture::CubeTexture(float width, float height, float depth, const std::string& vertexPath, const std::string& fragPath, const std::vector<std::string>& texturePaths, glm::vec3 trans) :
    m_height(height),
    m_width(width),
    m_depth(depth),
    m_FScale(1.0f),
    m_Translate(trans),
    m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_CubeColor(glm::vec3(1.0f, 0.0f, 0.0f)),
    m_Model(glm::mat4(1.0f)),
    m_View(glm::mat4(1.0f)),
    rotationAxis(glm::vec3(0.0f, 0.0f, 1.0f)),
    rotationAngle(0.0f)
{
    int widthA, heightA;
    glfwGetWindowSize(glfwGetCurrentContext(), &widthA, &heightA);
    m_Proj = glm::perspective(glm::radians(45.0f), (float)widthA / heightA, 0.1f, 20000.0f);

    float vertices[] = {
        // positions         // texture coords
        // Front face
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

        // Back face
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,

        // Left face
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,

        // Right face
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  0.0f, 1.0f,

        // Bottom face
        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

        // Top face
        -1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f, 0.0f
    };



    for (const auto& path : texturePaths) {
        m_Textures.emplace_back(std::make_unique<Texture>(path));
    }

    m_VBO = std::make_unique<VBO>(vertices, sizeof(vertices));
    VBOLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO = std::make_unique<VAO>();
    m_VAO->AddBuffer(*m_VBO, layout);

    m_Shader = std::make_unique<Shader>(vertexPath, fragPath);
    m_Shader->Bind();
    SetDimensions(width, height, depth);
    m_VAO->Unbind();
    m_Shader->Unbind();
}

CubeTexture::~CubeTexture() {}

void CubeTexture::draw() {
    m_VAO->Bind();
    m_Shader->Bind();
    for (int i = 0; i < m_Textures.size(); ++i) {
        updateUniforms();
        m_Textures[i]->Bind();
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
    
   
    
}

void CubeTexture::updateUniforms() {
    m_Model = glm::mat4(1.0f);
    m_Model = glm::translate(m_Model, m_Translate);
    m_Model = glm::rotate(m_Model, glm::radians(rotationAngle), rotationAxis);
    m_Model = glm::scale(m_Model, glm::vec3(m_width, m_height, m_depth));

    m_Shader->Bind();
    m_Shader->SetUniform3fv("setColor", m_CubeColor);
    m_Shader->setUniformMat4f("model", m_Model);
    m_Shader->setUniformMat4f("view", m_View);
    m_Shader->setUniformMat4f("projection", m_Proj);
    m_Shader->SetUniform1i("isColor", 0);
    m_Shader->SetUniform1i("tex0", 0);
}

void CubeTexture::Translate(glm::vec3& translate) {
    m_Model = glm::translate(m_Model, -m_Translate);
    m_Pos -= m_Translate;
    m_Translate = translate;
    m_Pos += m_Translate;
    m_Model = glm::translate(m_Model, m_Translate);
}

void CubeTexture::Scale(glm::vec3 scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f));
    m_Scale = scale;
    m_Model = glm::scale(m_Model, m_Scale);
}

void CubeTexture::Scale(float scale) {
    m_Model = glm::scale(m_Model, glm::vec3(1.0f / m_FScale));
    m_FScale = scale;
    m_Scale = glm::vec3(m_FScale);
    m_Model = glm::scale(m_Model, m_Scale);
}

void CubeTexture::Rotate(float angle, glm::vec3 axis) {
    rotationAngle = angle;
    rotationAxis = axis;
}

void CubeTexture::SetView(glm::mat4 view) {
    m_View = view;
}

void CubeTexture::SetProj(glm::mat4 proj) {
    m_Proj = proj;
}

void CubeTexture::SetDimensions(float width, float height, float depth) {
    m_width = width;
    m_height = height;
    m_depth = depth;
}
