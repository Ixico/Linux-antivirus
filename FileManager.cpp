#include "FileManager.h"
#include "iostream"
#include <fstream>
#include <sstream>
#include <filesystem>
using std::string;
using std::filesystem::recursive_directory_iterator;
using std::vector;
const int DIGEST_LENGTH = 32;

string readFileToString(string file_path){
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
vector<string> findFilesInDirectory(string directory_path){
    vector<string> files;
    for (const auto& dirEntry : recursive_directory_iterator(directory_path))
        if (dirEntry.is_regular_file()) files.push_back(dirEntry.path());
    return files;
}

