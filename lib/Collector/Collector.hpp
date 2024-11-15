#pragma once
#ifndef COLLECTOR_HEADER
#define COLLECTOR_HEADER

template<class T>
class Collector {
public:
    Collector() = default;
    Collector(const Collector&) = default;
    Collector(Collector&&) noexcept = default;

    virtual ~Collector() noexcept = default;

    Collector& operator=(const Collector&) = default;
    Collector& operator=(Collector&&) noexcept = default;

    [[nodiscard]]
    virtual T getData() = 0;

    virtual void beginPins() = 0;
};

#endif // !COLLECTOR_HEADER