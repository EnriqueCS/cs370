#include "../HeaderFiles/counter_manager.h"
#include <papi.h>
#include <sstream>

PAPICounterManager::PAPICounterManager(int eventCode, bool debug) 
    : event(eventCode), value(0), eventSet(PAPI_NULL), debug(debug) {
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        throw std::runtime_error("PAPI library initialization failed.");
    } else if (debug) {
        std::cout << "PAPI library initialized successfully." << std::endl;
    }

    if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
        throw std::runtime_error("Failed to create PAPI event set.");
    } else if (debug) {
        std::cout << "PAPI event set created successfully." << std::endl;
    }

    int retval = PAPI_add_event(eventSet, event);
    if (retval != PAPI_OK) {
        std::stringstream ss;
        ss << "Failed to add PAPI event: " << event << ", Error: " << PAPI_strerror(retval);
        throw std::runtime_error(ss.str());
    } else if (debug) {
        std::cout << "PAPI event " << event << " added successfully." << std::endl;
    }
}

void PAPICounterManager::start() {
    if (PAPI_start(eventSet) != PAPI_OK) {
        throw std::runtime_error("Failed to start PAPI counter.");
    } else if (debug) {
        std::cout << "PAPI counter started successfully." << std::endl;
    }
}

void PAPICounterManager::stop() {
    if (PAPI_stop(eventSet, &value) != PAPI_OK) {
        throw std::runtime_error("Failed to stop PAPI counter.");
    } else if (debug) {
        std::cout << "PAPI counter stopped successfully." << std::endl;
    }
}

long long PAPICounterManager::getValue() const {
    return value;
}

PAPICounterManager::~PAPICounterManager() {
    if (PAPI_cleanup_eventset(eventSet) != PAPI_OK) {
        if (debug) {
            std::cerr << "Warning: Failed to clean up PAPI event set." << std::endl;
        }
    } else if (debug) {
        std::cout << "PAPI event set cleaned up successfully." << std::endl;
    }
    if (PAPI_destroy_eventset(&eventSet) != PAPI_OK) {
        if (debug) {
            std::cerr << "Warning: Failed to destroy PAPI event set." << std::endl;
        }
    } else if (debug) {
        std::cout << "PAPI event set destroyed successfully." << std::endl;
    }
}