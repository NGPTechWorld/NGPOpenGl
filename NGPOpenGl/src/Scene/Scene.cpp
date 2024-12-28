#include "Scene.h"
#include "Application.h"
#include <Shapes/SquareTexture.h>
#include <Shapes/CubeTexture.h>
#include <Shapes/CubeTextureLighting.h>

Scene* Scene::instancePtr = nullptr;
Shape* s;
std::vector<Shape*> shapes;
CubeTexture* c;
CubeTextureLighting* cl;
Scene::Scene() :
	lastX(0.0f), lastY(0.0f), firstMouse(true),
	camera(glm::vec3(0.0f, 0.5f, 3.0f))
{
	instancePtr = this;
	lastX = Window::getWidth() / 2.0f;
	lastY = Window::getHeight() / 2.0f;

	//================================
	
	shapes.push_back(new SquareTexture(100, 100, "assets/shaders/defaultVert.vert", "assets/shaders/defaultFrag.frag", "assets/textures/g1.jpg", glm::vec3(0.0f, 0.0f, 0.0f)));
	shapes[0]->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	shapes[0]->setModeTexture(2);
	shapes.push_back(new SquareTexture(1000, 1000, "assets/shaders/defaultVert.vert", "assets/shaders/defaultFrag.frag", "assets/textures/Daylight Box_Front.bmp", glm::vec3(0.0f, 0.0f, 1000.0f),1));

	std::vector<std::string> tex = { "assets/textures/Daylight Box_Front.bmp","assets/textures/Daylight Box_Left.bmp","assets/textures/Daylight Box_Right.bmp","assets/textures/Daylight Box_Front.bmp","assets/textures/Daylight Box_Bottom.bmp","assets/textures/Daylight Box_Top.bmp" };
	//c = new CubeTexture(1990, 1990, 1990, "assets/shaders/defaultVert.vert", "assets/shaders/defaultFrag.frag", tex, glm::vec3(0.0f, 2.005f, 0.0f));
	//cl = new CubeTextureLighting(4, 2,5, "assets/shaders/lightingVert.vert", "assets/shaders/lightingFrag.frag", tex, glm::vec3(0.0f, 2.005f, 0.0f));
}
void Scene::render()
{
	
	glm::mat4 view = camera.GetViewMatrix();
	 
	for (Shape* shape : shapes) {
		shape->SetView(view);
		shape->draw();
	}
	
	//c->SetView(view);
	//c->draw();
}

Scene::~Scene()
{
	instancePtr = nullptr;
}

void Scene::processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime)
{
	static int cnt = 0;
	if (action == GLFW_REPEAT) {
		return;  // don't respond to repeatedly pressed buttons
	}

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(Window::instancePtr->getWindow(), true);
	}
	else if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_F11) {
			Window::instancePtr->toggleFullscreen();
		}
		if (key == GLFW_KEY_CAPS_LOCK) {
			int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
			glfwSetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR, mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}

	}

}

void Scene::onCursorPositionEvent(double x, double y)
{
	int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
	if (mode == GLFW_CURSOR_NORMAL)
	{
		lastX = Window::getWidth() / 2.0f;
		lastY = Window::getHeight() / 2.0f;
		firstMouse = true;
		return;
	}
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void Scene::processContinuousInput(float& deltaTime)
{
	GLFWwindow* window = Window::instancePtr->getWindow();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(DOWN, deltaTime);
	}
}
