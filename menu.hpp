#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include "game.hpp"

class Menu{
    private:
        sf::RenderWindow mainwind;
        sf::RectangleShape button1;
        sf::RectangleShape button2;
        sf::Font font;
        sf::Text text1, text2, maintext;
        sf::Vector2u sizewind;
    public:
        Menu(unsigned int _w, unsigned int _h) : mainwind(sf::VideoMode(_w , _h), "Tik-tok"), sizewind(_w,_h){
            mainwind.setSize(sizewind);

            button1.setSize(sf::Vector2f(_w / 2, _h / 3 - 30));
            button2.setSize(sf::Vector2f(_w / 2, _h / 3 - 30));

            button1.setFillColor(sf::Color::White);
            button2.setFillColor(sf::Color::White);

            button1.setOutlineThickness(10.f);
            button2.setOutlineThickness(10.f);

            button1.setOutlineColor(sf::Color(255, 255, 0));
            button2.setOutlineColor(sf::Color(255, 255, 0));

            button1.setPosition(sf::Vector2f(_w / 4, _h / 3));
            button2.setPosition(sf::Vector2f(_w / 4, 2 * _h / 3));
        }
        void Init(){
            if (!font.loadFromFile("arial.ttf")) {
                std::cerr << "ERROR LOAD FONT" << std::endl;
                return;
            }
            text1.setFont(font);
            text2.setFont(font);
            maintext.setFont(font);
            maintext.setString(L"Крестики-нолики");
            text1.setString(L"ПВП");
            text2.setString(L"ComputerMind");

            text1.setFillColor(sf::Color::Black);
            text2.setFillColor(sf::Color::Black);
            maintext.setFillColor(sf::Color::Black);

            maintext.setCharacterSize(sizewind.y / 10);
            text1.setCharacterSize(sizewind.y / 10 );
            text2.setCharacterSize(sizewind.y / 10 );
            maintext.setPosition(sf::Vector2f(sizewind.x/4, 0));
            text1.setPosition(sf::Vector2f(sizewind.x/4 + 10.f, sizewind.y / 3  + 35));
            text2.setPosition(sf::Vector2f(sizewind.x/4 + 10.f, 2 * sizewind.y / 3 + 35));
        }

        void start(){

            sf::Event evn;

            while(mainwind.isOpen()){

                while(mainwind.pollEvent(evn)){
                    switch(evn.type) {
                        case sf::Event::Closed:{
                            mainwind.close();
                            break;
                        }
                        case sf::Event::MouseMoved:{
                            if( evn.mouseMove.x < button1.getPosition().x + button1.getSize().x && 
                                evn.mouseMove.x > button1.getPosition().x &&
                                evn.mouseMove.y > button1.getPosition().y &&
                                evn.mouseMove.y < button1.getPosition().y + button1.getSize().y ) {
                                    button1.setFillColor(sf::Color(255,255,200));
                            }else {
                                button1.setFillColor(sf::Color::White);
                            }
                            if( evn.mouseMove.x < button2.getPosition().x + button2.getSize().x && 
                                evn.mouseMove.x > button2.getPosition().x &&
                                evn.mouseMove.y > button2.getPosition().y &&
                                evn.mouseMove.y < button2.getPosition().y + button2.getSize().y ) {
                                    button2.setFillColor(sf::Color(255,255,200));
                            } else {
                                button2.setFillColor(sf::Color::White);
                            }
                            break;
                        }
                        case sf::Event::MouseButtonPressed:{
                            if( evn.mouseButton.x < button1.getPosition().x + button1.getSize().x && 
                                evn.mouseButton.x > button1.getPosition().x &&
                                evn.mouseButton.y > button1.getPosition().y &&
                                evn.mouseButton.y < button1.getPosition().y + button1.getSize().y ) {
                                    GamePvP g(800);
                                    int p = g.Init();
                                    if(!p)
                                        g.start1();
                                }
                                if( evn.mouseButton.x < button2.getPosition().x + button2.getSize().x && 
                                evn.mouseButton.x > button2.getPosition().x &&
                                evn.mouseButton.y > button2.getPosition().y &&
                                evn.mouseButton.y < button2.getPosition().y + button2.getSize().y ) {
                                    GameAI g(800);
                                    int p = g.Init();
                                    if(!p)
                                        g.start1();
                                }
                                break;
                        }
                        default:
                            break;
                    }
                }

                mainwind.clear(sf::Color(252,200,230,255));
                mainwind.draw(button1);
                mainwind.draw(button2);
                mainwind.draw(text1);
                mainwind.draw(text2);
                mainwind.draw(maintext);
                

                mainwind.display();


            }

        }
};

#endif