#include "request.h"

void Request::process()
{
    out_func("Starting processing request " + std::to_string(value_) + "...");
}

void Request::finish()
{
    out_func("Finished request " + std::to_string(value_));
}