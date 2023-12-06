//
// Created by Rob on 12/5/2023.
//

#include "debugMenu.h"

std::map<std::string, std::string> debugMenu::registry;

void debugMenu::Register(std::string key) {
    registry.insert({key, ""});
}

void debugMenu::UpdateValue(std::string key, std::string value) {
    registry[key] = std::move(value);
}

void debugMenu::DrawMenu() {

    std::map<std::string, std::string>::iterator _it;
    COORD coord;
    coord.X = 1;
    coord.Y = 1;

    for (_it = registry.begin(); _it != registry.end(); _it++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        std::cout << _it->first << ": " << _it->second;
        coord.Y++;
    }
}
