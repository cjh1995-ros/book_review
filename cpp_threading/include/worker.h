#pragma once

#include "abstract_request.h"
// #include "dispatcher.h"

class Dispatcher;

#include <condition_variable>
#include <mutex>
#include <chrono>



class Worker
{
private:
    std::condition_variable cv_;
    std::mutex mtx_;
    std::unique_lock<std::mutex> ulock_;

    AbstractRequest* request_;
    bool running_;
    bool ready_;

public:
    Worker() 
    { 
        running_ = true; 
        ready_ = false; 
        ulock_ = std::unique_lock<std::mutex>(mtx_); 
    }

    void run();
    void stop() { running_ = false; }
    void set_request(AbstractRequest* rq) 
    { 
        request_ = rq;
        ready_ = true;    
    }
    std::condition_variable& get_cv() {return cv_; }

};

