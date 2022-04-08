//
// Created by ixico on 23.03.2022.
//

#ifndef ANTIVIRUS_QUARANTINECONTROLLER_H
#define ANTIVIRUS_QUARANTINECONTROLLER_H

#include <iostream>

class QuarantineController {
public:
    explicit QuarantineController(std::string quarantine_path);
    void init();
    void imposeQuarantine(std::string file_path);
    void removeQuarantine(std::string);
private:
    std::string quarantine_path;
    const int AES_BLOCK_SIZE = 16;
    void useCipher();
    void moveFile(std::string file_name, std::string destination);
};


#endif //ANTIVIRUS_QUARANTINECONTROLLER_H
