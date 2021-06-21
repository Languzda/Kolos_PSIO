#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "AvengerSprite.h"

int Check_clolision(std::vector<std::unique_ptr<AvengerSprite>> &actors,const sf::RenderWindow &window) {
    Thor &thor = dynamic_cast<Thor&>(*actors[0]);

    for (auto it = actors.begin() + 1; it != actors.end(); it++) {
        if ((*it)->getGlobalBounds().intersects(thor.getGlobalBounds())) {
            if ((*it)->getName() == "stone") {
                thor.update(100, 0);
            }
            if ((*it)->getName() == "alien") {
                thor.update(0, -1);
                thor.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            }
            it = actors.erase(it);
            break;
        }
    }

    if (thor.getHP() < 1) return 2;
    else if (thor.getPoints() > POCZATKOWA_LICZBA_KAMIENI*KAMIEN_BONUSOWE_PUNKTY) return 1;
    else return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(ROZMIAR_OKNA_X, ROZMIAR_OKNA_Y), "Thor");
    std::vector<std::unique_ptr<AvengerSprite>> Actors;
    std::vector<std::unique_ptr<sf::Texture>> tekstury;

    auto thor = std::make_unique<Thor>(  Thor( window.getSize().x / 2, window.getSize().y / 2, 0, 150));
    auto texture =std::make_unique<sf::Texture>();
    if (texture->loadFromFile("textures/thor.png")) {   
        
    }
    tekstury.emplace_back(std::move(texture));
    thor->setTexture(*tekstury[0]);
    thor->setScale(0.1, 0.1);
    Actors.emplace_back(std::move(thor));

    auto textureK = std::make_unique<sf::Texture>();
    if (textureK->loadFromFile("textures/kamien.png")) {
      
        tekstury.emplace_back(std::move(textureK));
        for (int i = 0; i < 6; i++) {
            auto stone = std::make_unique<KamienNieskonczonosci>(KamienNieskonczonosci(rand()%window.getSize().x , rand()%window.getSize().y, 0, KAMIEN_PREDKOSC));
            stone->setTexture(*tekstury[1]);
            stone->setScale(0.1, 0.1);
            Actors.emplace_back(std::move(stone));
        }
    }
    

    auto textureA = std::make_unique<sf::Texture>();
    if (textureA->loadFromFile("textures/alien.png")) {
        textureA->setRepeated(false);
        tekstury.emplace_back(std::move(textureA));
        for (int i = 0; i < 20; i++) {
            auto alien = std::make_unique<StworOutrider>(StworOutrider(rand() % window.getSize().x, rand() % window.getSize().y, STWOR_PREDKOSC, 0));
            alien->setTexture(*tekstury[2]);
            alien->setScale(0.1, 0.1);
            Actors.emplace_back(std::move(alien));
        }
    }

    
    sf::Event event;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        for (auto& actor : Actors) {
            actor->Movement();
            actor->Animuj(elapsed);
        }
        


        if (int buff=Check_clolision(Actors, window) != 0) {
            if (buff == 1) std::cout << "Lose";
            if (buff == 2) std::cout << "Win";
            break;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                for (auto& aktor : Actors) {

                        sf::FloatRect aktor_bounds = aktor->getGlobalBounds();
                        if ((mouse_pos.x >= aktor_bounds.left && mouse_pos.x <= aktor_bounds.left + aktor_bounds.width) &&
                            (mouse_pos.y >= aktor_bounds.top && mouse_pos.y <= aktor_bounds.top + aktor_bounds.height)) {
                            if (aktor->getName() == "alien") {
                                StworOutrider& alien = dynamic_cast<StworOutrider&>(*aktor);
                                alien.Scale_up();
                            }
                            if (aktor->getName() == "stone") {
                                KamienNieskonczonosci& stone = dynamic_cast<KamienNieskonczonosci&>(*aktor);

                                stone.setPosition(rand() % (ROZMIAR_OKNA_X),rand() % (ROZMIAR_OKNA_Y));
                            }

                        }
                    
                }
             
            }
        }

        window.clear();
        for (auto& actor : Actors) {
            window.draw(*actor);
        }

        window.display();
    }
    window.close();
    getchar();
    
    return 0;;
}

