#pragma once


#include "abstract_request.h"
#include "worker.h"

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>



class Dispatcher
{
    static std::queue<AbstractRequest*> requests;
    static std::queue<Worker*> workers;
    static std::mutex request_mtx;
    static std::mutex worker_mtx;
    static std::vector<Worker*> all_workers;
    static std::vector<std::thread*> all_threads;
public:
    static bool init(int workers)
    {
        std::thread* t = nullptr;
        Worker* w = nullptr;

        for (int i = 0; i < workers; i++)
        {
            w = new Worker;
            all_workers.push_back(w);
            t = new std::thread(&Worker::run, w);
            all_threads.push_back(t);
        }

        return true;
    }
    
    static bool stop()
    {
        for (int i = 0; i < all_workers.size(); ++i)
            all_workers[i]->stop();
        
        std::cout << "Stopped Workers.\n";
        
        for (int j = 0; j < all_threads.size(); ++j)
        {
            all_threads[j]->join();
            std::cout << "Joined threads.\n";
        }

        return true;
    }

    static void add_request(AbstractRequest* rq)
    {
        worker_mtx.lock();
        if (!workers.empty())
        {
            Worker* w = workers.front();
            w->set_request(rq);
            std::condition_variable& cv = w->get_cv();
            cv.notify_one();
            workers.pop();
            worker_mtx.unlock();
        }
        else
        {
            worker_mtx.unlock();
            request_mtx.lock();
            requests.push(rq);
            request_mtx.unlock();
        }
    }
    
    static bool add_worker(Worker* worker)
    {
        bool wait = true;

        request_mtx.lock();
        if (!requests.empty())
        {
            AbstractRequest* rq = requests.front();
            worker->set_request(rq);
            requests.pop();
            wait = false;
            request_mtx.unlock();
        }
        else
        {
            request_mtx.unlock();
            worker_mtx.lock();
            workers.push(worker);
            worker_mtx.unlock();
        }

        return wait;
    }
};