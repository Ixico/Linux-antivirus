#include "FileManager.h"
#include "iostream"
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
using std::string;

const int DIGEST_LENGTH = 32;

string readFile(string file_path){
    std::ifstream file;
    //TODO: uwaga na cwd
    file.open(file_path, std::ios::in);
    if (!file.is_open()) throw std::invalid_argument("File not found");
    std::stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str(); //czy to czytanie z pliku jest ok?
    file.close(); //czy z bufferem tez sie cos robi?
    buffer.clear();
    return content;
}

std::unordered_set <string> readFileLines(string file_path){
    std::ifstream file;
    file.open(file_path,std::ios::in);
    if (!file.is_open()) throw std::invalid_argument("File not found");
    string line;
    std::unordered_set<string> lines;
    for (int i=0; getline(file,line); i++){
        if(line.length() != DIGEST_LENGTH) continue; //omit incorrect records
        lines.insert(line);
    }
    file.close();
    return lines;
}

