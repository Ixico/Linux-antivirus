#include "../Headers/FileManager.h"
#include "iostream"
#include <fstream>
#include <filesystem>
#include "../Headers/ConfigurationVariables.h"
#include <sys/statfs.h>
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
        file << record.file_path << ' ' << record.digest << std::endl;
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
    QuarantineRecord temp;
    while (file >> temp.file_path >> temp.digest) {
        records.push_back(temp);
    }
    file.close();
    return records;
}

//todo check filesystem and follow symlinks and skip permission denied
vector<path> findFilesInDirectory(path directory_path){
    vector<path> files;
    for (const auto& dirEntry : recursive_directory_iterator(directory_path))
        if (dirEntry.is_regular_file()) files.push_back(dirEntry.path());
    return files;
}

path followSymlinks(path file_name){
    path target;
    target = file_name;
    while (std::filesystem::is_symlink(target)){
        target = std::filesystem::read_symlink(target);
    }
    return target;
}

bool inRightFilesystem(path file_path){
    struct statfs buf;

    if (statfs(file_path.string().c_str(),&buf) == -1) throw std::invalid_argument("Cannot check file's filesystem!");
    return buf.f_type == 61267;
}
