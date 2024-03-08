#ifndef PAPI_COUNTER_MANAGER_H
#define PAPI_COUNTER_MANAGER_H
#include <vector>
#include <stdexcept>
#include <iostream>
#include <papi.h>
#include <sstream>

class PAPICounterManager {
private:
    std::vector<int> events;
    std::vector<long long> values;
    int eventSet = PAPI_NULL;
    bool debug; // Added debug flag

public:
    // Modified constructor to accept a debug parameter with a default value
    PAPICounterManager(const std::vector<int>& eventCodes, bool debug = false)
        : events(eventCodes), values(eventCodes.size(), 0), debug(debug) {
        if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
            throw std::runtime_error("PAPI library initialization failed.");
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI library initialized successfully." << std::endl;
        }
        
        if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
            throw std::runtime_error("Failed to create PAPI event set.");
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI event set created successfully." << std::endl;
        }

        // Attempt to add each event individually for more granular error checking
        for (int event : events) {
            int retval = PAPI_add_event(eventSet, event);
            if (retval != PAPI_OK) {
                std::stringstream ss;
                ss << "Failed to add PAPI event: " << event << ", Error: " << PAPI_strerror(retval);
                throw std::runtime_error(ss.str());
            } else if (debug) { // Check debug flag before printing
                std::cout << "PAPI event " << event << " added successfully." << std::endl;
            }
        }
    }

    void start() {
        if (PAPI_start(eventSet) != PAPI_OK) {
            throw std::runtime_error("Failed to start PAPI counters.");
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI counters started successfully." << std::endl;
        }
    }

    void stop() {
        if (PAPI_stop(eventSet, values.data()) != PAPI_OK) {
            throw std::runtime_error("Failed to stop PAPI counters.");
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI counters stopped successfully." << std::endl;
        }
    }

    const std::vector<long long>& getValues() const {
        return values;
    }

    ~PAPICounterManager() {
        if (PAPI_cleanup_eventset(eventSet) != PAPI_OK) {
            if (debug) { // Only print warning if debug is enabled
                std::cerr << "Warning: Failed to clean up PAPI event set." << std::endl;
            }
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI event set cleaned up successfully." << std::endl;
        }
        if (PAPI_destroy_eventset(&eventSet) != PAPI_OK) {
            if (debug) { // Only print warning if debug is enabled
                std::cerr << "Warning: Failed to destroy PAPI event set." << std::endl;
            }
        } else if (debug) { // Check debug flag before printing
            std::cout << "PAPI event set destroyed successfully." << std::endl;
        }
    }
};

#endif // PAPI_COUNTER_MANAGER_H