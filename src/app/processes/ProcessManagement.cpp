#include "ProcessManagement.hpp"
#include <memory>
#include <sys/wait.h>
#include "../Crypto/Crypto.hpp"
ProcessManagement::ProcessManagement(){};

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task){
    taskQueue.push(std::move(task));
    return true;
}   

void ProcessManagement::executeTasks(){
    while(!taskQueue.empty()){
        std::unique_ptr<Task> task = std::move(taskQueue.front());
        taskQueue.pop();
        std::cout << "Executing task : " << task->toString() << std::endl;
        executeCryption(task->toString());
    }
}