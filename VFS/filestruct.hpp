#ifndef FILESTRUCT_HPP
#define FILESTRUCT_HPP
#include <string>
#include <fstream>
class File{
private:
    std::string namefile;
    std::fstream file;
    std::string right;
public:
    File(std::string _namefile, std::string _right) : namefile(_namefile), right(_right), file(_namefile){}
    void rename(std::string _namefile){
        namefile = _namefile;
    }
    void reright(std::string _right){
        right = _right;
    }
};

#endif