#ifndef CONVEX_HULL_SHADER_H
#define CONVEX_HULL_SHADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<GL/glew.h>

class ConvexHullShader {
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    unsigned int programID;

    void CompileVertexShader(const std::string& vertexShaderCode) {
        int success;
        char infoLog[512];

        auto vertexShaderCodeCStr = vertexShaderCode.c_str();

        vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexShaderCodeCStr, NULL);
        glCompileShader(vertexShaderID);
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            throw std::runtime_error("Error: Vertex shader compilation failed\n" + std::string(infoLog));
        }
    }

    void CompileFragmentShader(const std::string& fragmentShaderCode) {
        int success;
        char infoLog[512];

        auto fragmentShaderCodeCStr = fragmentShaderCode.c_str();
        fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &fragmentShaderCodeCStr, NULL);
        glCompileShader(fragmentShaderID);
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
            throw std::runtime_error("Error: Fragment shader compilation failed\n" + std::string(infoLog));
        }
    }

    void LinkShaderProgram() {
        int success;
        char infoLog[512];

        programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(programID, 512, nullptr, infoLog);
            throw std::runtime_error("Error: Shader program linking failed\n" + std::string(infoLog));
        }
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
public:
    ConvexHullShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath): vertexShaderID(0), fragmentShaderID(0), programID(0) {
        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        std::stringstream vertexShaderStream, fragmentShaderStream;

        //Sets the fstream related exceptions to be thrown
        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            //Open the shader files
            vertexShaderFile.open(vertexShaderPath);
            fragmentShaderFile.open(fragmentShaderPath);

            //Read the shader files
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();
        }
        catch(std::ifstream::failure e) {
            throw std::runtime_error("Error: Shader file could not be read\n"+std::string(e.what()));
        }

        auto vertexShaderCode = vertexShaderStream.str();
        
        auto fragmentShaderCode = fragmentShaderStream.str();
        CompileVertexShader(vertexShaderCode);
        CompileFragmentShader(fragmentShaderCode);
        LinkShaderProgram();
    }

    void Use() {
        glUseProgram(programID);
    }
    
};
#endif