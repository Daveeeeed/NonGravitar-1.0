#ifndef Resources_hpp
#define Resources_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;
using namespace sf;

class Resources{
    
protected:
    
    int height;
    int length;
    Time timePerFrame;      // Determines how many fps
    Time utility_time;      // For transitions
    Clock utility_clock;    // For transitions
    RenderWindow window;
    ContextSettings settings;
    String localPath[3];
    SoundBuffer sound[3];
    Texture texture[34];
    Font font[2];
    void loadTextures();
    void loadSounds();
    void loadFonts();
    
public:
    
    Resources();
    int getHeight();
    int getLength();
    SoundBuffer caricaSuono(int n);
    Texture *caricaTexture(int n);
    Font getFont(int n);
    RenderWindow *getWindow();
    Time *getTimePerFrame();
    
};

/*
 
 SOUNDS:
 0.ogg - player bullet
 1.ogg - button pushed
 2.ogg - button selected

 TEXTURES:
 0.png - player bullet
 1.png - player laser
 2.png - main universe background
 3.png - bunker
 4.png - spaceship
 5.png - planet type 1
 6.png - planet type 2
 7.png - planet type 3
 8.png - planet type 4
 9.png - planet type 5
 10.png - planet type 6
 11.png - planet type 7
 12.png - planet type 8
 13.png - inside planet background
 14.png - enemies bullet type 1
 15.png - enemies bullet type 2
 16.png - life/fuel bar
 17.png - tractor beam //raggio traente
 18.png - fuel tank
 19.png - explosion type 1
 20.png - explosion type 2
 21.png - credits button
 22.png - exit button
 23.png - play button
 24.png - play button
 25.png - main menu type 1
 26.png - main menu type 2
 27.png - main menu type 3
 28.png - paused game backgroung
 29.png - planet soil
 30.png - thrust
 31.png - settings button
 32.png - settings background
 33.png - temporarly background for pause/game over
 
 FONTS:
 0.ttf - Text
 1.ttf - Demonized
 
*/

#endif /* Risorse_hpp */