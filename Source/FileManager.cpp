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

void saveQuarantineRecords(vector<QuarantineRecord> records){
    std::ofstream file;
    file.open(QUARANTINE_LIST_PATH);
    if (!file.is_open()) throw std::invalid_argument("File not found!");
    for (const auto &record : records){
        file << record.key << record.iv  <<  record.file_path << std::endl;
    }
    file.close();
}

//TODO: std::out_of_range exc
vector<QuarantineRecord> readQuarantineRecords(){
    std::ifstream file;
    file.open(QUARANTINE_LIST_PATH);
    if (!file.is_open()) throw std::invalid_argument("File not found listq");

    vector<QuarantineRecord> records;

    string line;
    int length = 16;
    for (int i=0; getline(file,line); i++){
        std::string key;
        std::string iv;
        std::string file_path;

        key = line.substr(0,length);
        iv = line.substr(length,length);
        file_path = line.substr(2*length, line.length()-2*length);

        records.push_back(QuarantineRecord(file_path,key,iv));
    }
    file.close();
    return records;
}

vector<path> findFilesInDirectory(path directory_path){
    vector<path> files;
    for (const auto& dirEntry : recursive_directory_iterator(directory_path))
        if (dirEntry.is_regular_file()) files.push_back(dirEntry.path());
    return files;
}