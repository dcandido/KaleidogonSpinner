#include "kaleidogon.h"

class canvas {
public:
	canvas();
	~canvas();
	void addKaleidogon(int xposition, int yposition);
	void rotateKaleidogons();
	void drawKaleidogons(sf::RenderWindow * window);
	kaleidogon* getKaleidogonAtPosition(int xposition, int yposition);
	kaleidogon* getKaleidogonAtPosition(int xposition, int yposition, kaleidogon *exception);

private:
	kaleidogon ** kaleidogonPtrArray;
	int arraySize;

	static int canvas::getDistanceSquared(int x1, int y1, int x2, int y2) {
		int distanceSquared = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
		return distanceSquared;
	}
};

