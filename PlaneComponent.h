#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include <vector>
using tigl::Vertex;

class Texture;

class PlaneComponent {
	std::vector<Vertex> verts;
public:
	PlaneComponent(glm::vec3 transform, int textureMultiplier = 1);
	~PlaneComponent();

	void draw(Texture texture);
private:
	int textureMultiplier;
};