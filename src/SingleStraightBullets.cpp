#include "SingleStraightBullets.hpp"

using namespace sf;
//tx_nr dovrebbe essere deciso qui invece che dal caller
SingleStraightBullets::SingleStraightBullets(int time_btw_shoot, int damage, int speed, 
                                int tx_nr, int sd_nr, bool autoshoot, Resources *src):
                                Bullets(time_btw_shoot,damage,speed,tx_nr,sd_nr,autoshoot,src){}

void SingleStraightBullets::addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo){
    double x = entity.getPosition().x;
    double y = entity.getPosition().y;
    double rotation = entity.getRotation();
    Time elapsed = bullet_time.getElapsedTime();
    if ((!autoshoot && Keyboard::isKeyPressed(pulsante) && elapsed.asMilliseconds()>time_btw_shoot) || 
        (autoshoot && elapsed.asMilliseconds() > (time_btw_shoot + tempo))) { //perché tempo? a cosa dovrebbe servire
        proiettile *tmp = head;
        head = new proiettile(tmp);
        spriteSetup(head,x,y,rotation);
        bullet_time.restart();
    }
}

void SingleStraightBullets::renderBullet(Terreno *terrain, Time perFrame){
    proiettile *pointer = head;
    Time elapsed;
    while (pointer != NULL){
		elapsed = pointer->invuln_clock.getElapsedTime();
		if ((elapsed.asMilliseconds() > invuln_time) &&
			outsideBounds(pointer, terrain)){
            proiettile *tmp = pointer;
            pointer = pointer->next;
            deleteBullet(tmp);
        } else {
            double angle = M_PI * pointer->bullet.getRotation() / 180;
            pointer->bullet.move(-sin(angle)*speed*perFrame.asSeconds()*100,
                             cos(angle)*speed*perFrame.asSeconds()*100);
            src->getWindow()->draw(pointer->bullet);
            pointer = pointer->next;
        }
    }
}

SingleStraightBullets::SingleStraightBullets(){}

int SingleStraightBullets::checkCollision(FloatRect p){
    proiettile *tmp = head;
    int hit_counter = 0;
    while (tmp != NULL){
        if (collidesWith(tmp,p)){
            hit_counter++;
            proiettile *target = tmp;
            tmp = tmp->next;
            deleteBullet(target);
        } else {
            tmp = tmp->next;
        }
    }
    return hit_counter;
}