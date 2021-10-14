#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

class TextMan {
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string name);
public:
	static sf::Texture& GetTexture(string name);
	static void Clear();
};
