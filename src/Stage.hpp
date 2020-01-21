#pragma once
#include "Pulsante.hpp"
#include "Slider.hpp"

class Stage{
    
protected:
    
    Resources *src;
    Sprite background;
    list<Pulsante*> buttonList;
    list<Slider*> sliderList;
    list<Text*> textList;
    bool sliderSelected;
    
public:
    
    Stage();
    Stage(Resources *src, int tx_sfondo);
    
    Sprite* getBackground();
    list<Pulsante*> *getButtonsList();
    list<Slider*> *getSliderList();
    list<Text*> *getTextList();
    
    void addButton(Vector2f position, int tx_nr, float scale, char name[]);
    void addSlider(Vector2f position, float min, float max, char name[]);
    Text* addText(Vector2f position, String text, Color fillColor, Color outlineColor, int size, float border);
    void drawBackground();
    void drawObjects();
};
