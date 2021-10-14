#include "TextMan.h"

unordered_map<string, sf::Texture> TextMan::textures;

void TextMan::LoadTexture(string filename) {
	string path = "images/";
	path += filename + ".png";

	textures[filename].loadFromFile(path);
}

sf::Texture& TextMan::GetTexture(string filename) {
	if (textures.find(filename) == textures.end()) {
		LoadTexture(filename);
	}
	
	return textures[filename];
}

void TextMan::Clear() {
	textures.clear();
}
