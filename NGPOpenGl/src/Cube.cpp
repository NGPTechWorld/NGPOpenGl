#include "Cube.h"
#include "Scene.h"
// TODO: Clean this :-)
Cube::Cube() :
	m_Length(100.0f),
	m_FScale(1.0f),
	m_Degree(0.0f),
	m_Axis(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_Translate(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_CubeColor(glm::vec3(1.0f, 0.5f, 0.31f)),
	m_Model(glm::mat4(1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f)))
{

	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	m_Proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 2000.0f);
}

Cube::Cube(float sideLength, const std::string& vertexPath, const std::string& fragPath, glm::vec3 trans) :
	m_Length(sideLength),
	m_FScale(1.0f),
	m_Degree(0.0f),
	m_Axis(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_Translate(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_CubeColor(glm::vec3(1.0f, 0.5f, 0.31f)),
	m_Model(glm::mat4(1.0f)),
	m_Pos(trans),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f)))
{
	int width, height;

	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	m_Proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 2000.0f);
	float vertices[] = {

 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  0.0f,0.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  1.0f,0.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  1.0f,1.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  1.0f,1.0f,

 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  0.0f,1.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 0.0f,-1.0f,  0.0f,0.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f,  0.0f,0.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f,  1.0f,0.0f,


  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f, 1.0f,1.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f, 1.0f,1.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f, 0.0f,1.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 0.0f, 1.0f, 0.0f,0.0f,

 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 1.0f,1.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 0.0f,1.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 0.0f,1.0f,

 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 1.0f,1.0f,


  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 0.0f,0.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,

 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 1.0f,1.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 1.0f,0.0f,

 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength + trans.x,-0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f,-1.0f, 0.0f, 0.0f,1.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 1.0f,1.0f,


  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y, 0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength + trans.x, 0.5f * sideLength + trans.y,-0.5f * sideLength + trans.z,  0.0f, 1.0f, 0.0f, 0.0f,1.0f
	};
	m_VBO = std::make_unique<VBO>(vertices, sizeof(vertices));
	VBOLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO = std::make_unique<VAO>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_Shader = std::make_unique<Shader>(vertexPath, fragPath);
	m_Shader->Bind();
	//m_Shader->SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose
	updateUniforms();
	m_VAO->Unbind();
	m_Shader->Unbind();
}

Cube::~Cube()
{
}

void Cube::draw()
{
	m_VAO->Bind();
	m_Shader->Bind();
	updateUniforms();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}
void Cube::updateUniforms() {
	m_Shader->Bind();
	m_Shader->SetUniform3fv("setColor", m_CubeColor);
	m_Shader->setUniformMat4f("model", m_Model);
	m_Shader->setUniformMat4f("view", m_View);
	m_Shader->setUniformMat4f("projection", m_Proj);

	//m_Shader->SetUniform3fv("viewPos", Scene::instancePtr->getCameraPosition());
}
void Cube::Rotate(float degree, glm::vec3& axis) {
	m_Model = glm::rotate(m_Model, glm::radians(-m_Degree), m_Axis);
	m_Degree = degree, m_Axis = axis;
	m_Model = glm::rotate(m_Model, glm::radians(m_Degree), m_Axis);
}
void Cube::Translate(glm::vec3& translate) {
	m_Model = glm::translate(m_Model, -m_Translate);
	m_Pos -= m_Translate;
	m_Translate = translate;
	m_Pos += m_Translate;
	m_Model = glm::translate(m_Model, m_Translate);
}
void Cube::Scale(glm::vec3& scale) {
	m_Model = glm::scale(m_Model, glm::vec3(1.0f, 1.0f, 1.0f) / m_Scale);
	m_Scale = scale;
	m_Model = glm::scale(m_Model, m_Scale);
}
void Cube::Scale(float scale) {
	m_Model = glm::scale(m_Model, glm::vec3(1.0f / m_FScale, 1.0f / m_FScale, 1.0f / m_FScale));
	m_FScale = scale;
	m_Scale = glm::vec3(m_FScale, m_FScale, m_FScale);
	m_Model = glm::scale(m_Model, m_Scale);
}



void Cube::SetView(glm::mat4 view) {
	m_View = view;

}

void Cube::SetProj(glm::mat4 proj) {
	m_Proj = proj;

}
