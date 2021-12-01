#ifndef AI_HPP
#define AI_HPP
#include <omp.h>
#include "game.hpp"
#include <string>
#include "tree.hpp"
#include <iostream>


class Field{
    public:
        Field(int _size) : data() {
            for(int i = 0; i < _size; i++){
                data.push_back(std::vector <char> (_size, ' '));
            }
        }

        Field(const Field & _f) : data(_f.data) {}
        
        void resize(){
            for(int i = 0; i < data.size(); i++){
                data[i].push_back(' ');
                data[i].insert(data[i].begin(), ' ');
            }
            data.push_back(std::vector <char> (data[0].size(), ' '));
            data.insert(data.begin(), std::vector <char> (data[0].size(), ' ') );

        }
        void Set(int i, int j, char newch){
            data[i][j] = newch;
        }
        char Get(int i, int j){
            return data[i][j];
        }
        int GetLen(){
            return data.size();
        }
    private:
        std::vector<std::vector<char> > data;
};



class AI{
    private:
        Tree<int, std::string> tree_solve;
    public:
        AI(){
            TreeGeneration();
        }

        void TreeGeneration(){
            for(int p = 0; p < 3; p++){
                std::string str = genStr(p, 1);
                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 9; p++){
                std::string str = genStr(p, 2);
                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 27; p++){
                std::string str = genStr(p, 3);
                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 81; p++){
                std::string str = genStr(p, 4);
                tree_solve.addNode(str, 0);
            }

            for(int p = 1; p < 243; p++){
                int score = 0;
                std::string str = genStr(p, 5);
                if(str.find(' ') == std::string::npos){
                    if(str == "OOOOO"){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str == "XXXXX"){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }
                    tree_solve.addNode(str, 0);
                    continue;
                }
                if(str.find('O') != std::string::npos && str.find('X') != std::string::npos){
                    tree_solve.addNode(str, 0);
                    continue;
                }
                if(std::count(str.begin(),str.end(), 'O') == 4){
                    tree_solve.addNode(str, -5000);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'O') == 3){
                    tree_solve.addNode(str, -1000);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'O') == 2){
                    tree_solve.addNode(str, -500);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'O') == 1){
                    tree_solve.addNode(str, -5);
                    continue;
                }

                if(std::count(str.begin(),str.end(), 'X') == 4){
                    tree_solve.addNode(str, 5000);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'X') == 3){
                    tree_solve.addNode(str, 1000);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'X') == 2){
                    tree_solve.addNode(str, 500);
                    continue;
                } else if(std::count(str.begin(),str.end(), 'X') == 1){
                    tree_solve.addNode(str, 5);
                    continue;
                }
            }
            tree_solve.addNode("     ", 0);
            
            for(int p = 0; p < 729; p++){
                std::string str = genStr(p, 6);
                if(str.find(' ') == std::string::npos){
                    if(str.find("OOOOO") != std::string::npos){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str.find("XXXXX") != std::string::npos){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }
                    tree_solve.addNode(str, 0);
                    continue;
                }
                int countX = std::count(str.begin(), str.end(), 'X');
                int countO = std::count(str.begin(), str.end(), 'O');

                if( countX == 1 && str[0] != 'X' && str[5] != 'X' && countO > 0){
                    tree_solve.addNode(str, 0);
                    continue;
                } else if(countX == 1 && countO > 0 && str[0] == 'X' && str[5] != 'O'){
                    std::string strr = str.substr(1,5);
                    tree_solve.addNode(str, tree_solve.find(strr));
                    continue;
                } else if(countX == 1 && countO > 0 && str[5] == 'X' && str[0] != 'O'){
                    std::string strr = str.substr(1,5);
                    tree_solve.addNode(str, tree_solve.find(strr));
                    continue;
                }

                if( countO == 1 && str[0] != 'O' && str[5] != 'O' && countX > 0){
                    tree_solve.addNode(str, 0);
                    continue;
                } else if(countO == 1 && countX > 0 && str[0] == 'O' && str[5] != 'X'){
                    std::string strr = str.substr(1,5);
                    tree_solve.addNode(str, tree_solve.find(strr));
                    continue;
                } else if(countO == 1 && countX > 0 && str[5] == 'O' && str[0] != 'X'){
                    std::string strr = str.substr(1,5);
                    tree_solve.addNode(str, tree_solve.find(strr));
                    continue;
                }

                if(countX > 1 && countO > 1){
                    tree_solve.addNode(str, 0);
                    continue;
                }

                if(countX == 0){
                    std::string strl = str.substr(0,5);
                    std::string strr = str.substr(1,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::min<int>(scoreL, scoreR));
                    continue;
                }
                if(countO == 0){
                    std::string strl = str.substr(0,5);
                    std::string strr = str.substr(1,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::max<int>(scoreL, scoreR));
                    continue;
                }
                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 2187; p++){
                std::string str = genStr(p, 7);
                if(str.find(' ') == std::string::npos){
                    if(str.find("OOOOO") != std::string::npos){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str.find("XXXXX") != std::string::npos){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }
                    tree_solve.addNode(str, 0);
                    continue;
                }
                int countX = std::count(str.begin(), str.end(), 'X');
                int countO = std::count(str.begin(), str.end(), 'O');

                if(countX == 0){
                    std::string strl = str.substr(0,5);
                    std::string strm = str.substr(1,5);
                    std::string strr = str.substr(2,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    int scoreM = tree_solve.find(strm);
                    tree_solve.addNode(str, std::min<int>(scoreL, std::min<int>(scoreR, scoreM)));
                    continue;
                }

                if(countO == 0){
                    std::string strl = str.substr(0,5);
                    std::string strm = str.substr(1,5);
                    std::string strr = str.substr(2,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    int scoreM = tree_solve.find(strm);
                    tree_solve.addNode(str, std::max<int>(scoreL, std::max<int>(scoreR, scoreM)));
                    continue;
                }
                if(countO >= 3 && countX >=2){
                    tree_solve.addNode(str, 0);
                    continue;
                }
                if(countX >= 3 && countO >=2){
                    tree_solve.addNode(str, 0);
                    continue;
                }

                if(countX == 1 && str[0] == 'X'){
                    std::string strl = str.substr(1,5);
                    std::string strr = str.substr(2,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::min<int>(scoreL, scoreR));
                    continue;
                } else if(countX == 1 && str[6] == 'X'){
                    std::string strl = str.substr(0,5);
                    std::string strr = str.substr(1,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::min<int>(scoreL, scoreR));
                    continue;
                } else if( (countX == 1  || countX == 2 && str[1] == str[0] && !(str[5] == str[6] && str[5] == 'O') )&& str[1] == 'X'){
                    std::string strr = str.substr(2,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if((countX == 1  || countX == 2 && str[5] == str[6] && !(str[0] == str[1] && str[0] == 'O'))&& str[5] == 'X'){
                    std::string strr = str.substr(0,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if(countX == 2 && str[0] == str[6] && str[0] == 'X'){
                    std::string strr = str.substr(1,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if(countX == 1){
                    tree_solve.addNode(str, 0);
                    continue;
                }

                if(countO == 1 && str[0] == 'O'){
                    std::string strl = str.substr(1,5);
                    std::string strr = str.substr(2,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::max<int>(scoreL, scoreR));
                    continue;
                } else if(countO == 1 && str[6] == 'O'){
                    std::string strl = str.substr(0,5);
                    std::string strr = str.substr(1,5);
                    int scoreL = tree_solve.find(strl);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, std::max<int>(scoreL, scoreR));
                    continue;
                } else if((countO == 1 || countO == 2 && str[1] == str[0] && !(str[5] == str[6] && str[5] == 'X'))&& str[1] == 'O'){
                    std::string strr = str.substr(2,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if((countO == 1 || countO == 2 && str[5] == str[6] && !(str[0] == str[1] && str[0] == 'X'))&& str[5] == 'O'){
                    std::string strr = str.substr(0,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if(countO == 2 && str[0] == str[6] && str[0] == 'O'){
                    std::string strr = str.substr(1,5);
                    int scoreR = tree_solve.find(strr);
                    tree_solve.addNode(str, scoreR);
                    continue;
                }else if(countO == 1){
                    tree_solve.addNode(str, 0);
                    continue;
                }


                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 6561; p++){
                std::string str = genStr(p, 8);
                if(str.find(' ') == std::string::npos){
                    if(str.find("OOOOO") != std::string::npos){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str.find("XXXXX") != std::string::npos){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }
                    tree_solve.addNode(str, 0);
                    continue;
                }
                if(str == "XXX  OOO"){
                    tree_solve.addNode(str, 0);
                }
                int scoreX = -100000;
                int scoreY =  100000;
                for(int p = 0; p < 4; p++){
                    std::string strn = str.substr(p, 5);
                    int countX = std::count(strn.begin(),strn.end(), 'X');
                    int countO = std::count(strn.begin(),strn.end(), 'O');
                    if(countX > 0 && countO > 0){
                        continue;
                    }
                    if(countX > 0 && countO == 0){
                        int score = tree_solve.find(strn);
                        if(score > scoreX){
                            scoreX = score;
                        }
                    }
                    if(countO > 0 && countX == 0){
                        int score = tree_solve.find(strn);
                        if(score < scoreY){
                            scoreY = score;
                        }
                    }
                }
                if(scoreY == 100000 || scoreX > -scoreY){
                    tree_solve.addNode(str, scoreX);
                    continue;
                }
                if(scoreX == -100000 || scoreX < -scoreY){
                    tree_solve.addNode(str, scoreY);
                    continue;
                }


                tree_solve.addNode(str, 0);
            }

            for(int p = 0; p < 6561; p++){
                std::string str = genStr(p, 8);
                str.insert(4 , 1, 'X');
                if(str.find(' ') == std::string::npos){
                    if(str.find("OOOOO") != std::string::npos){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str.find("XXXXX") != std::string::npos){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }

                    tree_solve.addNode(str, 0);
                    continue;
                }
                int scoreX = -100000;
                int scoreY =  100000;
                for(int p = 0; p < 5; p++){
                    std::string strn = str.substr(p, 5);
                    int countX = std::count(strn.begin(),strn.end(), 'X');
                    int countO = std::count(strn.begin(),strn.end(), 'O');
                    if(countX > 0 && countO > 0){
                        continue;
                    }
                    if(countX > 0 && countO == 0){
                        int score = tree_solve.find(strn);
                        if(score > scoreX){
                            scoreX = score;
                        }
                    }
                    if(countO > 0 && countX == 0){
                        int score = tree_solve.find(strn);
                        if(score < scoreY){
                            scoreY = score;
                        }
                    }
                }
                if(scoreY == 100000 || scoreX > -scoreY){
                    tree_solve.addNode(str, scoreX);
                    continue;
                }
                if(scoreX == -100000 || scoreX < -scoreY){
                    tree_solve.addNode(str, scoreY);
                    continue;
                }

                tree_solve.addNode(str, 0);
            }
            for(int p = 0; p < 6561; p++){
                std::string str = genStr(p, 8);
                str.insert(4 , 1, 'O');
                if(str.find(' ') == std::string::npos){
                    if(str.find("OOOOO") != std::string::npos){
                        tree_solve.addNode(str, -10000);
                        continue;
                    }
                    if(str.find("XXXXX") != std::string::npos){
                        tree_solve.addNode(str, 10000);
                        continue;
                    }
                    tree_solve.addNode(str, 0);
                    continue;
                }
                int scoreX = -100000;
                int scoreY =  100000;
                for(int p = 0; p < 5; p++){
                    std::string strn = str.substr(p, 5);
                    int countX = std::count(strn.begin(),strn.end(), 'X');
                    int countO = std::count(strn.begin(),strn.end(), 'O');
                    if(countX > 0 && countO > 0){
                        continue;
                    }
                    if(countX > 0 && countO == 0){
                        int score = tree_solve.find(strn);
                        if(score > scoreX){
                            scoreX = score;
                        }
                    }
                    if(countO > 0 && countX == 0){
                        int score = tree_solve.find(strn);
                        if(score < scoreY){
                            scoreY = score;
                        }
                    }
                }
                if(scoreY == 100000 || scoreX > -scoreY){
                    tree_solve.addNode(str, scoreX);
                    continue;
                }
                if(scoreX == -100000 || scoreX < -scoreY){
                    tree_solve.addNode(str, scoreY);
                    continue;
                }
                tree_solve.addNode(str, 0);
            }
            
        }

        std::string genStr(int p, int k){
            std::string res;
            while(k > 0){
                int t = p%3;
                if(t == 0){
                    res.push_back(' ');
                }
                if(t == 1){
                    res.push_back('X');
                }
                if(t == 2){
                    res.push_back('O');
                }
                p/=3;
                k--;
            }
            return res;
        }

        void GetChose(Field& f, int &xt, int &yt, int px, int py){
            int len = f.GetLen();
            /*std::vector<std::vector<int> > scores;
            for(int i = 0; i < len; i++){
                scores.push_back(std::vector<int> (len, 0));
            }*/
            int bestscore = - 1000000; // -max
            int depth = 3; // depth search
            //std::vector<std::vector<bool> > boolfield(15, std::vector<bool> (15, false));
            std::vector<int> boolfield(15,0);
            #pragma omp parralel for
            for(int i = 0; i < len; i++){
                for(int j = 0; j < len; j++){
                    if(f.Get(i,j) == 'O' || f.Get(i,j) == 'X'){
                        for(int x = -2; x <= 2; x++){ // 4
                            for(int y = -2; y <= 2; y++){ // 4
                                if(i + x < 0 || i + x >= len  || j + y < 0 || j + y >= len){
                                    continue;
                                }
                                if(f.Get(i + x,j + y) != ' ' || boolfield[j + y] & (1 << (i + x))){
                                    continue;
                                }
                                boolfield[j + y] |= 1 << (i + x);
                                f.Set(i + x,j + y, 'X');
                                int score = 0;
                                //#pragma omp parallel
                                //#pragma omp shared(tree_solve)
                                {
                                    score = minmax(f, depth, false);
                                }
                                f.Set(i + x,j + y, ' ');
                                if(bestscore < score){
                                    xt = i + x;
                                    yt = j + y;
                                    bestscore = score;
                                }
                            }
                        }
                    }
                    
                }
            }

        }
        //#pragma omp parallel
        int minmax(Field& f, int depth, bool chosen){
            if(depth < 0){
                return 0;
            }
            int bestscore = 0;
            int len = f.GetLen();
            //std::vector<std::vector<bool> > boolfield(15, std::vector<bool> (15, false));
            std::vector<int> boolfield(15,0);
            if(chosen){
                #pragma omp parralel for
                for(int i = 0; i < len; i++){
                    for(int j = 0; j < len; j++){
                        if(f.Get(i,j) == 'X' || f.Get(i,j) == 'O'){
                            for(int x = -2; x <= 2; x++){
                                for(int y = -2; y <= 2; y++){
                                    if(i + x < 0 || i + x >= len || j + y < 0 || j + y >= len){
                                        continue;
                                    }

                                    if(f.Get(i + x, j + y) != ' ' || boolfield[j + y] & (1 << (i + x))){
                                        continue;
                                    }
                                    boolfield[j + y] |= 1<<(i + x);
                                    f.Set(i + x,j + y, 'X');
                                    int score = 100000;
                                    std::string ans1;
                                    for(int p = 0; p < 9; p++){
                                        if((j + y - 4 + p) >= len || (i + x - 4 + p) >= len){
                                            continue;
                                        }
                                        if((i + x - 4 + p) < 0  || (j + y - 4 + p) < 0){
                                            continue;
                                        }
                                        ans1.push_back(f.Get(i + x - 4 + p, j + y - 4 + p));
                                    }
                                    Node<int, std::string> * ans1node = tree_solve.foundNode(ans1);

                                    if(ans1node != nullptr){
                                        //score += ans1node->value;
                                        score = std::max<int>(score, ans1node->value);
                                    } else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans1 << "_Len:" << ans1.size() << std::endl;
                                    }

                                    std::string ans2;
                                    for(int p = 0; p < 9; p++){
                                        if((i + x - 4 + p) >= len){
                                            continue;
                                        }
                                        if((i + x - 4 + p) < 0){
                                            continue;
                                        }
                                        ans2.push_back(f.Get(i + x - 4 + p, j + y));
                                    }

                                    Node<int, std::string> * ans2node = tree_solve.foundNode(ans2);
                                    if(ans2node != nullptr)
                                        //score += ans2node->value;
                                        score = std::max<int>(score, ans2node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans2 << "_Len:" << ans2.size() << std::endl;
                                    }

                                    std::string ans3;
                                    for(int p = 0; p < 9; p++){
                                        if((j + y - 4 + p) >= len){
                                            continue;
                                        }
                                        if((j + y - 4 + p) < 0 ){
                                            continue;
                                        }
                                        ans3.push_back(f.Get(i + x, j + y  - 4 + p));
                                    }
                                    

                                    Node<int, std::string> * ans3node = tree_solve.foundNode(ans3);
                                    if(ans3node != nullptr)
                                        //score += ans3node->value;
                                        score = std::max<int>(score, ans3node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans3 << "_Len:" << ans3.size() << std::endl;
                                    }

                                    std::string ans4;
                                    for(int p = 0; p < 9; p++){
                                        if((i + x - 4 + p) >= len || (j + y + 4 - p) < 0 ){
                                            continue;
                                        }
                                        if((i + x - 4 + p) < 0 || (j + y + 4 - p) >= len){
                                            continue;
                                        }
                                        ans4.push_back(f.Get(i + x - 4 + p, j + y  + 4 - p));
                                    }
                                    

                                    Node<int, std::string> * ans4node = tree_solve.foundNode(ans4);
                                    if(ans4node != nullptr)
                                        //score += ans4node->value;
                                        score = std::max<int>(score, ans4node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans4 << "_Len:" << ans4.size() << std::endl;
                                    }

                                    score += minmax(f, depth - 1, false);
                                    //score = std::min<int>(score, minmax(f, depth - 1, false));
                                    f.Set(i + x,j + y, ' ');
                                    if(bestscore < score){
                                        bestscore = score;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                #pragma omp parralel for
                for(int i = 0; i < len; i++){
                    for(int j = 0; j < len; j++){
                         if(f.Get(i,j) == 'X' || f.Get(i,j) == 'O'){
                            for(int x = -2; x <= 2; x++){
                                for(int y = -2; y <= 2; y++){
                                    if(i + x < 0 || i + x >= len || j + y < 0 || j + y >= len){
                                        continue;
                                    }

                                    if(f.Get(i + x, j + y) != ' ' || boolfield[j + y] & 1 << (i + x)){
                                        continue;
                                    }

                                    boolfield[j + y] |= 1 << (i + x);
                                    f.Set(i + x,j + y, 'O');
                                    int score = -100000;
                                    std::string ans1;
                                    for(int p = 0; p < 9; p++){
                                        if((i + x - 4 + p) < 0  || (j + y - 4 + p) < 0 || (j + y - 4 + p) >= len || (i + x - 4 + p) >= len){
                                            continue;
                                        }
                                        ans1.push_back(f.Get(i + x - 4 + p, j + y - 4 + p));
                                    }
                                    Node<int, std::string> * ans1node = tree_solve.foundNode(ans1);
                                    if(ans1node != nullptr)
                                        //score += ans1node->value;
                                        score = std::min<int>(score, ans1node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans1 << "_Len:" << ans1.size() << std::endl;
                                    }

                                    std::string ans2;

                                    for(int p = 0; p < 9; p++){
                                        if((i + x - 4 + p) < 0 || (i + x - 4 + p) >= len){
                                            continue;
                                        }
                                        ans2.push_back(f.Get(i + x - 4 + p, j + y));
                                    }

                                    Node<int, std::string> * ans2node = tree_solve.foundNode(ans2);
                                    if(ans2node != nullptr)
                                        //score += ans2node->value;
                                        score = std::min<int>(score, ans1node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans2 << "_Len:" << ans2.size() << std::endl;
                                    }

                                    std::string ans3;
                                    for(int p = 0; p < 9; p++){
                                        if((j + y - 4 + p) < 0 || (j + y - 4 + p) >= len){
                                            continue;
                                        }
                                        ans3.push_back(f.Get(i + x, j + y  - 4 + p));
                                    }
                                    
                                    Node<int, std::string> * ans3node = tree_solve.foundNode(ans3);
                                    if(ans3node != nullptr)
                                        //score += ans3node->value;
                                        score = std::min<int>(score, ans1node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans3 << "_Len:" << ans3.size() << std::endl;
                                    }

                                    std::string ans4;
                                    for(int p = 0; p < 9; p++){
                                        if((j + y + 4 - p) < 0 || (j + y + 4 - p) >= len || (i + x - 4 + p) < 0 || (i + x - 4 + p) >= len){
                                            continue;
                                        }
                                        ans4.push_back(f.Get(i + x - 4 + p, j + y + 4 - p));
                                    }

                                    Node<int, std::string> * ans4node = tree_solve.foundNode(ans4);
                                    if(ans4node != nullptr)
                                        //score += ans4node->value;
                                        score = std::min<int>(score, ans1node->value);
                                    else{
                                        std::cerr << "Not found situation" << std::endl;
                                        std::cerr << ans4 << "_Len:" << ans4.size() << std::endl;
                                    }

                                    score += minmax(f, depth - 1, true);
                                    //score = std::max<int>(score, minmax(f, depth -1, true));
                                    f.Set(i + x,j + y, ' ');
                                    if(bestscore > score){
                                        bestscore = score;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return bestscore;
        }


};

#endif