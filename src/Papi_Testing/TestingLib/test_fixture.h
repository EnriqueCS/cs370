#ifndef HASHINGPERFORMANCEMONITORTESTFIXTURE_H
#define HASHINGPERFORMANCEMONITORTESTFIXTURE_H

#include "../../Algorithms/HashingAlgorithm.h"
#include "./HeaderFiles/func_tester.h"
#include <vector>
#include <string>
#include <cstdio>

using MetricInfo = std::pair<int, std::string>;

class HashingPerformanceMonitorTestFixture {
public:
    HashingPerformanceMonitor* monitor = nullptr;
    HashingConfig config;
    MetricInfo metricInfo;

    HashingPerformanceMonitorTestFixture(const HashingConfig& config, const MetricInfo& metricInfo)
    : config(config), metricInfo(metricInfo) {}

    void SetUp() {
        monitor = new HashingPerformanceMonitor(config, metricInfo);
    }

    void TearDown() {
        delete monitor;
        monitor = nullptr;
    }

    std::string getPerformanceData(std::vector<std::string> lines) {
        return monitor->getPerformanceData(lines);
    }
};

#endif // HASHINGPERFORMANCEMONITORTESTFIXTURE_H