//
// Created by Rob on 9/9/2023.
//

#include <fstream>
#include "File.h"

File::File(std::string fileName) {
    this->fileName = fileName;
}

void File::Append(const std::string &contents) {
    std::ofstream ofstream;

    ofstream.open(fileName, std::ios_base::app);
    ofstream << contents;
    ofstream.close();
}

void File::Append(const std::vector<std::string> contents) {
    std::ofstream ofstream;

    ofstream.open(fileName, std::ios_base::app);
    for (int i = 0; i < contents.size(); i++){
        ofstream << contents[i];
    }
    ofstream.close();
}
