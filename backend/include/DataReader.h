#ifndef DATA_READER_H
#define DATA_READER_H

#include <string>
#include <vector>

#include "HandoverRecord.h"

class DataReader {
public:
    explicit DataReader(const std::string& filename);

    std::vector<HandoverRecord> readRecords();

private:
    std::string filename;

    std::vector<std::string> splitCSVLine(const std::string& line);
};

#endif