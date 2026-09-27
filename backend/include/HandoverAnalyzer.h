#ifndef HANDOVER_ANALYZER_H
#define HANDOVER_ANALYZER_H

#include <vector>
#include "HandoverRecord.h"

class HandoverAnalyzer {

private:
    const std::vector<HandoverRecord>& records;

public:

    explicit HandoverAnalyzer(
        const std::vector<HandoverRecord>& records
    );

    int getTotalHandovers() const;

    int getSuccessfulHandovers() const;

    int getFailedHandovers() const;

    double getSuccessRate() const;

    double getFailureRate() const;

    double getAverageRsrp() const;

    double getAverageRsrq() const;

    double getAverageSinr() const;

    double getAverageHandoverDuration() const;
};

#endif
