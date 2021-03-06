#include "Bullets.hpp"


proiettile::proiettile(double x, double y, double rotation, Texture *bullet_tx){
    this->bullet.setTexture(*bullet_tx);
    this->bullet.setOrigin(bullet_tx->getSize().x/2, bullet_tx->getSize().y/2);
    this->bullet.setPosition(x, y);
    this->bullet.setRotation(rotation);
    this->bullet.setTextureRect(IntRect(0, 0, bullet_tx->getSize().x, bullet_tx->getSize().y));
    this->bullet.scale(1,1);
}


Bullets::Bullets(){
    
}


Bullets::Bullets(int time_btw_shoot,int damage, int speed, int tx_nr, bool autoshoot, Resources *src){
    bulletList = new list<proiettile>;
    this->src = src;
    this->autoshoot = autoshoot;
    this->time_btw_shoot = time_btw_shoot;
    this->damage = damage;
    this->speed = speed;
    this->bullet_tx = src->getTexture(tx_nr);
	this->invuln_time = 500;
}


int Bullets::getDamage(){
    return damage;
}


int Bullets::checkCollision(FloatRect p){
    list<proiettile>::iterator it = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    int hit = 0;
    while (it != end){
        if (collidesWith(it,p)){
            hit = damage;
            it = bulletList->erase(it);
        } else {
            it++;
        }
    }
    return hit;
}


bool Bullets::collidesWith(list<proiettile>::iterator p, FloatRect obj){
    return p->bullet.getGlobalBounds().intersects(obj);
}


bool Bullets::outsideBounds(list<proiettile>::iterator p, Terrain *terrain){
    return p->bullet.getPosition().x < 0 ||
     p->bullet.getPosition().x > src->getLength() ||
      p->bullet.getPosition().y < 0 ||
       p->bullet.getPosition().y >= terrain->getTerrainY(p->bullet.getPosition().x - 15);

}


bool Bullets::outsideBounds(list<proiettile>::iterator p){
    return p->bullet.getPosition().x < 0 ||
    p->bullet.getPosition().x > src->getLength() ||
    p->bullet.getPosition().y < 0 || p->bullet.getPosition().y > src->getHeight();
}


void Bullets::handle(Terrain *terrain){
    cleanup(terrain);
    renderBullet();
}
