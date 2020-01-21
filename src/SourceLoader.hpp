#pragma once
#include <iostream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstring>
#include <fstream>

using namespace std;
using namespace sf;

class SourceLoader{
    
protected:
    
    int height;
    int length;
    int primaryDamage;
    int secondaryDamage;
    String path;
    SoundBuffer sound[3];
    Texture texture[44];
    Font font[2];
    ContextSettings settings;
    RenderWindow window;
    Time timePerFrame;      // Determines how many fps
    Time utilityTime;       // For transitions
    Clock utilityClock;     // For transitions
    void loadTextures();
    void loadSounds();
    void loadFonts();
    
public:
    
    SourceLoader();
    int getHeight();
    int getLength();
    int getPrimaryDamage();
    int getSecondaryDamage();
    String *getPath();
    SoundBuffer *getSound(int n);
    Texture *getTexture(int n);
    Font *getFont(int n);
    RenderWindow *getWindow();
    Time *getTimePerFrame();
    Time *getUtilityTime();
    Clock *getUtilityClock();
    
};

/*
 
 SOUNDS:
 0.ogg - player bullet
 1.ogg - button pushed
 2.ogg - button selected
 
 FONTS:
 0.ttf - Text
 1.ttf - Demonized
 
 TEXTURES:
 0.png - player bullet
 1.png - player laser
 2.png - slider
 3.png - bunker triple bullet
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
 22.png - slider axis
 23.png - new game button
 24.png - back button
 25.png - main menu background
 26.png - credits background
 27.png - highscore background
 28.png - universe background
 29.png - planet soil
 30.png - thrust
 31.png - hole
 32.png - boss
 33.jpg - boss background
 34.png - settings button
 35.png - settings background
 36.png - pause background (need to be overwritten)
 37.png - highscore button
 38.png - main menu button
 39.png - pause button
 40.png - resume button
 41.png - game over background
 42.png - bunker one bullet
 43.png - boss bunker

 */
