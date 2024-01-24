#include "worker.h"
#include "dispatcher.h"


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