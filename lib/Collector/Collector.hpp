#pragma once
#ifndef COLLECTOR_HEADER
#define COLLECTOR_HEADER

template<class T>
class Collector {
public:
    virtual ~Collector() noexcept = default;

    [[nodiscard]]
    virtual T getData() = 0;

    virtual void beginPins() = 0;
};

#endif // !COLLECTOR_HEADER