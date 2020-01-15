#include "GPlanet.hpp"

// COSTRUTTORI =======================================

lista_schermate_pianeta::lista_schermate_pianeta(Terreno *terrain_n, int n,
                        int totale_schermate, Resources *src,
                        lista_schermate_pianeta *next_n,
                        lista_schermate_pianeta *prev_n):
    next(next_n),
    prev(prev_n),
    terrain(terrain_n),
    nr_schermata(n)
    {
        enemies = new Bunker(src,terrain);
        carb = Fuel(terrain,src);
    }

lista_schermate_pianeta::lista_schermate_pianeta(Resources *s) :
    next(nullptr),
    prev(nullptr),
    terrain(nullptr),
    nr_schermata(666){
        // TODO: complete this
        //carb = BossFuel(...);
    }

GPlanet::GPlanet(){
    current = nullptr;
    head = nullptr;
	boss = Boss();
	boss_unlocked = false;
    in_boss = false;
    
}

// SETTERS E GETTERS =================================

bool GPlanet::getBoss_unlocked(){
    return this->boss_unlocked;
}

lista_schermate_pianeta *GPlanet::getCurrent(){
    return  this->current;
}

lista_schermate_pianeta *GPlanet::getHead(){
    return  this->head;
}

void GPlanet::setBoss_unlocked(bool boss_unlocked){
    this->boss_unlocked = boss_unlocked;
}

void GPlanet::setCurrent(lista_schermate_pianeta *current){
    this->current = current;
}

void GPlanet::setHead(lista_schermate_pianeta *head){
    this->head = head;
}

bool GPlanet::getIn_boss(){
    return in_boss;
}

// FUNZIONI ==========================================

lista_schermate_pianeta *GPlanet::find(int n){///???
    lista_schermate_pianeta *tmp = head;
    lista_schermate_pianeta *a = nullptr;
    while (tmp != nullptr && a == nullptr){
        if (tmp->nr_schermata == n) a = tmp;
        tmp = tmp->next;
    }
    return a;
}
 


void GPlanet::inizializza(int tot_schermate, Resources *src){
    this->src = src;
    completed = false;
    nr_schermate = tot_schermate;
    lista_schermate_pianeta *tmp = nullptr;
    lista_schermate_pianeta *pre_tmp = nullptr;
    hole_tx = src->caricaTexture(31);
	hole.setTexture(*hole_tx);
	hole.setOrigin(hole_tx->getSize().x / 2, hole_tx->getSize().y / 2);
    if(head == nullptr){
        head = new lista_schermate_pianeta(
            new Terreno(random_height(), random_height(), src, tot_schermate),
            0, tot_schermate, src);
        pre_tmp = head;
        for (int i = 1; i < tot_schermate; i++){
            tmp = new lista_schermate_pianeta(
                new Terreno(random_height(), pre_tmp->terrain->getSxCoord(),src,tot_schermate),
                i, tot_schermate, src, nullptr, pre_tmp);
            pre_tmp->next = tmp;
            pre_tmp = tmp;
        }
        tmp->next = head;
        head->prev = tmp;
        boss_screen = new lista_schermate_pianeta(src);
        boss = Boss(1000, 3, src);
        boss_screen->enemies = new BossBunker(src,boss.getRadius(),boss.getCenter());
        boss.setEnemies((BossBunker *)boss_screen->enemies);
        boss_unlocked = false;
        in_boss = false;
        current = head;
    } else {
        current->enemies->restartTimers();
    }
}

void GPlanet::cambia_schermata(int n){
    if (n != 666){ 
        if (n == 1){
            current = current->next;
        } else {
            current = current->prev;
        }
        current->enemies->restartTimers();
    } else {
        current = boss_screen;
    }
}

void GPlanet::checkCollision(Nave *player) { //maybe this should be split between universe and here
    current->enemies->checkCollision(player->SingleShot);
    current->enemies->checkCollision(player->Laser);
    if (current->enemies->checkCollision(&player->nave) > 0){
        player->getHit(current->enemies->DAMAGEONCOLLISION);
        player->push_back(5,current->nr_schermata == 666);
    }
    if (in_boss){
        boss.checkCollisionBoss(player->SingleShot);
        boss.checkCollisionBoss(player->Laser);
    }
    
    int hit = current->enemies->checkCollisionBBullets(player->nave.getGlobalBounds());
    player->getHit(hit, 0);
}
 
void GPlanet::handle(Nave *player){
    Terreno *terrain = nullptr;
    if (!boss_unlocked)
	    updateBossLock();
    player->raggioTraente();
    checkCollision(player);
    checkTerrain(player);
    if (!in_boss) {
        current->terrain->drawAll();
		current->carb.gestisci();
        raggiotraente(player);
        terrain = current->terrain;//B
	}
	if (boss_unlocked && current == head) src->getWindow()->draw(hole);
	if (in_boss){
        boss.gestisci(); //A
		boss.draw(0);
    }
	current->enemies->gestisci(player, current->terrain); //A
    player->armi(terrain);//B
    
    if(boss.isDead()){
        completed = true;
        player->setPunti(player->getPunti() + 1000);
    }
}

bool GPlanet::inHole(Sprite *body){
    if(boss_unlocked)
        return hole.getGlobalBounds().contains(body->getPosition());
    else return false;
}

void GPlanet::enterBoss(Nave *player){
    in_boss = true;
    cambia_schermata(666);
    player->nave.setPosition(src->getLength()/2,src->getHeight()/2);
}

void GPlanet::checkTerrain(Nave *player){
    if (!in_boss){
        if(inHole(&player->nave))
            enterBoss(player);
        else if (player->nave.getPosition().y + 22 
                    >= 
                getCurrent()->terrain->get_Y(player->nave.getPosition().x))
                player->setIsDead(true);
    } else {
        if(boss.checkCollisionBoss(&player->nave))
            player->push_back(4,1);
    }
}

int GPlanet::random_height(){
    return src->getHeight() - src->rand(0,99);
}

void GPlanet::updateBossLock(){
    bool no_bunkers = true;
    int i = 0;
    lista_schermate_pianeta *iterator = head;
    while (iterator != nullptr && no_bunkers && i < nr_schermate) {
        no_bunkers = no_bunkers && (iterator->enemies->isEmpty());
        iterator = iterator->next;
        i++;
    }
    if (no_bunkers) {
        boss_unlocked = true;
        head->terrain->prepareForBoss(&hole);
    }
}

bool GPlanet::getCompleted(){
    return completed;
}

void GPlanet::raggiotraente(Nave *player){
    if (player->raggioTraente()){
        fuel *tmp = current->carb.getHead();
        while(tmp!=nullptr){
            if(abs(player->nave.getPosition().x - tmp->x) <50 && (tmp->y - player->nave.getPosition().y <=150)){
                fuel *tmp1 = tmp->next;
                cout << player->getFuelbar() << "\n";
                player->setFuelbar(player->getFuelbar() + current->carb.getPower(tmp));
                cout << player->getFuelbar();
                current->carb.delete_fuel(tmp);
                tmp = tmp1;
            } else {
                tmp=tmp->next;
            }
        }
    }
}
