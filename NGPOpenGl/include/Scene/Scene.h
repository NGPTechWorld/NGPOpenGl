#pragma once
#include "core.h"
#include "cube.h"
#include "ModelObject.h"
#include "Camera.h"
#include <memory>
#include <vector>
#include "model.h"

class Scene
{
public:
	Scene();
	~Scene();
	void render();
	inline glm::vec3& getCameraPosition() { return camera.Position; }
	inline Camera& getCamera() { return camera; };

	void onCursorPositionEvent(double x, double y);
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void processContinuousInput(float& deltaTime);



	static Scene* instancePtr;
private:
	
	Camera camera;
	float lastX, lastY;
	bool firstMouse;
	
};

