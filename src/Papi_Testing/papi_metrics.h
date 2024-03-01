#ifndef PAPI_METRICS_H
#define PAPI_METRICS_H

#include <cstddef> // For size_t
#include "../Algorithms/HashingAlgorithm.h"
#include "counter_manager.h"

struct PapiMetrics {
    long long cpuCycles;           // Total CPU cycles
    double ipc;                    // Instructions per cycle
    long long cacheMisses;         // Total cache misses (consider specifying which level if necessary)
    long long branchMissPredictions; // Total branch miss predictions
    long long memoryAccesses;      // Total memory accesses
    long long tlbMisses;           // Total TLB misses
    long long instructionCount;    // Total instruction count
    long long dataHazards;         // Total data hazards (if applicable)

    // Default constructor initializes all metrics to zero or an appropriate default value
    PapiMetrics() 
        : cpuCycles(0), ipc(0.0), cacheMisses(0), branchMissPredictions(0),
          memoryAccesses(0), tlbMisses(0), instructionCount(0), dataHazards(0) {}
};

class MetricsAggregator {
public:
    static void updateTotalMetrics(PapiMetrics& totalMetrics, const PapiMetrics& currentMetrics) {
        totalMetrics.cpuCycles += currentMetrics.cpuCycles;
        totalMetrics.ipc += currentMetrics.ipc; // Note: IPC calculation might need to be adjusted
        totalMetrics.cacheMisses += currentMetrics.cacheMisses;
        totalMetrics.branchMissPredictions += currentMetrics.branchMissPredictions;
        totalMetrics.memoryAccesses += currentMetrics.memoryAccesses;
        totalMetrics.tlbMisses += currentMetrics.tlbMisses;
        totalMetrics.instructionCount += currentMetrics.instructionCount;
        totalMetrics.dataHazards += currentMetrics.dataHazards;
    }
};

class MetricsService {
public:
    static PapiMetrics aggregateMetrics(const std::vector<long long>& values) {
        PapiMetrics metrics{/* Initialize with values */};
        // Aggregate values into metrics
        return metrics;
    }
};

class HashingPerformanceMonitor {
private:
    HashingFactory hashingFactory;
    PapiMetrics totalInsertMetrics;
    PapiMetrics totalSearchMetrics;
    PapiMetrics totalRemoveMetrics;
    PAPICounterManager counterManager;

public:
    // Constructor initializes the hashing factory and counter manager with a predefined set of PAPI events
    HashingPerformanceMonitor(HashingAlgorithmType type, size_t table_size);

    // Performs an insert operation, measuring performance metrics before and after
    void insert(const std::string& key, const std::string& value);

    // Performs a search operation, measuring performance metrics before and after
    std::string search(const std::string& key);

    // Performs a remove operation, measuring performance metrics before and after
    void remove(const std::string& key);

    // Writes the collected total performance metrics to a JSON file
    void writeTotalMetricsToJson(const std::string& destinationFile) const;
};

#endif // PAPI_METRICS_H

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

using json = nlohmann::json;

class JSONSerializer {
public:
    static void writeMetricsToJson(const PapiMetrics& metrics, const std::string& destinationFile) {
        // Create a json object and populate it with PapiMetrics data
        nlohmann::json j = {
            {"cpuCycles", metrics.cpuCycles},
            {"ipc", metrics.ipc},
            {"cacheMisses", metrics.cacheMisses},
            {"branchMissPredictions", metrics.branchMissPredictions},
            {"memoryAccesses", metrics.memoryAccesses},
            {"tlbMisses", metrics.tlbMisses},
            {"instructionCount", metrics.instructionCount},
            {"dataHazards", metrics.dataHazards}
        };

        // Write the json object to a file
        std::ofstream file(destinationFile);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + destinationFile);
        }
        file << j.dump(4); // Serialize the json object to a string and write it to the file
        file.close();
    }
};

#endif // JSON_SERIALIZER_H