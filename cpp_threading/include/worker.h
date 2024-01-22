#pragma once

#include "abstract_request.h"
#include "dispatcher.h"

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

void Worker::run()
{
    while(running_)
    {
        if (ready_)
        {
            request_->process();
            request_->finish();
            ready_ = false;
        }
        if (Dispatcher::add_worker(this))
        {
            while (!ready_ && running_)
            {
                if (cv_.wait_for(ulock_, std::chrono::seconds(1)) == std::cv_status::timeout)
                {}
            }
        }
    }
}