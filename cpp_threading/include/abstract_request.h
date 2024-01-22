#pragma once

class AbstractRequest
{
public:
    virtual void set_value(int val) = 0;
    virtual void process() = 0;
    virtual void finish() = 0;
};