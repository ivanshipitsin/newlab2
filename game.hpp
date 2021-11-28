#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "AI.hpp"


int checkwin(Field& f, sf::Vector2f& start, sf::Vector2f& end){
    int len = f.GetLen();
    std::string str[4] = {"         ", "         ", "         ", "         "};
    std::string::size_type k1[4];
    std::string::size_type k2[4];
    for(int i = 0; i < len ; i++){
        for(int j = 0; j < len; j++){
            for(int k = -4; k <= 4; k++){
                if(i+k >= 0 && i + k < len && j + k >= 0 && j + k < len)
                    str[0][k+4] = f.Get(i + k, j + k);
                if(i+k >= 0 && i + k < len)
                    str[1][k+4] = f.Get(i + k, j);
                if(j + k >= 0 && j + k < len)
                    str[2][k+4] = f.Get(i, j + k);
                if(i+k >= 0 && i + k < len && j - k >= 0 && j - k < len)
                    str[3][k+4] = f.Get(i + k, j - k);
            }
            for(int l = 0; l < 4; l++){
                k1[l] = str[l].find("XXXXX");
                k2[l] = str[l].find("OOOOO");
            }
            if(k1[0] != std::string::npos){
                start.x = i + k1[0] - 4;
                start.y = j + k1[0] - 4;
                end.x = i + k1[0];
                end.y = j + k1[0];
                return 1;
            }
            if(k1[1] != std::string::npos){
                start.x = i + k1[1] - 4;
                start.y = j ;
                end.x = i + k1[1];
                end.y = j ;
                return 1;
            }
            if(k1[2] != std::string::npos){
                start.x = i ;
                start.y = j + k1[2] - 4;
                end.x = i ;
                end.y = j + k1[2];
                return 1;
            }
            if(k1[3] != std::string::npos){
                start.x = i + k1[3] - 4;
                start.y = j - k1[3] + 4;
                end.x = i + k1[3];
                end.y = j - k1[3];
                return 1;
            }
            if(k2[0] != std::string::npos){
                start.x = i + k2[0] - 4;
                start.y = j + k2[0] - 4;
                end.x = i + k2[0];
                end.y = j + k2[0];
                return 2;
            }
            if(k2[1] != std::string::npos){
                start.x = i + k2[1] - 4;
                start.y = j;
                end.x = i + k2[1];
                end.y = j;
                return 2;
            }
            if(k2[2] != std::string::npos){
                start.x = i ;
                start.y = j + k2[2] - 4;
                end.x = i ;
                end.y = j + k2[2];
                return 2;
            }
            if(k2[3] != std::string::npos){
                start.x = i + k2[3] - 4;
                start.y = j - k2[3] + 4;
                end.x = i + k2[3];
                end.y = j - k2[3];
                return 2;
            }
            k1[0]=k1[1]=k1[2]=k1[3]=0;
            k2[0]=k2[1]=k2[2]=k2[3]=0;
            str[0] = "         ";
            str[1] = "         ";
            str[2] = "         ";
            str[3] = "         ";
        }
    }
    return 0;
}


class GamePvP {
    private:
        sf::RenderWindow window;
        sf::SoundBuffer bufftik;
        sf::SoundBuffer bufftok;
        std::vector<sf::CircleShape> circls;
        std::vector<sf::CircleShape> tringls;
        sf::VertexArray playline;
        sf::VertexArray playlinev;
        sf::Vector2f start, end;
        sf::RectangleShape line;
        sf::VideoMode vm;
        Field f;
        int step;
        bool playsh;
        bool gameover;
        int win;
    public:
        GamePvP(unsigned int _l, int count = 15) : window(sf::VideoMode(_l, _l), "Tik-tok"), vm(_l,_l), f(count), 
                                                    playline(sf::Lines, (count + 1) * 2), playlinev(sf::Lines, (count + 1) * 2), 
                                                    line(sf::Vector2f(0.f,0.f)) {
            step = _l / (count + 2);
            playsh = false;
            gameover = false;
            win = 0;

            for(int i = 0; i < count + 1; i++){
                playline[2*i].position = sf::Vector2f(step, step + i*step);
                playline[2*i].color = sf::Color::Black;
                playline[2*i + 1].position = sf::Vector2f(_l - step, step + i * step);
                playline[2*i + 1].color = sf::Color::Black;
            }

            for(int i = 0; i < count + 1; i++){
                playlinev[2*i].position = sf::Vector2f(step + i*step, step);
                playlinev[2*i].color = sf::Color::Black;
                playlinev[2*i + 1].position = sf::Vector2f(step+ i *step, _l - step);
                playlinev[2*i + 1].color = sf::Color::Black;
            }

            line.setFillColor(sf::Color::Red);
        }
        int Init(){
            if (!bufftik.loadFromFile("sound/tik.wav")){
                std::cerr << "ERROR LOAD SOUND TIK" << std::endl;
                return -1;
            }
            
            if (!bufftok.loadFromFile("sound/tok.wav")){
                std::cerr << "ERROR LOAD SOUND TOK" << std::endl;
                return -1;
            }
            return 0;
        }

