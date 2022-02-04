#ifndef AI_HPP
#define AI_HPP
#include <omp.h>
#include "game.hpp"
#include <string>
#include "tree.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>
#include <random>

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

int checkwinb(Field& f, int i, int j){
    int len = f.GetLen();
    std::string str[4] = {"         ", "         ", "         ", "         "};
    std::string::size_type k1[4];
    std::string::size_type k2[4];
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
        return 1;
    }
    if(k1[1] != std::string::npos){
        return 1;
    }
    if(k1[2] != std::string::npos){
                
        return 1;
    }
    if(k1[3] != std::string::npos){
                
        return 1;
    }
    if(k2[0] != std::string::npos){
                
        return 2;
    }
    if(k2[1] != std::string::npos){
        
        return 2;
    }
    if(k2[2] != std::string::npos){
                
        return 2;
    }
    if(k2[3] != std::string::npos){
                
        return 2;
    }
    return 0;
}


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

class newAi{
    private:

        struct Move {
            int i;
            int j;
            int score;
        };

        int *** Table;
        Tree<int,int> cache;
        Tree< std::tuple<int,int,int>, int> gamecache;

        int CacheHits;
        int Cutoffs;
        int CacheCutoffs;
        int CachePuts;
        int StateCacheHits;
        int StateCachePuts;
        int MaximumDepth;
        int fc;
        const int WIN_DETECTED = std::numeric_limits<int>::min() + 1;

        Move bestmove;

        int hash(Field & f){
            int l = f.GetLen();
            int h = 0;
            for(int i = 0; i < l; i++){
                for(int j = 0; j < l; j++){
                    if(f.Get(i,j) == ' '){
                        continue;
                    }
                    if(f.Get(i,j) == 'X'){
                        h ^= Table[i][j][0];
                    }
                    if(f.Get(i,j) == 'O'){
                        h ^= Table[i][j][1];
                    }
                }
            }
            return h;
        }

        int update_hash(int h, bool player, int i, int j){
            int newh = h;
            if(player){
                newh ^= Table[i][j][0];
            }else{
                newh ^= Table[i][j][1];
            }
            return newh;
        }

        std::vector<Move> Generatechoses(std::array<int,4> const & restric, Field & f, bool player){
            std::vector<Move > scors;
            int len = f.GetLen();
            int xmin = restric[0];
            int ymin = restric[1];
            int xmax = restric[2];
            int ymax = restric[3];
            for(int i = std::max(xmin - 2, 0); i <= std::min(xmax + 2, len); i++){
                for(int j = std::max(ymin - 2, 0); j <= std::min(ymax + 2, len); j++){
                    if(f.Get(i,j) == ' ' && !remoteCell(f, i, j)){
                        Move move;
                        move.i = i;
                        move.j = j;
                        move.score = calcscore(f, i, j, player);
                        if (move.score == WIN_DETECTED) {
                            std::vector<Move> winning_move = { move };
                                return winning_move;
                            }
                        scors.push_back(move);
                    }
                }
            }
            std::sort(scors.begin(),scors.end(),[](Move a, Move b) {
                    return a.score > b.score;
                });
            return scors;
        }

        int calcscore(Field & f, int x, int y, bool player){
            int len = f.GetLen();
            int score = 0;
            int tempscore = 0;
            std::string ans1;
            for(int p = 0; p < 9; p++){
                if((y - 4 + p) >= len || (x - 4 + p) >= len){
                    continue;
                }
                if((x - 4 + p) < 0  || (y - 4 + p) < 0){
                    continue;
                }
                ans1.push_back(f.Get(x - 4 + p, y - 4 + p));
            }
            tempscore = calcstr(ans1, player);
            if(tempscore == WIN_DETECTED){
                return WIN_DETECTED;
            }else{
                score += tempscore;
            }

            std::string ans2;
            for(int p = 0; p < 9; p++){
                if((x - 4 + p) < 0  || (x - 4 + p) >= len){
                    continue;
                }
                ans2.push_back(f.Get(x - 4 + p, y));
            }
            tempscore = calcstr(ans2, player);
            if(tempscore == WIN_DETECTED){
                return WIN_DETECTED;
            }else{
                score += tempscore;
            }

            std::string ans3;
            for(int p = 0; p < 9; p++){
                if((y - 4 + p) >= len || (y - 4 + p) < 0){
                    continue;
                }
                ans3.push_back(f.Get(x, y - 4 + p));
            }
            tempscore = calcstr(ans3, player);
            if(tempscore == WIN_DETECTED){
                return WIN_DETECTED;
            }else{
                score += tempscore;
            }

            std::string ans4;
            for(int p = 0; p < 9; p++){
                if((y + 4 - p) >= len || (x - 4 + p) >= len){
                    continue;
                }
                if((x - 4 + p) < 0  || (y + 4 - p) < 0){
                    continue;
                }
                ans4.push_back(f.Get(x - 4 + p, y + 4 - p));
            }
            tempscore = calcstr(ans4, player);
            if(tempscore == WIN_DETECTED){
                return WIN_DETECTED;
            }else{
                score += tempscore;
            }

            return score;
        }

