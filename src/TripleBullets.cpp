#include "TripleBullets.hpp"


TripleBullets::TripleBullets(){
    
}


TripleBullets::TripleBullets(int time_btw_shoot, int damage, int speed,
                             int tx_nr, bool autoshoot, Resources *src):
    Bullets(time_btw_shoot,damage,speed,tx_nr,autoshoot,src){
        left = SingleStraightBullets(time_btw_shoot,damage,speed,tx_nr,autoshoot,src);
        centre = SingleStraightBullets(time_btw_shoot,damage,speed,tx_nr,autoshoot,src);
        right = SingleStraightBullets(time_btw_shoot,damage,speed,tx_nr,autoshoot,src);
    }


void TripleBullets::addSingleBullet(Sprite entity, Keyboard::Key pulsante){
    Sprite t = entity;
    centre.addSingleBullet(t,pulsante);
    t.setRotation(t.getRotation() - 30);
    left.addSingleBullet(t,pulsante);
    t.setRotation(t.getRotation() + 60);
    right.addSingleBullet(t,pulsante);
}


void TripleBullets::renderBullet(){
    left.renderBullet();
    centre.renderBullet();
    right.renderBullet();
}


int TripleBullets::checkCollision(FloatRect p){
    return left.checkCollision(p) + right.checkCollision(p) + centre.checkCollision(p);
}


void TripleBullets::cleanup(Terrain *terrain){
    left.cleanup(terrain);
    centre.cleanup(terrain);
    right.cleanup(terrain);
}

