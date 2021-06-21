#include "AvengerSprite.h"

AvengerSprite::AvengerSprite(int posX, int posY,
	float vX, float vY) : sf::Sprite() {
	this->velocity_x_ = vX;
	this->velocity_y_ = vY;
	this->setPosition(posX, posY);
}

AvengerSprite::~AvengerSprite(){}

void AvengerSprite::Animuj(const sf::Time& elapsed) {

    if (this->getGlobalBounds().top < 0) this->velocity_y_ = abs(velocity_y_);
    if (this->getGlobalBounds().top + this->getGlobalBounds().height > ROZMIAR_OKNA_Y) this->velocity_y_ = -abs(velocity_y_);
        if (this->getGlobalBounds().left < 0) this->velocity_x_=abs(velocity_x_);
        if (this->getGlobalBounds().left + this->getGlobalBounds().width > ROZMIAR_OKNA_X) this->velocity_x_ = -abs(velocity_x_);
    

    this->move(velocity_x_ * elapsed.asSeconds(), velocity_y_ * elapsed.asSeconds());
}

Thor::Thor(int posX, int posY,float vX, float vY) : AvengerSprite(posX, posY, vX, vY)
{
    this->base_speed_ = vY;
}

void Thor::Movement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->velocity_x_ = -base_speed_;
        this->velocity_y_ = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->velocity_x_ = base_speed_;
        this->velocity_y_ = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->velocity_x_ = 0;
        this->velocity_y_ = -base_speed_;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->velocity_x_ = 0;
        this->velocity_y_ = base_speed_;
    }
}

void Thor::update(const int &pkt,const int &hp) {
    this-> points_ += pkt;
    this->HP_ += hp;
}

int Thor::getHP() { return this->HP_; }
int Thor::getPoints() { return this->points_; }

std::string Thor::getName() { return "thor"; }

Thor::~Thor()
{
}

KamienNieskonczonosci::KamienNieskonczonosci(int posX, int posY,
    float vX, float vY) : AvengerSprite(posX, posY, vX, vY){}

void StworOutrider::Scale_up() {
    if (scale < 0.8) {
        this->scale *= 2;
        this->setScale(scale, scale);
    }
}

std::string KamienNieskonczonosci::getName() { return "stone"; }

KamienNieskonczonosci::~KamienNieskonczonosci()
{
}

StworOutrider::StworOutrider(int posX, int posY, float vX, float vY)
    : AvengerSprite(posX, posY, vX, vY) {
    if (rand() % 2 == 0) this->velocity_x_ = -abs(velocity_x_);
}

std::string StworOutrider::getName() { return "alien"; }

StworOutrider::~StworOutrider()
{
}
