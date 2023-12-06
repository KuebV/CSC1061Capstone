//
// Created by Rob on 8/28/2023.
//

#include <memory>
#include "Tag.h"
#include <string>
#include <sstream>

void Tag::CreateTagFile(const std::string &tagFileName, std::unordered_map<std::string, std::string> pairValue) {
    std::ofstream fStream;
    fStream.open(tagFileName);

    std::unordered_map<std::string, std::string>::iterator it;

    if (fStream.is_open()){
        for (it = pairValue.begin(); it != pairValue.end(); it++){
            std::string line = "<" + it->first + ">" + it->second + "</" + it->first + ">";
            fStream << line << '\n';
        }
    }
}

std::unordered_map<std::string, std::string> Tag::ReadTagFile(const std::string &tagFileName) {
    std::ifstream fStream(tagFileName);
    std::unique_ptr<std::string> line = std::make_unique<std::string>();
    std::unordered_map<std::string, std::string> keyPair;

    while (std::getline(fStream, *line)){
        std::string tag = getTag(*line);
        std::string value = getValue(*line, tag);
        keyPair.insert({tag, value});
    }

    return keyPair;
}

std::string Tag::getTag(const std::string &line) {
    size_t getStartingBracket = line.find('<');
    size_t getEndingBracket = line.find('>');
    return line.substr(getStartingBracket + 1, (getEndingBracket - getStartingBracket) - 1);
}

std::string Tag::getValue(const std::string &line, const std::string &tag) {
    std::unique_ptr<std::string> ptrLine = std::make_unique<std::string>(line);
    std::string startingElement = "<" + tag  + ">";
    std::string endingElement = "</" + tag + ">";
    *ptrLine = line.substr((line.find(startingElement) + startingElement.length()), line.length() - (startingElement.length() + endingElement.length()));
    return *ptrLine;
}

bool Tag::KeyExists(std::unordered_map<std::string, std::string> map, std::string key) {
    if (map[key].empty())
        return false;
    return true;
}

bool Tag::TagFileExists(const std::string &tagFileName) {
    if (FILE *file = fopen(tagFileName.c_str(), "r")){
        fclose(file);
        return true;
    }
    return false;
}

int Tag::ToInteger(const std::string &str) {
    return std::stoi(str);
}

bool Tag::ToBoolean(const std::string &str){
    bool x;
    std::istringstream is(str);
    is >> std::boolalpha >> x;
    return x;

}

