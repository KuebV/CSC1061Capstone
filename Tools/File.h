//
// Created by Rob on 9/9/2023.
//

#ifndef WORLDGENERATIONTEST_FILE_H
#define WORLDGENERATIONTEST_FILE_H

#include <vector>
#include <string>


class File {
public:
    File(std::string fileName);
    void Append(const std::string& contents);
    void Append(const std::vector<std::string> contents);
private:
    std::string fileName;
};


#endif //WORLDGENERATIONTEST_FILE_H
