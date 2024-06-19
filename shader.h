#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath){
        std::ifstream vertexStream(vertexPath);
        if(vertexStream.is_open()){
            std::cout<<"file is open ready to reed"<<std::endl;

        }
        std::string line;
        std::string vertexCode="";
        while(std::getline(vertexStream,line)){
            vertexCode+=line;
        }
        std::cout<<vertexCode<<std::endl;

    }
    

};