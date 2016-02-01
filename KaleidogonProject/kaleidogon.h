#include "stdafx.h"
#include <SFML/Graphics.hpp>

class kaleidogon : public sf::CircleShape {
public:
	kaleidogon();
	int getRotationAmount();
	void setRotationAmount(int newRotationAmount);
	
private:
	static const int NUMBER_OF_VERTICES = 6; // all hexagons have six vertices
	int rotationAmount;
	sf::Texture texture;
	sf::Texture * ptTexture;
};