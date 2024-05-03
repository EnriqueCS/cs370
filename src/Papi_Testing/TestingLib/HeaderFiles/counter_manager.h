#ifndef PAPI_COUNTER_MANAGER_H
#define PAPI_COUNTER_MANAGER_H

#include <stdexcept>
#include <iostream>

class PAPICounterManager {
private:
    int event;
    long long value;
    int eventSet;
    bool debug;

public:
    PAPICounterManager(int eventCode, bool debug = false);
    void start();
    void stop();
    long long getValue() const;
    ~PAPICounterManager();
};

#endif // PAPI_COUNTER_MANAGER_H