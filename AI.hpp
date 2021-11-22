#ifndef AI_HPP
#define AI_HPP
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
            for(int p = 0; p < 6561; p++){
                int score = 0;
                std::string str = genStr(p, 8);
                str.insert(4 , 1, 'X');
                int k1 = str.find('O');
                int k2 = str.find('O', std::max(4, k1 + 1));
                if(k1 != std::string::npos && k2 != std::string::npos && k1 < 4  && (k2 - k1) <= 5){
                    score += 5; // first coeff
                }
                int OOOO = str.find("OOOO");
                if(OOOO != std::string::npos){
                    score += 50000;
                } else {
                    int OOO = str.find("OOO");
                    int OOO1 = str.find("OOO", 4);
                    if(OOO != std::string::npos){
                        if(OOO == 1 || OOO == 5){
                            score += 500; // second coeff
                        }else{ 
                            score += 100;
                        }
                    }
                }
                int k3 = str.find("XXXXX");
                if(k3 != std::string::npos){
                    score += 1000000;
                } else {
                    int k4 = str.find("XXXX");
                    if(k4 != std::string::npos){
                        if(k1 == std::string::npos || k2 == std::string::npos || k1 > 4 || (k2 - k1 > 5))
                            score += 10000;
                        else 
                            score += 1000;
                    } else {
                        int k5 = str.find("XXX");
                        if(k5 != std::string::npos){
                            if(k5 == 0 && k1 != std::string::npos && k1 != 3){
                                score += 5000;
                            }else if((k1 != std::string::npos && k2 != std::string::npos) && (k2 - k1) <= 5){
                                score += 5000;
                            }
                        }
                    }
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 6561; p++){
                int score = 0;
                std::string str = genStr(p, 8);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 2187; p++){
                int score = 0;
                std::string str = genStr(p, 8);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 2187; p++){
                int score = 0;
                std::string str = genStr(p, 7);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 729; p++){
                int score = 0;
                std::string str = genStr(p, 6);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 729; p++){
                int score = 0;
                std::string str = genStr(p, 6);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 243; p++){
                int score = 0;
                std::string str = genStr(p, 5);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 243; p++){
                int score = 0;
                std::string str = genStr(p, 5);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 81; p++){
                int score = 0;
                std::string str = genStr(p, 4);
                str.insert(4 , 1, 'X');
                int k1 = str.find('O');
                if(k1 != std::string::npos){
                    score += 1; // first coeff
                } else {
                    int XXXXX = str.find("XXXXX");
                    if(XXXXX != std::string::npos){
                        score += 100000;
                    }else {
                        int XXXX = str.find("XXXX");
                        if(XXXX != std::string::npos){
                            score += 10;
                        }else{
                            int XXX = str.find("XXX");
                            if(XXX != std::string::npos){
                                score += 5;
                            }else {
                                int XX = str.find("XX");
                                if(XX != std::string::npos){

                                }
                            }
                        }
                    }
                }
                int OOOO = str.find("OOOO");
                if(OOOO!=std::string::npos){
                    score += 100;
                } else {
                    int OOO = str.find("OOO");
                    if(OOO != std::string::npos){
                        score += 80;
                    }
                }
                

                tree_solve.addNode(str, score);
            }
            for(int p = 0; p < 81; p++){
                int score = 0;
                std::string str = genStr(p, 4);
                str.insert(4 , 1, 'O');
                int k1 = str.find('X');
                int k2 = str.find('X', k1 + 1);
                if(k1 < 4 && k2>4 && (k2 - k1) <= 5){
                    score += -1; // first coeff
                }
                int XXX = str.find("XXX");
                if(XXX + 1 == 4 || XXX - 1 == 4 ){
                    score += -20; // second coeff
                }

                tree_solve.addNode(str, score);
            }
            for(int p = 1; p < 81; p++){
                int score = 0;
                std::string str = genStr(p, 4);
                tree_solve.addNode(str, 0);
            }
            for(int p = 1; p < 27; p++){
                int score = 0;
                std::string str = genStr(p, 3);
                tree_solve.addNode(str, 0);
            }
            for(int p = 1; p < 9; p++){
                int score = 0;
                std::string str = genStr(p, 2);
                tree_solve.addNode(str, 0);
            }
            for(int p = 1; p < 3; p++){
                int score = 0;
                std::string str = genStr(p, 1);
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

        void GetChose(Field& f, int &x, int &y){
            int len = f.GetLen();
            /*std::vector<std::vector<int> > scores;
            for(int i = 0; i < len; i++){
                scores.push_back(std::vector<int> (len, 0));
            }*/
            int bestscore = - 1000000; // -max
            int depth = 2; // depth search
            for(int i = 0; i < len; i++){
                for(int j = 0; j < len; j++){
                    if(f.Get(i,j) == ' '){
                        f.Set(i,j, 'X');
                        int score = minmax(f, depth, false);
                        f.Set(i,j, ' ');
                        if(bestscore < score){
                            x = i;
                            y = j;
                            bestscore = score;
                        }
                    }
                }
            }

        }

        int minmax(Field& f, int depth, bool chosen){
            if(depth < 0){
                return 0;
            }
            int bestscore = 0;
            int len = f.GetLen();
            if(chosen){
                for(int i = 0; i < len; i++){
                    for(int j = 0; j < len; j++){
                        if(f.Get(i,j) == ' '){
                            f.Set(i,j, 'X');
                            int score = 0;
                            std::string ans1;
                            bool fullstring = true;
                            for(int p = 0; p < 9; p++){
                                if((j - 4 + p) >= len || (i - 4 + p) >= len){
                                    continue;
                                }
                                if((i - 4 + p) < 0  || (j - 4 + p) < 0){
                                    fullstring = false;
                                    continue;
                                }
                                ans1.push_back(f.Get(i - 4 + p, j - 4 + p));
                            }
                            if(!fullstring){
                                std::reverse(ans1.begin(), ans1.end());
                            }
                            Node<int, std::string> * ans1node = tree_solve.foundNode(ans1);

                            if(ans1node != nullptr){
                                score += ans1node->value;
                            } else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans1 << std::endl;
                            }

                            std::string ans2;
                            fullstring = true;
                            for(int p = 0; p < 9; p++){
                                if((i - 4 + p) >= len){
                                    continue;
                                }
                                if((i - 4 + p) < 0){
                                    fullstring = false;
                                    continue;
                                }
                                ans2.push_back(f.Get(i - 4 + p, j));
                            }
                            if(!fullstring){
                                std::reverse(ans2.begin(), ans2.end());
                            }

                            Node<int, std::string> * ans2node = tree_solve.foundNode(ans2);
                            if(ans2node != nullptr)
                                score += ans2node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans2 << std::endl;
                            }

                            std::string ans3;
                            fullstring = true;
                            for(int p = 0; p < 9; p++){
                                if((j - 4 + p) >= len){
                                    continue;
                                }
                                if((j - 4 + p) < 0 ){
                                    fullstring = false;
                                    continue;
                                }
                                ans3.push_back(f.Get(i, j  - 4 + p));
                            }
                            
                            if(!fullstring){
                                std::reverse(ans3.begin(), ans3.end());
                            }

                            Node<int, std::string> * ans3node = tree_solve.foundNode(ans3);
                            if(ans3node != nullptr)
                                score += ans3node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans3 << std::endl;
                            }

                            std::string ans4;
                            fullstring = true;
                            for(int p = 0; p < 9; p++){
                                if((i - 4 + p) >= len || (j + 4 - p) < 0 ){
                                    continue;
                                }
                                if((i - 4 + p) < 0 || (j + 4 - p) >= len){
                                    fullstring = false;
                                    continue;
                                }
                                ans4.push_back(f.Get(i - 4 + p, j  + 4 - p));
                            }
                            
                            if(!fullstring){
                                std::reverse(ans4.begin(), ans4.end());
                            }

                            Node<int, std::string> * ans4node = tree_solve.foundNode(ans4);
                            if(ans4node != nullptr)
                                score += ans4node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans4 << std::endl;
                            }

                            score += minmax(f, depth - 1, false);
                            f.Set(i,j, ' ');
                            if(bestscore < score){
                                bestscore = score;
                            }
                        }
                    }
                }
            } else {
                for(int i = 0; i < len; i++){
                    for(int j = 0; j < len; j++){
                        if(f.Get(i,j) == ' '){
                            f.Set(i,j, 'O');
                            int score = 0;
                            std::string ans1;
                            for(int p = 0; p < 9; p++){
                                if((i - 4 + p) < 0  || (j - 4 + p) < 0 || (j - 4 + p) >= len || (i - 4 + p) >= len){
                                    continue;
                                }
                                ans1.push_back(f.Get(i - 4 + p, j - 4 + p));
                            }
                            Node<int, std::string> * ans1node = tree_solve.foundNode(ans1);
                            if(ans1node != nullptr)
                                score += ans1node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans1 << std::endl;
                            }

                            std::string ans2;

                            for(int p = 0; p < 9; p++){
                                if((i - 4 + p) < 0 || (i - 4 + p) >= len){
                                    continue;
                                }
                                ans2.push_back(f.Get(i - 4 + p, j));
                            }

                            Node<int, std::string> * ans2node = tree_solve.foundNode(ans2);
                            if(ans2node != nullptr)
                                score += ans2node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans2 << std::endl;
                            }

                            std::string ans3;
                            for(int p = 0; p < 9; p++){
                                if((j - 4 + p) < 0 || (j - 4 + p) >= len){
                                    continue;
                                }
                                ans3.push_back(f.Get(i, j  - 4 + p));
                            }
                            
                            Node<int, std::string> * ans3node = tree_solve.foundNode(ans3);
                            if(ans3node != nullptr)
                                score += ans3node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans3 << std::endl;
                            }

                            std::string ans4;
                            for(int p = 0; p < 9; p++){
                                if((j + 4 - p) < 0 || (j + 4 - p) >= len || (i - 4 + p) < 0 || (i - 4 + p) >= len){
                                    continue;
                                }
                                ans4.push_back(f.Get(i - 4 + p, j  + 4 - p));
                            }

                            Node<int, std::string> * ans4node = tree_solve.foundNode(ans4);
                            if(ans4node != nullptr)
                                score += ans4node->value;
                            else{
                                std::cerr << "Not found situation" << std::endl;
                                std::cerr << ans4 << std::endl;
                            }

                            score += minmax(f, depth - 1, true);
                            f.Set(i,j, ' ');
                            if(bestscore > score){
                                bestscore = score;
                            }
                        }
                    }
                }
            }

            return bestscore;
        }


};

#endif