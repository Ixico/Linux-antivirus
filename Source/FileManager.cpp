#include "../Headers/FileManager.h"
#include "iostream"
#include <fstream>
#include <filesystem>
#include "../Headers/ConfigurationVariables.h"
using std::string;
using std::filesystem::recursive_directory_iterator;
using std::vector;
const int DIGEST_LENGTH = 32;
using std::filesystem::path;


//TODO manage file types and symlinks
std::unordered_set <string> readDatabaseRecords(path file_path){
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) throw std::invalid_argument("File not found ex");
    string line;
    std::unordered_set<string> lines;
    for (int i=0; getline(file,line); i++){
        if(line.length() != DIGEST_LENGTH) continue; //omit incorrect records
        lines.insert(line);
    }
    file.close();
    return lines;
}

void saveQuarantinePaths(vector<std::filesystem::path> paths){
    std::ofstream file;
    file.open(QUARANTINE_LIST_PATH);
    if (!file.is_open()) throw std::invalid_argument("File not found!");
    for (const auto &path : paths){
        file << path << std::endl;
    }
    file.close();
}

//TODO: std::out_of_range exc
vector<std::filesystem::path> readQuarantinePaths(){
    std::ifstream file;
    file.open(QUARANTINE_LIST_PATH);
    if (!file.is_open()) throw std::invalid_argument("File not found listq");

    vector<std::filesystem::path> paths;

    string line;
    while(getline(file,line)){
        line.erase(std::remove(line.begin(),line.end(),'\"'),line.end());//remove quotation marks
        path p = line;
        paths.push_back(p);
    }
    file.close();
    return paths;
}

vector<path> findFilesInDirectory(path directory_path){
    vector<path> files;
    for (const auto& dirEntry : recursive_directory_iterator(directory_path))
        if (dirEntry.is_regular_file()) files.push_back(dirEntry.path());
    return files;
}