#include "../../../Algorithms/HashingAlgorithm.h"
#include "../HeaderFiles/counter_manager.h"
#include "../HeaderFiles/func_tester.h"
#include <string>

// General method to test performance of any passed function
long long HashingPerformanceMonitor::testPerformance(std::function<void()> func) {
    counterManager.start();
    func();  // Execute the passed function
    counterManager.stop();
    return counterManager.getValue();
}

void HashingPerformanceMonitor::performPartialOperation(const std::vector<std::string>& data, double percentage, std::function<void(const std::string&)> operation) {
    size_t limit = static_cast<size_t>(percentage * data.size() / 100.0);
    for (size_t i = 0; i < limit; ++i) {
        operation(data[i]);
    }
}

long long HashingPerformanceMonitor::testInsertPerformance(const std::vector<std::string>& data){
    long long insertMetric = testPerformance([&]() {
        for (const auto& value : data) {
            hashing_algo.insert(value);
        }
    });
    return insertMetric;
}
long long HashingPerformanceMonitor::testRemovePerformance(const std::vector<std::string>& data){
    // Test remove performance
    long long removeMetric = testPerformance([&]() {
        for (const auto& value : data) {
            hashing_algo.remove(value);
        }
    });
    return removeMetric;
}
long long HashingPerformanceMonitor::testSearchPerformance(const std::vector<std::string>& data){
    // Test search performance
    long long searchMetric = testPerformance([&]() {
        for (const auto& value : data) {
            hashing_algo.search(value);
        }
    });
    return searchMetric;
}

std::string HashingPerformanceMonitor::getPerformanceDataPapi(std::vector<std::string>& lines) {
    std::string result = "Total Strings: " + std::to_string(lines.size()) + "\n\n";
    // std::vector<double> loadFactors = {5, 20, 50, 80, 95};

    // Initial full insertion and metrics collection
    result += "Insert All Metric: " + std::to_string(testInsertPerformance(lines)) + " units\n";
    result += "Search Metric (Table is full): " + std::to_string(testSearchPerformance(lines)) + " units\n";  
    result += "Remove All Metric: " + std::to_string(testRemovePerformance(lines)) + " units\n";
    result += "Search Metric (Table is Empty): " + std::to_string(testSearchPerformance(lines)) + " units\n\n";  

    // Test under different load factors
    for (double factor : loadFactors) {
        // Insert to achieve the load factor
        long long insertMetric = testPerformance([&]() {
            performPartialOperation(lines, factor, [&](const std::string& item) { 
                hashing_algo.insert(item); 
            });
        });

        // Test performance for searching 1% of the items at current load factor
        long long searchMetric = testPerformance([&]() {
            performPartialOperation(lines, 1, [&](const std::string& item) { 
                hashing_algo.search(item); 
            });
        });

        // Remove inserted items
        long long removeMetric = testPerformance([&]() {
            performPartialOperation(lines, factor, [&](const std::string& item) { 
                hashing_algo.remove(item); 
            });
        });

        result += "Load Factor " + std::to_string(factor) + "% - Insert Metric: " + std::to_string(insertMetric) + " units\n";
        result += "Load Factor " + std::to_string(factor) + "% - Search Metric: " + std::to_string(searchMetric) + " units\n";
        result += "Load Factor " + std::to_string(factor) + "% - Remove Metric: " + std::to_string(removeMetric) + " units\n\n";
    }

    
    return result;
}