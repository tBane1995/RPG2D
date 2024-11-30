#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Shader {
public:
	std::string name;
	sf::Shader* shader;

	Shader(std::string pathfile);
	Shader(std::string name, std::string vertex_pathfile, std::string fragment_pathfile) {

		this->name = name;
		shader = new sf::Shader();
		shader->loadFromFile("assets/" + vertex_pathfile, "assets/" + fragment_pathfile);
		//cout << "load shader: " << vertex_pathfile << ", " << fragment_pathfile << " as: " << name << endl;
	}
};

extern std::vector < Shader* > shaders;

void loadShader(std::string name, std::string vertex_pathfile, std::string fragment_pathfile);
void loadShader(std::string pathfile);
void loadShaders();
Shader* getShader(std::string name);
void updateShaders();
