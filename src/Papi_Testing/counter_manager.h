#ifndef PAPI_COUNTER_MANAGER_H
#define PAPI_COUNTER_MANAGER_H

#include <papi.h>
#include <vector>
#include <stdexcept>
#include <iostream>

class PAPICounterManager {
private:
    std::vector<int> events;
    std::vector<long long> values;
    int eventSet = PAPI_NULL;

public:
    PAPICounterManager(const std::vector<int>& eventCodes) : events(eventCodes), values(eventCodes.size(), 0) {
        if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
            throw std::runtime_error("PAPI library initialization failed.");
        }
        if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
            throw std::runtime_error("Failed to create PAPI event set.");
        }

        // Attempt to add each event individually for more granular error checking
        for (int event : events) {
            int retval = PAPI_add_event(eventSet, event);
            if (retval != PAPI_OK) {
                std::stringstream ss;
                ss << "Failed to add PAPI event: " << event << ", Error: " << PAPI_strerror(retval);
                throw std::runtime_error(ss.str());
            }
        }
    }

    void start() {
        if (PAPI_start(eventSet) != PAPI_OK) {
            throw std::runtime_error("Failed to start PAPI counters.");
        }
    }

    void stop() {
        if (PAPI_stop(eventSet, values.data()) != PAPI_OK) {
            throw std::runtime_error("Failed to stop PAPI counters.");
        }
    }

    const std::vector<long long>& getValues() const {
        return values;
    }

    ~PAPICounterManager() {
        if (PAPI_cleanup_eventset(eventSet) != PAPI_OK) {
            std::cerr << "Warning: Failed to clean up PAPI event set." << std::endl;
        }
        if (PAPI_destroy_eventset(&eventSet) != PAPI_OK) {
            std::cerr << "Warning: Failed to destroy PAPI event set." << std::endl;
        }
    }
};

#endif // PAPI_COUNTER_MANAGER_H