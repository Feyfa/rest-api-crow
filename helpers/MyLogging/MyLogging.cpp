#include "MyLogging.h"

std::string MyLogging::get_log_level(crow::LogLevel level)
{
    switch (level)
    {
        case crow::LogLevel::Info: return "INFO";
        case crow::LogLevel::Warning: return "WARNING";
        case crow::LogLevel::Error: return "ERROR";
        case crow::LogLevel::Debug: return "DEBUG";
        default: return "NONE";
    };
}

MyLogging::MyLogging()
{
    std::filesystem::create_directories(this->folder);
}

void MyLogging::log(std::string message, crow::LogLevel level)
{
    std::string log_type = this->get_log_level(level);
    this->file_output.open(std::format("{}/{}", this->folder, this->path), std::ios::app);
    if (file_output.is_open())
    {
        std::string time = MyDate::now();
        this->file_output << "(" << time << ") " << log_type << ": " << message << std::endl;
    }
    this->file_output.close();
}

MyLogging::~MyLogging()
{
    if (this->file_output.is_open())
    {
        this->file_output.close();
    }
};