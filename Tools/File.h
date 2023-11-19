//
// Created by Rob on 9/9/2023.
//

#ifndef CSC1061CAPSTONET_FILE_H
#define CSC1061CAPSTONET_FILE_H

#include <vector>
#include <string>
#include <iostream>
#include "SaveState.h"


class File {
public:
    File(std::string fileName);
    void Append(const std::string& contents);
    void Append(const std::vector<std::string> contents);
    void Silence(bool silence);

    bool WriteSaveFile(SaveState data);
    SaveState ReadSaveFile();

private:
    std::string fileName;
    bool silenceOutput;
};


#endif //CSC1061CAPSTONE_FILE_H