        void start1(){
            sf::Sound tik;
            tik.setBuffer(bufftik);

            sf::Sound tok;
            tok.setBuffer(bufftok);

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    switch(event.type) {
                        case sf::Event::Closed:{
                            window.close();
                            break;
                        }
                        case sf::Event::MouseButtonPressed:{
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            if(x < step || x > vm.width - step){
                                break;
                            }
                            if(y < step || y > vm.height - step){
                                break;
                            }
                            if(playsh && f.Get(x/step - 1, y/step - 1) == ' ' && !gameover){
                                f.Set(x/step - 1, y/step - 1, 'O');
                                sf::CircleShape  answ(step/2.f - 4.f) ;
                                answ.setFillColor(sf::Color(100, 250, 50));
                                answ.setPosition((x/step)*step + 3, (y/step)*step + 3);
                                circls.push_back(answ);
                                playsh = false;
                                tik.play();
                                win = checkwin(f, start, end);
                                if(win){
                                    gameover = true;
                                    /*std::cout << start.x << " " << start.y << " START\n";
                                    std::cout << end.x << " " << end.y << " END\n";*/

                                    if(start.y == end.y){
                                        line.setSize(sf::Vector2f(step*5, 5.f));
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x + 1) * step  : (end.x + 1) * step ), (start.y + 1) * step + step/2.f));
                                    }
                                    else if(start.x == end.x){
                                        line.setSize(sf::Vector2f( 5.f, step*5));
                                        line.setPosition(sf::Vector2f((start.x + 1)* step + step/2.f,(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    } else if ((start.y > end.y && (start.x < end.x)) || (start.y < end.y && start.x > end.x)) {
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(135.f);
                                        line.setPosition(sf::Vector2f( (end.x + 2) * step,(end.y+1)* step));
                                    } else{
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(45.f);
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x+1)* step : (end.x+1)* step),(start.y < end.y ? (start.y+1)* step : (end.y+1)* step)));
                                    }
                                }
                            }else if(!playsh && f.Get(x/step - 1, y/step - 1 ) == ' ' && !gameover){
                                f.Set(x/step - 1, y/step - 1, 'X');
                                sf::CircleShape  answ(step/2.f, 3);
                                answ.setFillColor(sf::Color(0, 100, 50));
                                answ.setPosition((x/step)*step , (y/step)*step + 5);
                                tringls.push_back(answ);
                                playsh = true;
                                tok.play();
                                win = checkwin(f, start, end);
                                if(win) {
                                    gameover = true;
                                    /*std::cout << start.x << " " << start.y << " START\n";
                                    std::cout << end.x << " " << end.y << " END\n";*/
                                    if(start.y == end.y){
                                        line.setSize(sf::Vector2f(step*5, 5.f));
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x + 1) * step : (end.x + 1) * step ), (start.y + 1) * step + step/2.f));
                                    }
                                    else if(start.x == end.x){
                                        line.setSize(sf::Vector2f( 5.f, step*5));
                                        line.setPosition(sf::Vector2f((start.x + 1)* step + step/2.f,(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    } else if ((start.y > end.y && (start.x < end.x)) || (start.y < end.y && start.x > end.x)) {
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(135.f);
                                        line.setPosition(sf::Vector2f((end.x + 2)* step, (end.y + 1)* step));
                                    } else{
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(45.f);
                                        line.setPosition(sf::Vector2f((start.x < end.x ?(start.x + 1)* step : (end.x + 1)* step),(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    }
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
                
                window.clear(sf::Color(255,252,200,255));
                for(int i = 0; i < circls.size(); i++){
                    window.draw(circls[i]);
                }
                for(int i = 0; i < tringls.size(); i++){
                    window.draw(tringls[i]);
                }
                if(win != 0){
                    window.draw(line);
                }
                window.draw(playline);
                window.draw(playlinev);
                window.display();
            }
        }


};


class GameAI {
    private:
        sf::RenderWindow window;
        sf::SoundBuffer bufftik;
        sf::SoundBuffer bufftok;
        std::vector<sf::CircleShape> circls;
        std::vector<sf::CircleShape> tringls;
        sf::VertexArray playline;
        sf::VertexArray playlinev;
        sf::Vector2f start, end;
        sf::RectangleShape line;
        sf::VideoMode vm;
        Field f;
        int step;
        bool playsh;
        bool gameover;
        int win;
        AI aiplayer;
    public:
        GameAI(unsigned int _l, int count = 15) : window(sf::VideoMode(_l, _l), "Tik-tok"), vm(_l,_l), f(count), 
                                                    playline(sf::Lines, (count + 1) * 2), playlinev(sf::Lines, (count + 1) * 2), 
                                                    line(sf::Vector2f(0.f,0.f)) {
            step = _l / (count + 2);
            playsh = true;
            gameover = false;
            win = 0;

            for(int i = 0; i < count + 1; i++){
                playline[2*i].position = sf::Vector2f(step, step + i*step);
                playline[2*i].color = sf::Color::Black;
                playline[2*i + 1].position = sf::Vector2f(_l - step, step + i * step);
                playline[2*i + 1].color = sf::Color::Black;
            }

            for(int i = 0; i < count + 1; i++){
                playlinev[2*i].position = sf::Vector2f(step + i*step, step);
                playlinev[2*i].color = sf::Color::Black;
                playlinev[2*i + 1].position = sf::Vector2f(step+ i *step, _l - step);
                playlinev[2*i + 1].color = sf::Color::Black;
            }

            line.setFillColor(sf::Color::Red);
        }
        int Init(){
            if (!bufftik.loadFromFile("sound/tik.wav")){
                std::cerr << "ERROR LOAD SOUND TIK" << std::endl;
                return -1;
            }
            
            if (!bufftok.loadFromFile("sound/tok.wav")){
                std::cerr << "ERROR LOAD SOUND TOK" << std::endl;
                return -1;
            }
            return 0;
        }

        void start1(){
            sf::Sound tik;
            tik.setBuffer(bufftik);

            sf::Sound tok;
            tok.setBuffer(bufftok);

            while (window.isOpen())
            {

                sf::Event event;
                while (window.pollEvent(event))
                {
                    switch(event.type) {
                        case sf::Event::Closed:{
                            window.close();
                            break;
                        }
                        case sf::Event::MouseButtonPressed:{
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            if(x < step || x > vm.width - step){
                                break;
                            }
                            if(y < step || y > vm.height - step){
                                break;
                            }
                            if(playsh && f.Get(x/step - 1, y/step - 1) == ' ' && !gameover){
                                f.Set(x/step - 1, y/step - 1, 'O');
                                sf::CircleShape  answ(step/2.f - 4.f) ;
                                answ.setFillColor(sf::Color(100, 250, 50));
                                answ.setPosition((x/step)*step + 3, (y/step)*step + 3);
                                circls.push_back(answ);
                                playsh = false;
                                //tik.play();
                                win = checkwin(f, start, end);
                                if(win){
                                    gameover = true;
                                    /*std::cout << start.x << " " << start.y << " START\n";
                                    std::cout << end.x << " " << end.y << " END\n";*/

                                    if(start.y == end.y){
                                        line.setSize(sf::Vector2f(step*5, 5.f));
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x + 1) * step  : (end.x + 1) * step ), (start.y + 1) * step + step/2.f));
                                    }
                                    else if(start.x == end.x){
                                        line.setSize(sf::Vector2f( 5.f, step*5));
                                        line.setPosition(sf::Vector2f((start.x + 1)* step + step/2.f,(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    } else if ((start.y > end.y && (start.x < end.x)) || (start.y < end.y && start.x > end.x)) {
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(135.f);
                                        line.setPosition(sf::Vector2f( (end.x + 2) * step,(end.y+1)* step));
                                    } else{
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(45.f);
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x+1)* step : (end.x+1)* step),(start.y < end.y ? (start.y+1)* step : (end.y+1)* step)));
                                    }
                                }
                            }
                            if(!playsh && !gameover){
                                int px = 0, py = 0;
                                aiplayer.GetChose(f, px , py);
                                f.Set(px, py, 'X');
                                sf::CircleShape  answ(step/2.f, 3);
                                answ.setFillColor(sf::Color(0, 100, 50));
                                answ.setPosition((px + 1)*step , (py + 1)*step + 5);
                                tringls.push_back(answ);
                                playsh = true;
                                //tok.play();
                                win = checkwin(f, start, end);
                                if(win) {
                                    gameover = true;
                                    /*std::cout << start.x << " " << start.y << " START\n";
                                    std::cout << end.x << " " << end.y << " END\n";*/
                                    if(start.y == end.y){
                                        line.setSize(sf::Vector2f(step*5, 5.f));
                                        line.setPosition(sf::Vector2f((start.x < end.x ? (start.x + 1) * step : (end.x + 1) * step ), (start.y + 1) * step + step/2.f));
                                    }
                                    else if(start.x == end.x){
                                        line.setSize(sf::Vector2f( 5.f, step*5));
                                        line.setPosition(sf::Vector2f((start.x + 1)* step + step/2.f,(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    } else if ((start.y > end.y && (start.x < end.x)) || (start.y < end.y && start.x > end.x)) {
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(135.f);
                                        line.setPosition(sf::Vector2f((end.x + 2)* step, (end.y + 1)* step));
                                    } else{
                                        line.setSize(sf::Vector2f(step*5*1.4142f, 5.f));
                                        line.rotate(45.f);
                                        line.setPosition(sf::Vector2f((start.x < end.x ?(start.x + 1)* step : (end.x + 1)* step),(start.y < end.y ? (start.y + 1)* step : (end.y + 1)* step)));
                                    }
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
                
                window.clear(sf::Color(255,252,200,255));
                for(int i = 0; i < circls.size(); i++){
                    window.draw(circls[i]);
                }
                for(int i = 0; i < tringls.size(); i++){
                    window.draw(tringls[i]);
                }
                if(win != 0){
                    window.draw(line);
                }
                window.draw(playline);
                window.draw(playlinev);
                window.display();
            }
        }


};


#endif