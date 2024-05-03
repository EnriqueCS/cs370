#include "../../../Algorithms/HashingAlgorithm.h"
#include "../HeaderFiles/counter_manager.h"
#include "../HeaderFiles/func_tester.h"
#include <string>
#include <chrono>  // Include chrono for timing
#include <vector>
#include <functional>

// Method to measure performance of a function using chrono with microsecond precision
long long HashingPerformanceMonitor::measureTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();  // Execute the passed function
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    return static_cast<long long>(duration.count());
}

// Perform a part of the operation on a percentage of data
void HashingPerformanceMonitor::performPartialOperationTime(const std::vector<std::string>& data, double percentage, std::function<void(const std::string&)> operation) {
    size_t limit = static_cast<size_t>(percentage * data.size() / 100.0);
    for (size_t i = 0; i < limit; ++i) {
        operation(data[i]);
    }
}

// Measure performance for inserting data into the hash table
long long HashingPerformanceMonitor::testInsertPerformanceTime(const std::vector<std::string>& data) {
    return measureTime([&]() {
        for (const auto& value : data) {
            hashing_algo.insert(value);
        }
    });
}

// Measure performance for removing data from the hash table
long long HashingPerformanceMonitor::testRemovePerformanceTime(const std::vector<std::string>& data) {
    return measureTime([&]() {
        for (const auto& value : data) {
            hashing_algo.remove(value);
        }
    });
}

// Measure performance for searching data in the hash table
long long HashingPerformanceMonitor::testSearchPerformanceTime(const std::vector<std::string>& data) {
    return measureTime([&]() {
        for (const auto& value : data) {
            hashing_algo.search(value);
        }
    });
}

// Compile performance data from various tests
std::string HashingPerformanceMonitor::getPerformanceDataTime(std::vector<std::string>& lines) {
    std::string result = "Total Strings: " + std::to_string(lines.size()) + "\n\n";

    // Test full table operations
    result += "Insert All Metric: " + std::to_string(testInsertPerformanceTime(lines)) + " ms\n";
    result += "Search Metric (Table is full): " + std::to_string(testSearchPerformanceTime(lines)) + " ms\n";
    result += "Remove All Metric: " + std::to_string(testRemovePerformanceTime(lines)) + " ms\n";
    result += "Search Metric (Table is Empty): " + std::to_string(testSearchPerformanceTime(lines)) + " ms\n\n";

    for (double factor : loadFactors) {
        // Insert to achieve the load factor
        long long insertMetric = measureTime([&]() {
            performPartialOperationTime(lines, factor, [&](const std::string& item) { 
                hashing_algo.insert(item); 
            });
        });

        // Test performance for searching 1% of the items at current load factor
        long long searchMetric = measureTime([&]() {
            performPartialOperationTime(lines, 1, [&](const std::string& item) { 
                hashing_algo.search(item); 
            });
        });

        // Remove inserted items
        long long removeMetric = measureTime([&]() {
            performPartialOperationTime(lines, factor, [&](const std::string& item) { 
                hashing_algo.remove(item); 
            });
        });

        result += "Load Factor " + std::to_string(factor) + "% - Insert Metric: " + std::to_string(insertMetric) + " ms\n";
        result += "Load Factor " + std::to_string(factor) + "% - Search Metric: " + std::to_string(searchMetric) + " ms\n";
        result += "Load Factor " + std::to_string(factor) + "% - Remove Metric: " + std::to_string(removeMetric) + " ms\n\n";
    }

    return result;
}