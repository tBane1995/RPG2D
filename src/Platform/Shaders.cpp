#include "Shaders.h"
#include "Window.h"
#include "Time.h"
#include "Camera.h"
#include <iostream>

Shader::Shader(std::string pathfile) {
	name = "";
		
	short i = short(pathfile.size()) - 6;
	while (i >= 0)
	{
		name = pathfile[i--] + name;
	}

	shader = new sf::Shader();
	shader->loadFromFile("assets/" + pathfile, sf::Shader::Fragment);
	//cout << "load shader: " << pathfile << " as: " << name << endl;
}

std::vector < Shader* > shaders;

void loadShader(std::string name, std::string vertex_pathfile, std::string fragment_pathfile) {
	shaders.push_back(new Shader(name, vertex_pathfile, fragment_pathfile));
}

void loadShader(std::string pathfile) {
	shaders.push_back(new Shader(pathfile));
}

void loadShaders() {
	loadShader("shaders/empty.frag");
	loadShader("shaders/water.frag");
	loadShader("shaders/lake", "shaders/vertex.vert", "shaders/lake.frag");
	loadShader("shaders/palette_lake", "shaders/vertex.vert", "shaders/palette_lake.frag");
	loadShader("shaders/shadow", "shaders/vertex.vert", "shaders/shadow.frag");
	loadShader("shaders/circle.frag");
	loadShader("shaders/jagged_circle.frag");
	loadShader("shaders/circles.frag");

}

Shader* getShader(std::string name) {

	for (auto& s : shaders) {
		if (s->name == name) {
			return s;
		}
	}

	std::cout << "error - get Shader - Shader: \"" << name << "\" not exists\n";
	return nullptr;
}

void updateShaders() {

	sf::Vector2f resolution(screenWidth, screenHeight);

	for (auto& s : shaders)
	{
		s->shader->setUniform("time", currentTime.asSeconds());
	}

	// lake shader
	Shader* s = getShader("shaders/lake");
	s->shader->setUniform("resolution", resolution);

	// palette_lak
	s = getShader("shaders/palette_lake");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("camPosition", cam->position);
}
