#include "Crypto.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"

#include <ctime>
#include <iomanip>
int executeCryption(const std::string &taskData){
    Task task = Task::fromString(taskData);
    ReadEnv env;
    std::string envKey = env.getenv();
    int key = std::stoi(envKey);
    // std::cout << "Key: " << key << "\n";

    /**
     * CHATGPT suggest we load file in buffer make changes and then write as whole as this helps mitigate file pointer issues
     * on first glance , the only issue i can think of is, what if the file is too large
     * to fit into memory? rare case but can actually cause an issue
     * for that edge maybe we can modify to load a chunk of file , write it and then move to the next chunk?
     * for now let the old approach run
    std::vector<char> buffer(std::istreambuf_iterator<char>(task.f_stream), {});
    for (auto &ch : buffer) {
        if (task.action == Action::ENCRYPT) {
            ch = (ch + key) % 256;
        } else {
           ch = (ch - key + 256) % 256;
        }
    }
    task.f_stream.clear();
    task.f_stream.seekp(0, std::ios::beg);
    task.f_stream.write(buffer.data(), buffer.size());

     */
    if(task.action == Action::ENCRYPT){
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch+key) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }else{
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch - key + 256)%256;
            task.f_stream.seekp(-1,std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::cout <<"Exiting encryption/decryption at: " << std::put_time(now, "%Y-%m-%d %H:%M:%S") << std::endl;   
    return 0;
}