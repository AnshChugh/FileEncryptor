#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H
#include <memory>
#include <queue>
#include <iostream>
#include "Task.hpp"
#include <atomic>
#include <semaphore.h>
#include <pthread.h>
#include <mutex>

class ProcessManagement{
    sem_t* itemSemaphore;
    sem_t* emptySemaphore;
    public:
        ProcessManagement();
        ~ProcessManagement();
        bool submitToQueue(std::unique_ptr<Task> t);
        void executeTasks();
    private:
        struct SharedMemory{
            std::atomic<int> size;
            char tasks[1000][256];
            int front;
            int rear;
            void printShareMemory(){
                std::cout << size<< std::endl;
            }
        };
        SharedMemory* sharedMem;
        int shmFd;
        const char* SHM_NAME = "/my_queue";
        std::mutex queueLock;

};

#endif