        int calcstr(std::string str, bool player){
            int score = 0;
            for(int i = 0; (i + 4) < str.size(); ++i){
                int countX = 0;
                int countO = 0;
                for(int j = 0; j < 5; ++j){
                    if(str[i + j] == 'X'){
                        countX++;
                    }
                    if(str[i + j] == 'O'){
                        countO++;
                    }
                    
                }

                if(player){
                    score += evalff(getState(countX,countO));
                } else {
                    score += evalff(getState(countO,countX));
                }
                if(score >= 800000){
                    return WIN_DETECTED;
                }
            }
            return score;
        }


        int evalff(int seq) {
            switch (seq) {
                case 0:
                    return 7;
                case 1:
                    return 35;
                case 2:
                    return 800;
                case 3:
                    return 15000;
                case 4:
                    return 800000;
                case -1:
                    return 15;
                case -2:
                    return 400;
                case -3:
                    return 1800;
                case -4:
                    return 100000;
                case 17:
                    return 0;
            }
        }

        int evaluateblock(int blocks,int pieces) {
            if (blocks == 0) {
                switch (pieces) {
                    case 1:
                        return 10;
                    case 2:
                        return 100;
                    case 3:
                        return 1000;
                    case 4:
                        return 10000;
                    default:
                        return 100000;
                }
            } else if (blocks == 1) {
                switch (pieces) {
                    case 1:
                        return 1;
                    case 2:
                        return 10;
                    case 3:
                        return 100;
                    case 4:
                        return 1000;
                    default:
                        return 100000;
                }
            } else {
                if (pieces >= 5) {
                    return 100000;
                } else {
                    return 0;
                }
            }
        }

        int getState(int X, int O) {
            if (X + O == 0) {
                return 0;
            }
            if (X != 0 && O == 0) {
                return X;
            }
            if (X == 0 && O != 0) {
                return -O;
            }
            if (X != 0 && O != 0) {
                return 17;
            }
        }

        int eval_board(Field & f,char pieceType, std::array<int, 4> const & restric) {
            int len = f.GetLen();
            int score = 0;
            int xmin = restric[0];
            int ymin = restric[1];
            int xmax = restric[2];
            int ymax = restric[3];

            for (int i = xmin; i < xmax + 1; i++) {
                for (int j = ymin; j < ymax + 1; j++) {
                    if (f.Get(i,j) == pieceType) {
                        int block = 0;
                        int piece = 1;
                        // left
                        if (j == 0 || f.Get(i, j - 1) != ' ') {
                            block++;
                        }
                        // pieceNum
                        for (j++; j < len && f.Get(i,j) == pieceType; j++) {
                            piece++;
                        }
                        // right
                        if (j == len || f.Get(i,j) != ' ') {
                            block++;
                        }
                        score += evaluateblock(block, piece);
                    }
                }
            }

            for (int j = ymin; j < ymax + 1; j++) {
                for (int i = xmin; i < xmax + 1; i++) {
                    if (f.Get(i,j) == pieceType) {
                        int block = 0;
                        int piece = 1;
                        // left
                        if (i == 0 || f.Get(i - 1, j) != ' ') {
                            block++;
                        }
                        // pieceNum
                        for (i++; i < len && f.Get(i,j) == pieceType; i++) {
                            piece++;
                        }
                        // right
                        if (i == len || f.Get(i,j) != ' ') {
                            block++;
                        }
                        score += evaluateblock(block, piece);
                    }
                }
            }

            for (int n = xmin; n < (ymax -ymin + xmax); n += 1) {
                int r = n;
                int c = ymin;
                while (r >= xmin && c <= ymax) {
                    if (r <= xmax) {
                        if (f.Get(r,c) == pieceType) {
                            int block = 0;
                            int piece = 1;
                            // left
                            if (c == 0 || r == len - 1 ||f.Get(r + 1, c - 1) != ' ') {
                                block++;
                            }
                            // pieceNum
                            r--;
                            c++;
                            for (; r >= 0 && f.Get(r,c) == pieceType; r--) {
                                piece++;
                                c++;
                            }
                            // right
                            if (r < 0 || c == len || f.Get(r,c) != ' ') {
                                block++;
                            }
                            score += evaluateblock(block, piece);
                        }
                    }
                    r -= 1;
                    c += 1;
                }
            }

            for (int n = xmin - (ymax - ymin); n <= xmax; n++) {
                int r = n;
                int c = ymin;
                while (r <= xmax && c <= ymax) {
                    if (r >= xmin && r <= xmax) {
                        if (f.Get(r,c) == pieceType) {
                            int block = 0;
                            int piece = 1;
                            // left
                            if (c == 0 || r == 0 || f.Get(r - 1, c - 1) != ' ') {
                                block++;
                            }
                            // pieceNum
                            r++;
                            c++;
                            for (; r < len && f.Get(r, c) == pieceType; r++) {
                                piece++;
                                c++;
                            }
                            // right
                            if (r == len || c == len || f.Get(r,c) != ' ') {
                                block++;
                            }
                            score += evaluateblock(block, piece);
                        }
                    }
                    r += 1;
                    c += 1;
                }

            }
            return score;
        }

