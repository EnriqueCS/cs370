#ifndef HASHING_PERFORMANCE_MONITOR_H
#define HASHING_PERFORMANCE_MONITOR_H

#include "../../../Algorithms/HashingAlgorithm.h"  // Adjust path as necessary
#include "counter_manager.h"
#include <vector>
#include <string>
#include <functional> // For std::function
#include <chrono>     // For std::chrono, needed for timing
#include <utility>    // For std::pair

// Define a pair of PAPI event code and its string name
using MetricInfo = std::pair<int, std::string>;

class HashingPerformanceMonitor {
private:
    HashingFactory hashing_algo;  // Adjusted to use a factory for flexibility
    MetricInfo metricInfo;
    PAPICounterManager counterManager;

    // These methods will now be private as they're used internally for testing
    long long testPerformance(std::function<void()> testFunction);
    long long testInsertPerformance(const std::vector<std::string>& data);
    long long testRemovePerformance(const std::vector<std::string>& data);
    long long testSearchPerformance(const std::vector<std::string>& data);
    void performPartialOperation(const std::vector<std::string>& data, double percentage, std::function<void(const std::string&)> operation);
    std::string getPerformanceDataPapi(std::vector<std::string>& lines);

    // These methods will now be private as they're used internally for testing
    long long measureTime(std::function<void()> testFunction);
    long long testInsertPerformanceTime(const std::vector<std::string>& data);
    long long testRemovePerformanceTime(const std::vector<std::string>& data);
    long long testSearchPerformanceTime(const std::vector<std::string>& data);
    void performPartialOperationTime(const std::vector<std::string>& data, double percentage, std::function<void(const std::string&)> operation);
    std::string getPerformanceDataTime(std::vector<std::string>& lines);

    std::vector<double> createVectorWithSteps(double stepSize) {
        std::vector<double> vec;
        for (double i = 2; i < 100; i += stepSize) {
            vec.push_back(i);
        }
        return vec;
    }
    double stepSize = 2; // Adjust this as needed
    std::vector<double> loadFactors = createVectorWithSteps(stepSize);

public:
    // Constructor now accepts a HashingConfig object and a MetricInfo object for initialization
    HashingPerformanceMonitor(const HashingConfig& config, const MetricInfo& metricInfo)
        : hashing_algo(config), counterManager(metricInfo.first), metricInfo(metricInfo) {}

    std::string getPerformanceData(std::vector<std::string>& lines){
        return getPerformanceDataPapi(lines) + getPerformanceDataTime(lines);
    }
};

#endif // HASHING_PERFORMANCE_MONITOR_H