#ifndef HASHING_PERFORMANCE_MONITOR_H
#define HASHING_PERFORMANCE_MONITOR_H

#include "../../Algorithms/HashingAlgorithm.h"
#include "counter_manager.h"
#include "papi_metrics.h"
#include <string>
// Include other necessary headers that define HashingFactory, PAPICounterManager, MetricsService, and JSONSerializer

// Insert method implementation
void HashingPerformanceMonitor::insert(const std::string& key, const std::string& value) {
    counterManager.start();
    hashingFactory.insert(key, value);
    counterManager.stop();
    totalInsertMetrics = MetricsService::aggregateMetrics(counterManager.getValues());
}

// Search method implementation
std::string HashingPerformanceMonitor::search(const std::string& key) {
    counterManager.start();
    std::string result = hashingFactory.search(key);
    counterManager.stop();
    totalSearchMetrics = MetricsService::aggregateMetrics(counterManager.getValues());
    return result;
}

// Remove method implementation
void HashingPerformanceMonitor::remove(const std::string& key) {
    counterManager.start();
    hashingFactory.remove(key);
    counterManager.stop();
    totalRemoveMetrics = MetricsService::aggregateMetrics(counterManager.getValues());
}
#endif