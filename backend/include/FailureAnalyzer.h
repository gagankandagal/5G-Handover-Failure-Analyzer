#ifndef FAILURE_ANALYZER_H
#define FAILURE_ANALYZER_H

#include <string>
#include <map>
#include <vector>
#include "HandoverRecord.h"

class FailureAnalyzer {

public:

    static std::string analyze(
        const HandoverRecord& record
    );

    static std::map<std::string, int> countFailureReasons(
        const std::vector<HandoverRecord>& records
    );
};

#endif
