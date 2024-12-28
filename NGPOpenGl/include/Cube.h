#pragma once
#include <VBO.h>
#include <Shader.h>
#include <EBO.h>
#include <VAO.h>
#include <memory>
#include <Texture.h>
#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>
#include "PointLight.h"
#include "SpotLight.h"
class Cube
{

public:
	Cube();
	Cube(float sideLength , const std::string& vertexPath , const std::string& fragPath , glm::vec3 trans = glm::vec3(0.0f , 0.0f , 0.0f) );

	// Allow moving
	Cube(Cube&&) noexcept = default;
	Cube& operator=(Cube&&) noexcept = default;
	~Cube();
	void draw();
	void updateUniforms();
	void Rotate(float degree, glm::vec3& axis);
	void Translate(glm::vec3& translate);
	void Scale(glm::vec3& scale);
	void Scale(float scale);
	void SetView(glm::mat4 view);
	void SetProj(glm::mat4 proj);
	inline void setTransform(glm::mat4 transform) {
		m_Model = transform;
	}

private:
	std::unique_ptr< VAO >m_VAO;
	std::unique_ptr< VBO >m_VBO;
	std::unique_ptr< Shader >m_Shader;

	float m_Length, m_Degree, m_FScale;
	glm::mat4 m_Proj, m_View, m_Model;

	glm::vec3 m_Axis, m_Pos, m_Translate, m_Scale, m_CubeColor;


};

