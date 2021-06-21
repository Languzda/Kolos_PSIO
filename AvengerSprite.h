#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define ROZMIAR_OKNA_X  800
#define ROZMIAR_OKNA_Y  800
#define THOR_PREDKOSC 150.f
#define STWOR_PREDKOSC 100.f
#define KAMIEN_PREDKOSC -50.f
#define POCZATKOWA_LICZBA_STWOROW 20
#define POCZATKOWA_LICZBA_KAMIENI 6
#define KAMIEN_BONUSOWE_PUNKTY 100

class AvengerSprite : public sf::Sprite
{
public:
	AvengerSprite(int posX, int posY,
		float vX, float vY);
	virtual ~AvengerSprite() = 0;
	virtual void Movement() = 0;
	void Animuj(const sf::Time& elapsed);
	virtual std::string getName()=0;
protected:
	float velocity_x_=0;
	float velocity_y_=0;
};

class Thor : public AvengerSprite
{
public:
	Thor(int posX, int posY,
		float vX, float vY);
	~Thor();
	void Movement();
	void update(const int& pkt, const int& hp);
	int getHP();
	int getPoints();
	std::string getName();
private:
	float base_speed_;
	sf::Vector2f mouse_move_speed;
	int HP_=3;
	int points_=0;
};

class KamienNieskonczonosci : public AvengerSprite
{
public:
	KamienNieskonczonosci(int posX, int posY,float vX, float vY);
	~KamienNieskonczonosci();
	void Movement() {};
	std::string getName();


};

class StworOutrider : public AvengerSprite
{
public:
	StworOutrider(int posX, int posY, float vX, float vY);
	~StworOutrider();
	void Movement() {};
	void Scale_up();
	std::string getName();
private:
	float scale = 0.1;
};


