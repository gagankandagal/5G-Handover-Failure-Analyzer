#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "../include/DataReader.h"
#include "../include/HandoverRecord.h"
#include "../include/HandoverAnalyzer.h"
#include "../include/FailureAnalyzer.h"
#include "../include/CellHandoverStats.h"

namespace fs = std::filesystem;


// =====================================
// CSV EXPORT
// =====================================

void exportCSV(
    const std::vector<HandoverRecord>& records,
    const std::vector<CellPairStats>& cellStats,
    const HandoverAnalyzer& analyzer
) {

    fs::create_directories("output");

    std::ofstream file(
        "output/handover_report.csv"
    );

    if (!file.is_open()) {

        std::cerr
            << "ERROR: Could not create CSV report.\n";

        return;
    }

    file << "HANDOVER KPI SUMMARY\n";

    file
        << "Total Handovers,Successful,Failed,"
        << "Success Rate,Failure Rate,"
        << "Average RSRP,Average RSRQ,"
        << "Average SINR,Average Duration\n";

    file
        << analyzer.getTotalHandovers() << ","
        << analyzer.getSuccessfulHandovers() << ","
        << analyzer.getFailedHandovers() << ","
        << analyzer.getSuccessRate() << ","
        << analyzer.getFailureRate() << ","
        << analyzer.getAverageRsrp() << ","
        << analyzer.getAverageRsrq() << ","
        << analyzer.getAverageSinr() << ","
        << analyzer.getAverageHandoverDuration()
        << "\n\n";


    file << "CELL TO CELL ANALYSIS\n";

    file
        << "Source Cell,Target Cell,Attempts,"
        << "Successes,Failures,Success Rate,Failure Rate\n";

    for (const auto& stats : cellStats) {

        file
            << stats.sourceCell << ","
            << stats.targetCell << ","
            << stats.attempts << ","
            << stats.successes << ","
            << stats.failures << ","
            << stats.successRate << ","
            << stats.failureRate
            << "\n";
    }


    file << "\nHANDOVER RECORDS\n";

    file
        << "Record ID,Timestamp,Source Cell,Target Cell,"
        << "RSRP,RSRQ,SINR,Handover Duration,Result\n";

    for (const auto& record : records) {

        file
            << record.recordId << ","
            << record.timestamp << ","
            << record.sourceCell << ","
            << record.targetCell << ","
            << record.rsrp << ","
            << record.rsrq << ","
            << record.sinr << ","
            << record.handoverDurationMs << ","
            << record.result
            << "\n";
    }

    file.close();

    std::cout
        << "CSV report created: "
        << "output/handover_report.csv\n";
}


// =====================================
// JSON EXPORT
// =====================================

