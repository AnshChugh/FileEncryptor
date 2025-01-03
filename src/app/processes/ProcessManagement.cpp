#include "ProcessManagement.hpp"
#include <memory>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <cstring>
#include "../Crypto/Crypto.hpp"
#include <atomic>
ProcessManagement::ProcessManagement()
{

    itemSemaphore = sem_open("/itemSemaphore", O_CREAT, 0666, 0);
    emptySemaphore = sem_open("/emptySemaphore", O_CREAT, 0666, 1000);
    shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    // if size greather than sharedmemorysize(256) extra data discarded
    // if less , extra data is null bytes '\0'
    ftruncate(shmFd, sizeof(SharedMemory));
    sharedMem = static_cast<SharedMemory *>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0));
    sharedMem->front = 0;
    sharedMem->rear = 0;
    sharedMem->size.store(0);
};
ProcessManagement::~ProcessManagement()
{
    munmap(sharedMem, sizeof(SharedMemory));
    shm_unlink(SHM_NAME);
};
bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task)
{
    sem_wait(emptySemaphore);
    std::unique_lock<std::mutex> lock(queueLock);
    if (sharedMem->size.load() >= 1000)
    {
        return false;
    }
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear = (sharedMem->rear + 1) % 1000;
    sharedMem->size.fetch_add(1);
    lock.unlock();
    sem_post(itemSemaphore);

    int pid = fork();
    if (pid < 0)
    {
        return false;
    }
    else if (pid == 0)
    {
        std::cout << "Entering the parent process\n";
    }
    else
    {
        std::cout << "Entering the child process\n";
        executeTasks();
        std::cout << "Exiting the child process\n";
        exit(0);
    }

    return true;
}

void ProcessManagement::executeTasks()
{
    sem_wait(itemSemaphore);
    std::unique_lock<std::mutex> lock(queueLock);
    char taskStr[256];
    strcpy(taskStr, sharedMem->tasks[sharedMem->front]);
    sharedMem->front = (sharedMem->front + 1) % 1000;
    sharedMem->size.fetch_sub(1);
    lock.unlock();
    sem_post(emptySemaphore);
    std::cout << "Executing child process";
    executeCryption(taskStr);
}