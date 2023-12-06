//
// Created by Rob on 12/5/2023.
//

#ifndef CSC1061CAPSTONE_DEBUGMENU_H
#define CSC1061CAPSTONE_DEBUGMENU_H

#include <map>
#include <string>
#include <iostream>
#include <windows.h>

class debugMenu {
public:
    static void Register(std::string key);
    static void UpdateValue(std::string key, std::string value);
    static void DrawMenu();
private:
    static std::map<std::string, std::string> registry;
};


#endif //CSC1061CAPSTONE_DEBUGMENU_H
