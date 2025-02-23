#pragma once
#include <string>
#include <fstream>
#include "../../helpers/MyDate/MyDate.h"
#include <crow.h>

class MyLogging : public crow::ILogHandler
{
private:
    std::string folder = "logging";
    std::string path = "crow.log";
    std::ofstream file_output;

    // digunakan untuk mengambil type dari log
    std::string get_log_level(crow::LogLevel level);

public:
    MyLogging();
    virtual void log(std::string message, crow::LogLevel level); // override log dari class ILogHandler
    ~MyLogging();
};