void exportJSON(
    const std::vector<HandoverRecord>& records,
    const std::vector<CellPairStats>& cellStats,
    const HandoverAnalyzer& analyzer
) {

    fs::create_directories("output");

    std::ofstream file(
        "output/handover_report.json"
    );

    if (!file.is_open()) {

        std::cerr
            << "ERROR: Could not create JSON report.\n";

        return;
    }

    file << std::fixed << std::setprecision(2);

    file << "{\n";


    // =====================================
    // KPI
    // =====================================

    file << "  \"kpis\": {\n";

    file
        << "    \"totalHandovers\": "
        << analyzer.getTotalHandovers()
        << ",\n";

    file
        << "    \"successful\": "
        << analyzer.getSuccessfulHandovers()
        << ",\n";

    file
        << "    \"failed\": "
        << analyzer.getFailedHandovers()
        << ",\n";

    file
        << "    \"successRate\": "
        << analyzer.getSuccessRate()
        << ",\n";

    file
        << "    \"failureRate\": "
        << analyzer.getFailureRate()
        << ",\n";

    file
        << "    \"averageRsrp\": "
        << analyzer.getAverageRsrp()
        << ",\n";

    file
        << "    \"averageRsrq\": "
        << analyzer.getAverageRsrq()
        << ",\n";

    file
        << "    \"averageSinr\": "
        << analyzer.getAverageSinr()
        << ",\n";

    file
        << "    \"averageHandoverDuration\": "
        << analyzer.getAverageHandoverDuration()
        << "\n";

    file << "  },\n";


    // =====================================
    // CELL STATISTICS
    // =====================================

    std::map<std::string, int> failureReasons = FailureAnalyzer::countFailureReasons(records);

    file << "  \"failureReasons\": {\n";

    size_t reasonIndex = 0;
    for (const auto& reason : failureReasons) {
        file << "    \"" << reason.first << "\": " << reason.second;
        if (reasonIndex + 1 < failureReasons.size()) {
            file << ",";
        }
        file << "\n";
        reasonIndex++;
    }

    file << "  },\n";

    file << "  \"cellStatistics\": [\n";

    for (size_t i = 0;
         i < cellStats.size();
         ++i) {

        const auto& stats = cellStats[i];

        file << "    {\n";

        file
            << "      \"sourceCell\": \""
            << stats.sourceCell
            << "\",\n";

        file
            << "      \"targetCell\": \""
            << stats.targetCell
            << "\",\n";

        file
            << "      \"attempts\": "
            << stats.attempts
            << ",\n";

        file
            << "      \"successes\": "
            << stats.successes
            << ",\n";

        file
            << "      \"failures\": "
            << stats.failures
            << ",\n";

        file
            << "      \"successRate\": "
            << stats.successRate
            << ",\n";

        file
            << "      \"failureRate\": "
            << stats.failureRate
            << "\n";

        file << "    }";

        if (i + 1 < cellStats.size()) {
            file << ",";
        }

        file << "\n";
    }

    file << "  ],\n";


    // =====================================
    // RECORDS
    // =====================================

    file << "  \"records\": [\n";

    for (size_t i = 0;
         i < records.size();
         ++i) {

        const auto& record = records[i];

        file << "    {\n";

        file
            << "      \"recordId\": "
            << record.recordId
            << ",\n";

        file
            << "      \"timestamp\": \""
            << record.timestamp
            << "\",\n";

        file
            << "      \"sourceCell\": \""
            << record.sourceCell
            << "\",\n";

        file
            << "      \"targetCell\": \""
            << record.targetCell
            << "\",\n";

        file
            << "      \"rsrp\": "
            << record.rsrp
            << ",\n";

        file
            << "      \"rsrq\": "
            << record.rsrq
            << ",\n";

        file
            << "      \"sinr\": "
            << record.sinr
            << ",\n";

        file
            << "      \"handoverDurationMs\": "
            << record.handoverDurationMs
            << ",\n";

        file
            << "      \"result\": \""
            << record.result
            << "\"\n";

        file << "    }";

        if (i + 1 < records.size()) {
            file << ",";
        }

        file << "\n";
    }

    file << "  ]\n";

    file << "}\n";

    file.close();

    std::cout
        << "JSON report created: "
        << "output/handover_report.json\n";
}


// =====================================
// MAIN
// =====================================

