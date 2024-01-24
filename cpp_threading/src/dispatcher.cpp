#include "dispatcher.h"
#include "worker.h"

std::queue<AbstractRequest*> Dispatcher::requests;
std::queue<Worker*> Dispatcher::workers;
std::mutex Dispatcher::request_mtx;
std::mutex Dispatcher::worker_mtx;
std::vector<Worker*> Dispatcher::all_workers;
std::vector<std::thread*> Dispatcher::all_threads;


bool Dispatcher::init(int workers)
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

bool Dispatcher::stop()
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

void Dispatcher::add_request(AbstractRequest* rq)
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

bool Dispatcher::add_worker(Worker* worker)
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