#include "PlaneComponent.h"
#include "tigl.h"
#include "Texture.h"
using tigl::Vertex;

PlaneComponent::PlaneComponent(glm::vec3 transform, int textureMultiplier)
	: textureMultiplier(textureMultiplier) {
	verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, -transform.z / 2), glm::vec2(0, 0)));
	verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
	verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
	verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));
}

PlaneComponent::~PlaneComponent() {

}

void PlaneComponent::draw(Texture texture) {
	tigl::begin(GL_QUADS);
	tigl::shader->enableColor(true);
	texture.bind();
	tigl::shader->enableTexture(true);
	tigl::drawVertices(GL_QUADS, verts);
	tigl::shader->enableTexture(false);
	texture.unbind();
	tigl::shader->enableColor(false);
	tigl::end();
}