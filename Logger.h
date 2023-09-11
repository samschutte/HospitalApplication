//
// Created by schut on 4/20/2023.
//

#ifndef HOSPITALAPP_LOGGER_H
#define HOSPITALAPP_LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Logger {
public:
    static Logger& getInstance();
    void log(const string& output);
    void setDebugMode(bool in);
    bool getDebugMode();
    ~Logger();
private:
    Logger();
    static bool debugMode;
    ofstream file;
};

extern Logger &logger;


#endif //HOSPITALAPP_LOGGER_H
