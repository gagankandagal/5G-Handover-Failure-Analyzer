#include "../include/HandoverAnalyzer.h"

HandoverAnalyzer::HandoverAnalyzer(
    const std::vector<HandoverRecord>& records
)
    : records(records) {
}

int HandoverAnalyzer::getTotalHandovers() const {

    return static_cast<int>(records.size());
}

int HandoverAnalyzer::getSuccessfulHandovers() const {

    int count = 0;

    for (const auto& record : records) {

        if (record.result == "SUCCESS") {
            count++;
        }
    }

    return count;
}

int HandoverAnalyzer::getFailedHandovers() const {

    int count = 0;

    for (const auto& record : records) {

        if (record.result == "FAILURE") {
            count++;
        }
    }

    return count;
}

double HandoverAnalyzer::getSuccessRate() const {

    if (records.empty()) {
        return 0.0;
    }

    return
        static_cast<double>(getSuccessfulHandovers())
        * 100.0
        / records.size();
}

double HandoverAnalyzer::getFailureRate() const {

    if (records.empty()) {
        return 0.0;
    }

    return
        static_cast<double>(getFailedHandovers())
        * 100.0
        / records.size();
}

double HandoverAnalyzer::getAverageRsrp() const {

    if (records.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (const auto& record : records) {
        total += record.rsrp;
    }

    return total / records.size();
}

double HandoverAnalyzer::getAverageRsrq() const {

    if (records.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (const auto& record : records) {
        total += record.rsrq;
    }

    return total / records.size();
}

double HandoverAnalyzer::getAverageSinr() const {

    if (records.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (const auto& record : records) {
        total += record.sinr;
    }

    return total / records.size();
}

double HandoverAnalyzer::getAverageHandoverDuration() const {

    if (records.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (const auto& record : records) {
        total += record.handoverDurationMs;
    }

    return total / records.size();
}
