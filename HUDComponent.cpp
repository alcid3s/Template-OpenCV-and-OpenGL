#include "HUDComponent.h"
#include "tigl.h"
#include "Texture.h"
using tigl::Vertex;

HUDComponent::HUDComponent(glm::vec3 transform, int textureMultiplier)
	: textureMultiplier(textureMultiplier) {
	verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, -transform.z / 2), glm::vec2(0, 0)));
	verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
	verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
	verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));
}

HUDComponent::~HUDComponent() {

}

void HUDComponent::draw(Texture texture) {
	tigl::begin(GL_QUADS);
	bindHUD();

	// making texture transparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	texture.bind();
	tigl::shader->enableTexture(true);
	tigl::drawVertices(GL_QUADS, verts);
	tigl::shader->enableTexture(false);
	texture.unbind();

	glEnable(GL_DEPTH_TEST);
	unbindHUD();
	tigl::end();
}

void HUDComponent::bindHUD()
{
	// Change to 2D projection
	glMatrixMode(GL_PROJECTION);

	// Save current projection
	glPushMatrix();

	// Reset matrix
	glLoadIdentity();

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void HUDComponent::unbindHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
