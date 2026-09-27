#include "../include/CellHandoverStats.h"

#include <map>
#include <utility>

std::vector<CellPairStats>
CellHandoverStats::calculate(
    const std::vector<HandoverRecord>& records
) {

    std::map<
        std::pair<std::string, std::string>,
        CellPairStats
    > statsMap;

    for (const auto& record : records) {

        std::pair<std::string, std::string> key = {
            record.sourceCell,
            record.targetCell
        };

        if (statsMap.find(key) == statsMap.end()) {

            CellPairStats stats;

            stats.sourceCell = record.sourceCell;
            stats.targetCell = record.targetCell;

            stats.attempts = 0;
            stats.successes = 0;
            stats.failures = 0;

            stats.successRate = 0.0;
            stats.failureRate = 0.0;

            statsMap[key] = stats;
        }

        statsMap[key].attempts++;

        if (record.result == "SUCCESS") {
            statsMap[key].successes++;
        }
        else if (record.result == "FAILURE") {
            statsMap[key].failures++;
        }
    }

    std::vector<CellPairStats> result;

    for (auto& entry : statsMap) {

        CellPairStats& stats = entry.second;

        if (stats.attempts > 0) {

            stats.successRate =
                static_cast<double>(stats.successes)
                * 100.0
                / stats.attempts;

            stats.failureRate =
                static_cast<double>(stats.failures)
                * 100.0
                / stats.attempts;
        }

        result.push_back(stats);
    }

    return result;
}
