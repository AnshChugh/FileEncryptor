#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include <iostream>
#include <sstream>
#include "../fileHandling/IO.hpp"
enum class Action
{
    ENCRYPT,
    DECRYPT
};

struct Task
{
    std::string file_path;
    std::fstream f_stream;
    Action action;
    Task(std::fstream &&stream, Action act, std::string file_path) : f_stream(std::move(stream)), file_path(file_path), action(act) {};

    std::string toString()
    {
        std::ostringstream oss;

        oss << file_path << ",";
        if (action == Action::ENCRYPT)
        {
            oss << "ENCRYPT";
        }
        else
        {
            oss << "DECRYPT";
        }
        // test.txt Encrypt f_stream
        return oss.str();
    }
    static Task fromString(const std::string &taskData)
    {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;
        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr))
        {
            Action action = actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if (f_stream.is_open())
            {
                return Task(std::move(f_stream), action, filePath);
            }
            else
            {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        }
        else
        {
            throw std::runtime_error("Error in Task data: " + taskData);
        }
    }
};

#endif