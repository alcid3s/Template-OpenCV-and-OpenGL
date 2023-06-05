#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include <vector>
using tigl::Vertex;

class Texture;

class HUDComponent {
	std::vector<Vertex> verts;
public:
	HUDComponent(glm::vec3 transform, int textureMultiplier = 1);
	~HUDComponent();

	void draw(Texture texture);
private:
	int textureMultiplier;

private:
	void bindHUD();
	void unbindHUD();
};