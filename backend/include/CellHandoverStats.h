#ifndef CELL_HANDOVER_STATS_H
#define CELL_HANDOVER_STATS_H

#include <string>
#include <vector>

#include "HandoverRecord.h"

struct CellPairStats {

    std::string sourceCell;
    std::string targetCell;

    int attempts;
    int successes;
    int failures;

    double successRate;
    double failureRate;
};

class CellHandoverStats {

public:

    static std::vector<CellPairStats> calculate(
        const std::vector<HandoverRecord>& records
    );
};

#endif
