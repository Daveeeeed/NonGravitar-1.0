#include <ctime>
#include "Game.hpp"
#include <unistd.h>
#include <stdio.h>

int main() {
    
    // INIZIALIZZAZIONE ==============================
    Resources src;
    Game game = Game(&src);
    Time timeSinceLastUpdate = Time::Zero;
    Clock deltaClock;       // This will track how much time has past since the last frame

    string line;
    fstream infile;
    infile.open("./resources/highscore", fstream::in | fstream::out);
    while(getline(infile,line)) // To get you all the lines.
    {
        ; // Saves the line in STRING.
        cout<<line; // Prints our STRING.
    }
    infile.close();
    
    // FINESTRA ======================================
	while (src.getWindow()->isOpen()) {
		Event event1;
		while (src.getWindow()->pollEvent(event1)) {
			if (event1.type == Event::Closed)
				src.getWindow()->close();
		}
        Time deltaTime = deltaClock.restart();  // Restart returns the time since the last restart call
        timeSinceLastUpdate += deltaTime;
        if (timeSinceLastUpdate >= *src.getTimePerFrame()){
            src.getWindow()->clear(Color::Black);
            timeSinceLastUpdate -= *src.getTimePerFrame();
            game.handle();
            src.getWindow()->display();
        }
    }
	return 0;
}
