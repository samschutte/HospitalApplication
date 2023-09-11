//
// Created by schut on 4/21/2023.
//
#include "Logger.h"

Logger::Logger() {};
Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
};
void Logger::log(const string& output){
    if(debugMode){
        cout << output << endl;
    }
    else {
        // put in file
        file.open("log.txt",ios_base::app);
        file << output << endl;
        file.close();
    }
};
void Logger::setDebugMode(bool in){
    debugMode = in;
};
bool Logger::getDebugMode(){
    return debugMode;
};
Logger::~Logger() {
    file.close();
}
bool Logger::debugMode = false;


Logger &logger = Logger::getInstance();
