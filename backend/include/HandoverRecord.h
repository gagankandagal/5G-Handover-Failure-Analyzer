#ifndef HANDOVER_RECORD_H
#define HANDOVER_RECORD_H

#include <string>

struct HandoverRecord {

    int recordId;

    std::string timestamp;

    std::string sourceCell;
    std::string targetCell;

    double rsrp;
    double rsrq;
    double sinr;

    double handoverDurationMs;

    std::string result;
};

#endif
