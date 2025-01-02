#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H
#include <memory>
#include <queue>
#include "Task.hpp"

class ProcessManagement{
    public:
        ProcessManagement();
        bool submitToQueue(std::unique_ptr<Task> t);
        void executeTasks();
    private:
        std::queue<std::unique_ptr<Task>> taskQueue;

};

#endif