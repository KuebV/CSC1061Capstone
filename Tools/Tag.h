//
// Created by Rob on 8/28/2023.
//

#ifndef WORLDGENERATIONTEST_TAG_H
#define WORLDGENERATIONTEST_TAG_H


#include <unordered_map>
#include <string>
#include <fstream>

class Tag {
public:
    static void CreateTagFile(const std::string& tagFileName, std::unordered_map<std::string, std::string> pairValue);
    static std::unordered_map<std::string, std::string> ReadTagFile(const std::string& tagFileName);
    static bool KeyExists(std::unordered_map<std::string, std::string> map, std::string key);
    static bool TagFileExists(const std::string& tagFileName);
private:
    static std::string getTag(const std::string& line);
    static std::string getValue(const std::string& line, const std::string& tag);
};


#endif //WORLDGENERATIONTEST_TAG_H
