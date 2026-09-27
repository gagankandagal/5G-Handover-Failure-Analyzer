#include "../include/FailureAnalyzer.h"

#include <sstream>
#include <iomanip>
#include <map>
#include <vector>

std::string FailureAnalyzer::analyze(
    const HandoverRecord& record
) {
    std::ostringstream output;

    output << std::fixed << std::setprecision(1);

    output << "Handover Failure Analysis\n";
    output << "-------------------------\n";

    output << "Record ID: " << record.recordId << "\n";
    output << "Timestamp: " << record.timestamp << "\n";
    output << "Source Cell: " << record.sourceCell << "\n";
    output << "Target Cell: " << record.targetCell << "\n";

    output << "\nRadio Measurements:\n";
    output << "- RSRP: " << record.rsrp << " dBm\n";
    output << "- RSRQ: " << record.rsrq << " dB\n";
    output << "- SINR: " << record.sinr << " dB\n";
    output << "- Handover Duration: "
           << record.handoverDurationMs << " ms\n";

    output << "\nPotential Indicators:\n";

    bool indicatorFound = false;

    if (record.rsrp < -110.0) {
        output << "- Very weak RSRP detected.\n";
        indicatorFound = true;
    }
    else if (record.rsrp < -100.0) {
        output << "- Weak RSRP detected.\n";
        indicatorFound = true;
    }

    if (record.rsrq < -15.0) {
        output << "- Poor RSRQ indicates possible radio-quality concern.\n";
        indicatorFound = true;
    }

    if (record.sinr < 5.0) {
        output << "- Very low SINR detected.\n";
        indicatorFound = true;
    }
    else if (record.sinr < 10.0) {
        output << "- Low SINR detected.\n";
        indicatorFound = true;
    }

    if (record.handoverDurationMs > 300.0) {
        output << "- High handover completion duration detected.\n";
        indicatorFound = true;
    }

    if (!indicatorFound) {
        output << "- No strong radio-quality indicator detected "
               << "from the configured thresholds.\n";
    }

    output << "\nInvestigation Status:\n";
    output << "Requires further investigation. "
           << "The indicators above are observations from "
           << "the available measurements and do not establish "
           << "a definitive root cause.\n";

    return output.str();
}


std::map<std::string, int>
FailureAnalyzer::countFailureReasons(
    const std::vector<HandoverRecord>& records
) {
    std::map<std::string, int> reasons;

    for (const auto& record : records) {

        if (record.result != "FAILURE") {
            continue;
        }

        if (record.rsrp < -110.0) {
            reasons["Very Weak RSRP"]++;
        }
        else if (record.rsrp < -100.0) {
            reasons["Weak RSRP"]++;
        }

        if (record.rsrq < -15.0) {
            reasons["Poor RSRQ"]++;
        }

        if (record.sinr < 5.0) {
            reasons["Very Low SINR"]++;
        }
        else if (record.sinr < 10.0) {
            reasons["Low SINR"]++;
        }

        if (record.handoverDurationMs > 300.0) {
            reasons["High Handover Duration"]++;
        }
    }

    return reasons;
}