        std::array<int, 4> Get_restrictions(Field & f) {
            int len = f.GetLen();
            int xmin = 100;
            int ymin = 100;
            int xmax = -100;
            int ymax = -100;
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    if (f.Get(i,j) != ' ') {
                        xmin = std::min(xmin, i);
                        ymin = std::min(ymin, j);
                        xmax = std::max(xmax, i);
                        ymax = std::max(ymax, j);
                    }
                }
            }
            if (xmin - 2 < 0) {
                xmin = 2;
            }
            if (ymin - 2 < 0) {
                ymin = 2;
            }
            if (xmax + 2 >= len) {
                xmax = len - 3;
            }
            if (ymax + 2 >= len) {
                ymax = len - 3;
            }
            std::array<int, 4> restric = {xmin , ymin, xmax, ymax};
            return restric;
        }

        std::array<int, 4> Change_restrictions(Field & f,std::array<int, 4> const & restric ,int  i,int  j) {
            int len = f.GetLen();
            int xmin = restric[0];
            int ymin = restric[1];
            int xmax = restric[2];
            int ymax = restric[3];

            if (i < xmin) {
                xmin = i;
            } else if (i > xmax) {
                xmax = i;
            }
            if (j < ymin) {
                ymin = j;
            } else if (j > ymax) {
                ymax = j;
            }
            if (xmin - 2 < 0) {
                xmin = 2;
            }
            if (ymin - 2 < 0) {
                ymin = 2;
            }
            if (xmax + 2 >= len) {
                xmax = len - 3;
            }
            if (ymax + 2 >= len) {
                ymax = len - 3;
            }

            std::array<int, 4> new_restic = {xmin, ymin, xmax, ymax};
            return new_restic;
        }


        int evaluate_state(Field & f,bool player,int  hash, std::array<int,4> const & restric) {
            int black_score = eval_board(f, 'X', restric);
            int  white_score = eval_board(f, 'O', restric);
            int score = 0;
            if (player) {
                score = (black_score - white_score);
            } else {
                score = (white_score - black_score);
            }
            cache.addNode(hash, score);
            StateCachePuts++;
            return score;
        }


        int negamax(Field & f,bool player,int depth,int a,int b,int hash,std::array<int, 4> const & restric ,int last_i,int last_j) {
            int alphaOrig = a;
            int len = f.GetLen();
            Node<std::tuple<int,int,int>, int >* CacheNode = gamecache.foundNode(hash);  
            if ((CacheNode != nullptr) && (std::get<1>(CacheNode->value) >= depth)) {
                CacheHits++;
                int score = std::get<0>(CacheNode->value);
                if (std::get<2>(CacheNode->value) == 0) {
                    CacheCutoffs++;
                    return score;
                }
                if (std::get<2>(CacheNode->value) == -1) {
                    a = std::max(a, score);
                } else if (std::get<2>(CacheNode->value) == 1) {
                    b = std::min(b, score);
                }
                if (a >= b) {
                    CacheCutoffs++;
                    return score;
                }
            }
            fc++;
            if (checkwinb(f, last_i, last_j)) {
                return -2000000 + (MaximumDepth - depth);
            }
            if (depth == 0) {
                Node<int,int>* StateCacheNode = cache.foundNode(hash);
                if (StateCacheNode != nullptr) {
                    StateCacheHits++;
                    return StateCacheNode->value;
                }
                return evaluate_state(f, player, hash, restric);
            }

            std::vector<Move > availSpots = Generatechoses(restric, f, player);
            if (availSpots.size() == 0) {
                return 0;
            }

            int i, j;
            int newHash;
            int bestvalue = -100000000;
            int value;
            for (int y = 0; y < availSpots.size(); y++) {
                i = availSpots[y].i;
                j  = availSpots[y].j;
                newHash = update_hash(hash, player, i, j);
                if(player){
                    f.Set(i,j,'X');
                }else {
                    f.Set(i,j,'O');
                }
                std::array <int, 4> newrestric = Change_restrictions(f,restric, i, j);
                int value = -negamax(f, !player, depth - 1, -b, -a, newHash, newrestric, i, j);
                f.Set(i,j, ' ');
                if (value > bestvalue) {
                    bestvalue = value;
                    if (depth == MaximumDepth) {
                        bestmove = {i, j, value};
                        //debug
                        std::cout << "best move" << std::endl;
                        std::cout << bestmove.i << ' ' << bestmove.j << ' ' << bestmove.score << std::endl;
                    }
                }
                a = std::max(a, value);
                if (a >= b) {
                    break;
                }
            }
            CachePuts++;
            std::tuple<int,int,int> obj;
            //const obj={score: bestvalue,depth:depth};
            if (bestvalue <= alphaOrig) {
                obj = std::make_tuple(bestvalue, depth, 1);
            } else if (bestvalue >= b) {
                obj = std::make_tuple(bestvalue, depth, -1);
                //obj.Flag = -1
            } else {
                obj = std::make_tuple(bestvalue, depth, 0);
                //obj.Flag = 0
            }
            gamecache.addNode(hash,obj);
            return bestvalue;
        }


        bool remoteCell(Field & f, int r, int c) {
            int len = f.GetLen();
            for (int i = r - 2; i <= r + 2; i++) {
                if (i < 0 || i >= len) continue;
                for (int j = c - 2; j <= c + 2; j++) {
                    if (j < 0 || j >= len) continue;
                    if (f.Get(i,j) != ' ') return false;
                }
            }
            return true;
        }
        


    public:
        newAi(int size){
            std::mt19937 mt_rand(time(0));
            srand(time(nullptr));
            Table = new int **[size];
            for(int i = 0; i < size; i++){
                Table[i] = new int *[size];
                for(int j = 0; j < size; j++){
                    Table[i][j] = new int[2];
                    Table[i][j][0] = mt_rand();
                    Table[i][j][1] = mt_rand();
                }
            }
            
        }

        void iterative_negamax(bool player, Field & f,int depth, int &px, int &py) {
            bestmove.i = -1;
            bestmove.j = -1;
            bestmove.score = 0;
            int i = 2;
            int bestscore;
            while (i != depth + 2) {
                MaximumDepth = i;
                std::array<int, 4> restric = Get_restrictions(f);
                bestscore = negamax(f, player, MaximumDepth, std::numeric_limits<int>::min()+1, std::numeric_limits<int>::max()-1, hash(f),restric, 0, 0);
                i += 2;
            }
            px = bestmove.i;
            py = bestmove.j;
        }

        void search(Field & f,bool player,int depth,int & newbestx, int & newbesty) {
            MaximumDepth = depth;
            std::array<int, 4> restric = Get_restrictions(f);
            int bestMove = negamax(f, player, depth, -1000000, 1000000, hash(f), restric, 0, 0);
            newbestx = bestmove.i;
            newbesty = bestmove.j;
            std::cout << "LOG" << std::endl;
            std::cout << "CacheHits " << CacheHits << std::endl;
            std::cout << "CacheCutoffs " << CacheCutoffs << std::endl;
            std::cout <<"CachePuts " << CachePuts << std::endl;
            std::cout << "StateCacheHits " << StateCacheHits << std::endl;
            std::cout << "StateCachePuts " << StateCachePuts << std::endl;
            std::cout << "fc " << fc << std::endl;

}

};

#endif