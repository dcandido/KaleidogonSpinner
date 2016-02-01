#include "stdafx.h"
#include "kaleidogon.h"
#include <string>

kaleidogon::kaleidogon() {

	const int TEXTURE_WIDTH = 1024;
	const int TEXTURE_HEIGHT = 1024;

	// constants for determining random rotation speed
	const int MAX_MULTIPLIER = 600;
	const int MIN_MULTIPLIER = 200;
	const int DIVISOR = 100000;

	setPointCount(NUMBER_OF_VERTICES);

	// make the radius a random number up to 1/8 of the screen width
	srand (time(NULL));
	int screenWidth = sf::VideoMode::getDesktopMode().width;
	int newRadius = (rand() % (screenWidth / 8)) + 1;
	setRadius(newRadius);

	setOrigin(newRadius, newRadius);

	// make the rotation speed a random percent of the clock speed
	int randomMultiplier = (rand() % (MAX_MULTIPLIER - MIN_MULTIPLIER + 1)) + MIN_MULTIPLIER;
	rotationAmount = CLOCKS_PER_SEC * randomMultiplier / DIVISOR;

	// 50% chance of reversing the rotation direction
	if (rand() % 2 == 0) {
		rotationAmount *= -1;
	}

	// get random coordinates of the texture
	int randomx = rand() % (TEXTURE_WIDTH - newRadius + 1);
	int randomy = rand() % (TEXTURE_HEIGHT - newRadius + 1);

	// set the texture with these coordinates
	sf::IntRect texturePart(randomx, randomy, newRadius, newRadius);
	texture.loadFromFile("texture.jpg", texturePart);
	ptTexture = &texture;
	setTexture(ptTexture);
}

int kaleidogon::getRotationAmount() {
	return rotationAmount;
}

void kaleidogon::setRotationAmount(int newRotationAmount) {
	rotationAmount = newRotationAmount;
}