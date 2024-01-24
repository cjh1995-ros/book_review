#pragma once


#include "abstract_request.h"
// #include "worker.h"

class Worker;

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
    static bool init(int workers);
    static bool stop();
    static void add_request(AbstractRequest* rq);
    static bool add_worker(Worker* w);
};