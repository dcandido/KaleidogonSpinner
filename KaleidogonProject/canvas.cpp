#include "StdAfx.h"
#include "canvas.h"


canvas::canvas() {
	arraySize = 0;
	kaleidogonPtrArray = new kaleidogon*[0];
}

canvas::~canvas() {
	for (int i = 0; i < arraySize; i++) {
		delete kaleidogonPtrArray[i];
	}
	delete [] kaleidogonPtrArray;
}

void canvas::addKaleidogon(int xposition, int yposition) {

	kaleidogon ** oldKaleidogonPtrArray = kaleidogonPtrArray;

	// set up a new kaleidogon
	kaleidogon *newKaleidogonPtr;
	newKaleidogonPtr = new kaleidogon;
	newKaleidogonPtr->setPosition(xposition, yposition);
	
	// find the appropriate index of the new kaleidogon,
	// so that the array is sorted by radius descending
	int radius = newKaleidogonPtr->getRadius();
	int index = 0;
	while (index < arraySize) {
		if (radius > oldKaleidogonPtrArray[index]->getRadius()) {
			break;
		} else {
			index++;
		}
	}

	// now make the new array, which has a size one larger...
	arraySize++;

	kaleidogonPtrArray = new kaleidogon*[arraySize];

	// put the old kaleidogons into the new array, until reaching the new kaleidogon
	for (int i = 0; i < index; i++) {
		kaleidogonPtrArray[i] = oldKaleidogonPtrArray[i];
	}

	// put the new kaleidogon into the new array
	kaleidogonPtrArray[index] = newKaleidogonPtr;

	// put the rest of the old kaleidogons into the new array
	for (int i = index + 1; i < arraySize; i++) {
		kaleidogonPtrArray[i] = oldKaleidogonPtrArray[i-1];
	}

	delete [] oldKaleidogonPtrArray;
	
}

void canvas::rotateKaleidogons() {
	for (int index = 0; index < arraySize; index++) {
		int rotationAmount = kaleidogonPtrArray[index]->getRotationAmount();
		kaleidogonPtrArray[index]->rotate(rotationAmount);
	}
}

void canvas::drawKaleidogons(sf::RenderWindow * window) {
	for (int index = 0; index < arraySize; index++) {
		kaleidogon shapeToDraw = *kaleidogonPtrArray[index];
		window->draw(shapeToDraw);
	}
}

// returns a pointer to the kaleidogon at that position
// if there is no kaleidogon at that position, returns null
kaleidogon* canvas::getKaleidogonAtPosition(int xposition, int yposition) {

	// loop backwards, in order to prioritize the kaleidogon with smallest radius
	for (int index = arraySize - 1; index >= 0; index--) {

		kaleidogon * kaleidogonPtr = kaleidogonPtrArray[index];

		sf::Vector2f kaleidogonPosition = kaleidogonPtr->getPosition();
		int kaleidogonx = kaleidogonPosition.x;
		int kaleidogony = kaleidogonPosition.y;
		int kaleidogonRadius = kaleidogonPtr->getRadius();

		if (getDistanceSquared(kaleidogonx, kaleidogony, xposition, yposition) < (kaleidogonRadius * kaleidogonRadius)) {
			return kaleidogonPtr;
		}
	}
	return NULL;
}

// if called with a kaleidogon exception, don't return that kaleidogon
kaleidogon* canvas::getKaleidogonAtPosition(int xposition, int yposition, kaleidogon *exception) {

	// loop backwards, in order to prioritize the kaleidogon with smallest radius
	for (int index = arraySize - 1; index >= 0; index--) {

		kaleidogon * kaleidogonPtr = kaleidogonPtrArray[index];

		// check all kaleidogons except the exception
		if (kaleidogonPtr != exception) {
			sf::Vector2f kaleidogonPosition = kaleidogonPtr->getPosition();
			int kaleidogonx = kaleidogonPosition.x;
			int kaleidogony = kaleidogonPosition.y;
			int kaleidogonRadius = kaleidogonPtr->getRadius();

			if (getDistanceSquared(kaleidogonx, kaleidogony, xposition, yposition) < (kaleidogonRadius * kaleidogonRadius)) {
				return kaleidogonPtr;
			}
		}
	}
	return NULL;
}