int main() {

    std::cout
        << "=====================================\n";

    std::cout
        << "     5G HANDOVER FAILURE ANALYZER\n";

    std::cout
        << "=====================================\n\n";


    // =====================================
    // READ CSV
    // =====================================

    DataReader reader(
        "data/handover_data.csv"
    );

    std::vector<HandoverRecord> records =
        reader.readRecords();

    std::cout
        << "Records loaded: "
        << records.size()
        << "\n\n";


    if (records.empty()) {

        std::cout
            << "No valid handover records found.\n";

        return 0;
    }


    // =====================================
    // ANALYZER
    // =====================================

    HandoverAnalyzer analyzer(records);


    // =====================================
    // FIRST RECORD
    // =====================================

    std::cout
        << "First handover record:\n";

    std::cout
        << "-------------------------------------\n";

    const HandoverRecord& first =
        records[0];

    std::cout
        << "Record ID          : "
        << first.recordId
        << "\n";

    std::cout
        << "Timestamp          : "
        << first.timestamp
        << "\n";

    std::cout
        << "Source Cell        : "
        << first.sourceCell
        << "\n";

    std::cout
        << "Target Cell        : "
        << first.targetCell
        << "\n";

    std::cout
        << "RSRP               : "
        << first.rsrp
        << " dBm\n";

    std::cout
        << "RSRQ               : "
        << first.rsrq
        << " dB\n";

    std::cout
        << "SINR               : "
        << first.sinr
        << " dB\n";

    std::cout
        << "Handover Duration  : "
        << first.handoverDurationMs
        << " ms\n";

    std::cout
        << "Result             : "
        << first.result
        << "\n";


    // =====================================
    // KPI
    // =====================================

    std::cout
        << "\n=====================================\n";

    std::cout
        << "          HANDOVER KPIs\n";

    std::cout
        << "=====================================\n";

    std::cout
        << "Total Handovers       : "
        << analyzer.getTotalHandovers()
        << "\n";

    std::cout
        << "Successful            : "
        << analyzer.getSuccessfulHandovers()
        << "\n";

    std::cout
        << "Failed                : "
        << analyzer.getFailedHandovers()
        << "\n";

    std::cout
        << std::fixed
        << std::setprecision(2);

    std::cout
        << "Success Rate          : "
        << analyzer.getSuccessRate()
        << "%\n";

    std::cout
        << "Failure Rate          : "
        << analyzer.getFailureRate()
        << "%\n";

    std::cout
        << "Average RSRP          : "
        << analyzer.getAverageRsrp()
        << " dBm\n";

    std::cout
        << "Average RSRQ          : "
        << analyzer.getAverageRsrq()
        << " dB\n";

    std::cout
        << "Average SINR          : "
        << analyzer.getAverageSinr()
        << " dB\n";

    std::cout
        << "Average HO Duration   : "
        << analyzer.getAverageHandoverDuration()
        << " ms\n";


    // =====================================
    // FAILURE ANALYSIS
    // =====================================

    std::cout
        << "\n=====================================\n";

    std::cout
        << "        FAILURE ANALYSIS\n";

    std::cout
        << "=====================================\n\n";

    for (const auto& record : records) {

        if (record.result == "FAILURE") {

            std::cout
                << FailureAnalyzer::analyze(record)
                << "\n";
        }
    }


    // =====================================
    // CELL-TO-CELL
    // =====================================

    std::vector<CellPairStats> cellStats =
        CellHandoverStats::calculate(records);

    std::cout
        << "\n=====================================\n";

    std::cout
        << "       CELL-TO-CELL ANALYSIS\n";

    std::cout
        << "=====================================\n\n";

    for (const auto& stats : cellStats) {

        std::cout
            << stats.sourceCell
            << " -> "
            << stats.targetCell
            << "\n";

        std::cout
            << "Attempts       : "
            << stats.attempts
            << "\n";

        std::cout
            << "Successes      : "
            << stats.successes
            << "\n";

        std::cout
            << "Failures       : "
            << stats.failures
            << "\n";

        std::cout
            << "Success Rate   : "
            << stats.successRate
            << "%\n";

        std::cout
            << "Failure Rate   : "
            << stats.failureRate
            << "%\n";

        std::cout
            << "-------------------------------------\n";
    }


    // =====================================
    // EXPORT
    // =====================================

    std::cout
        << "\n=====================================\n";

    std::cout
        << "          EXPORT RESULTS\n";

    std::cout
        << "=====================================\n\n";

    exportCSV(
        records,
        cellStats,
        analyzer
    );

    exportJSON(
        records,
        cellStats,
        analyzer
    );

    std::cout
        << "\nAnalysis completed successfully.\n";

    return 0;
}
