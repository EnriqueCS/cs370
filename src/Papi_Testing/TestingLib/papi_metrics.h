#ifndef PAPI_METRICS_H
#define PAPI_METRICS_H

#include <cstddef> // For size_t
#include "../../Algorithms/HashingAlgorithm.h"
#include "counter_manager.h"
#include <vector>
#include <utility> // For std::pair

struct PapiMetrics {
    std::vector<long long> values;

    PapiMetrics(size_t numMetrics = 4) : values(numMetrics, 0) {}

    void updateMetric(size_t index, long long value) {
        if (index < values.size()) {
            values[index] += value;
        }
    }

    long long getMetric(size_t index) const {
        return index < values.size() ? values[index] : 0;
    }

    size_t size() const { return values.size(); }
};

class MetricsAggregator {
public:
    static void updateTotalMetrics(PapiMetrics& totalMetrics, const PapiMetrics& currentMetrics) {
        for (size_t i = 0; i < totalMetrics.size() && i < currentMetrics.size(); ++i) {
            totalMetrics.updateMetric(i, currentMetrics.getMetric(i));
        }
    }
};

class MetricsService {
public:
    static PapiMetrics aggregateMetrics(const std::vector<long long>& values) {
        PapiMetrics metrics(values.size());
        for (size_t i = 0; i < values.size(); ++i) {
            metrics.values[i] = values[i];
        }
        return metrics;
    }
};

#ifndef METRICS_SERIALIZER_H
#define METRICS_SERIALIZER_H

class MetricsSerializer {
public:
    static void writeMetricsToTxt(const PapiMetrics& metrics, const std::vector<std::string>& metricNames, const std::string& destinationFile) {
        std::ofstream file(destinationFile);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + destinationFile);
        }

        // Ensure there's a name for each metric value
        size_t numMetricsToWrite = std::min(metrics.size(), metricNames.size());

        for (size_t i = 0; i < numMetricsToWrite; ++i) {
            file << metricNames[i] << ": " << metrics.getMetric(i) << "\n";
        }

        file.close();
    }
};

#endif // METRICS_SERIALIZER_H
#endif

// Define a pair of PAPI event code and its string name
using MetricInfo = std::pair<int, std::string>;
class HashingPerformanceMonitor {
private:
    HashingFactory hashingFactory;
    PapiMetrics totalInsertMetrics;
    PapiMetrics totalSearchMetrics;
    PapiMetrics totalRemoveMetrics;
    PAPICounterManager counterManager;
    std::vector<MetricInfo> metricInfos; // Added to store the metric codes and names

public:
    // Constructor initializes the hashing factory and counter manager with a predefined set of PAPI events
    HashingPerformanceMonitor(HashingAlgorithmType type, size_t table_size, const std::vector<MetricInfo>& metricInfos)
        : hashingFactory(type, table_size), 
          counterManager(ExtractMetricCodes(metricInfos)), // Initialize counterManager with extracted metric codes
          metricInfos(metricInfos) // Store the full metric information (codes and names)
    {
    }

    // Method implementations (insert, search, remove) remain unchanged...
    // Performs an insert operation, measuring performance metrics before and after
    void insert(const std::string& key, const std::string& value);

    // Performs a search operation, measuring performance metrics before and after
    std::string search(const std::string& key);

    // Performs a remove operation, measuring performance metrics before and after
    void remove(const std::string& key);

    // Modified writeTotalMetricsToTxt to include metric names in serialization
    void writeTotalMetricsToTxt(const std::string& destinationFile) const {
        std::vector<std::string> metricNames = ExtractMetricNames(metricInfos); // Extract metric names from stored infos
        MetricsSerializer::writeMetricsToTxt(totalInsertMetrics, metricNames, destinationFile + "_insert.txt");
        // Repeat for totalSearchMetrics and totalRemoveMetrics as needed
    }

private:
    static std::vector<int> ExtractMetricCodes(const std::vector<MetricInfo>& metricInfos) {
        std::vector<int> codes;
        for (const auto& info : metricInfos) {
            codes.push_back(info.first); // Extract and store the metric code
        }
        return codes;
    }

    static std::vector<std::string> ExtractMetricNames(const std::vector<MetricInfo>& metricInfos) {
        std::vector<std::string> names;
        for (const auto& info : metricInfos) {
            names.push_back(info.second); // Extract and store the metric name
        }
        return names;
    }
};