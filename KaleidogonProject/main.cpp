#include "stdafx.h"
#include "canvas.h"
#include <SFML/Graphics.hpp>

int main() {

	// set up the window
	int screenWidth = sf::VideoMode::getDesktopMode().width;
	int screenHeight = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Kaleidogons");
	sf::RenderWindow * windowPtr = &window;

	canvas kaleidogons;

	// pointer to a kaleidogon being dragged.
	// whenever no kaleidogon is being dragged, set it to NULL.
	kaleidogon * draggingKaleidogonPtr = NULL;
	
    while (window.isOpen()) {
		
        sf::Event event;
        while (window.pollEvent(event)) {

			// let the user close the window
            if (event.type == sf::Event::Closed) {
                window.close();
			}

			// let the user leftclick to make and drag kaleidogons
			else if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
				int xpos = event.mouseButton.x;
				int ypos = event.mouseButton.y;

				kaleidogon * kaleidogonPtr = kaleidogons.getKaleidogonAtPosition(xpos, ypos);

				// if the user isn't clicking on a kaleidogon, create one at that spot...
				if (kaleidogonPtr == NULL) {
					kaleidogons.addKaleidogon(event.mouseButton.x, event.mouseButton.y);
				} else {
					// otherwise, start to drag that kaleidogon
					draggingKaleidogonPtr = kaleidogonPtr;
				}
			}

			// let the user stop dragging
			else if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left) && (draggingKaleidogonPtr != NULL)) {

				// if the user dragged a kaleidogon over another kaleidogon,
				// set this kaleidogon's center to that kaleidogon's center

				int xpos = event.mouseButton.x;
				int ypos = event.mouseButton.y;
				kaleidogon * kaleidogonPtr = kaleidogons.getKaleidogonAtPosition(xpos, ypos, draggingKaleidogonPtr);

				if (kaleidogonPtr != NULL) {
					draggingKaleidogonPtr->setPosition(kaleidogonPtr->getPosition());
				}

				// stop dragging
				draggingKaleidogonPtr = NULL;
				
			}

			// let the user reverse rotation of kaleidogons
			else if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Right)) {

				int xpos = event.mouseButton.x;
				int ypos = event.mouseButton.y;
				kaleidogon * kaleidogonPtr = kaleidogons.getKaleidogonAtPosition(xpos, ypos);

				if (kaleidogonPtr != NULL) {
					kaleidogonPtr->setRotationAmount(kaleidogonPtr->getRotationAmount() * -1);
				}
			}
        }

		// if the user is dragging a kaleidogon, make it follow the mouse
		if (draggingKaleidogonPtr != NULL) {
			draggingKaleidogonPtr->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		}

		kaleidogons.rotateKaleidogons();

        window.clear();
		kaleidogons.drawKaleidogons(windowPtr);
        window.display();
    }

    return 0;
}