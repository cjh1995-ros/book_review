#pragma once

#include "abstract_request.h"

#include <string>

typedef void (*log_function)(std::string text);

class Request : public AbstractRequest
{
private:
    int value_;
    log_function out_func;
public:
    void set_value(int val) noexcept override { value_ = val; }
    void set_output(log_function fnc) noexcept { out_func = fnc; }
    void process() override;
    void finish() override;
};

void Request::process()
{
    out_func("Starting processing request " + std::to_string(value_) + "...");
}

void Request::finish()
{
    out_func("Finished request " + std::to_string(value_));
}