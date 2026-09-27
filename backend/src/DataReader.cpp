#include "../include/DataReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

DataReader::DataReader(const std::string& filename)
    : filename(filename) {
}

std::string trim(const std::string& str) {

    size_t first = str.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\r\n");

    return str.substr(first, last - first + 1);
}

std::vector<std::string> DataReader::splitCSVLine(
    const std::string& line) {

    std::vector<std::string> fields;

    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, ',')) {
        fields.push_back(trim(field));
    }

    return fields;
}

std::vector<HandoverRecord> DataReader::readRecords() {

    std::vector<HandoverRecord> records;

    std::ifstream file(filename);

    if (!file.is_open()) {

        std::cerr << "Error: Could not open file: "
                  << filename << std::endl;

        return records;
    }

    std::string line;

    // Read CSV header
    if (!std::getline(file, line)) {

        std::cerr << "Error: CSV file is empty."
                  << std::endl;

        return records;
    }

    int lineNumber = 1;

    while (std::getline(file, line)) {

        lineNumber++;

        if (trim(line).empty())
            continue;

        std::vector<std::string> fields =
            splitCSVLine(line);

        // New CSV format has 9 columns
        if (fields.size() != 9) {

            std::cerr
                << "Warning: Invalid CSV row at line "
                << lineNumber
                << " - expected 9 columns, found "
                << fields.size()
                << std::endl;

            continue;
        }

        try {

            HandoverRecord record;

            record.recordId =
                std::stoi(fields[0]);

            record.timestamp =
                fields[1];

            record.sourceCell =
                fields[2];

            record.targetCell =
                fields[3];

            record.rsrp =
                std::stod(fields[4]);

            record.rsrq =
                std::stod(fields[5]);

            record.sinr =
                std::stod(fields[6]);

            record.handoverDurationMs =
                std::stod(fields[7]);

            record.result =
                fields[8];

            // Normalize result
            std::transform(
                record.result.begin(),
                record.result.end(),
                record.result.begin(),
                [](unsigned char c) {
                    return std::toupper(c);
                }
            );

            records.push_back(record);

        }
        catch (const std::exception& e) {

            std::cerr
                << "Warning: Invalid data at line "
                << lineNumber
                << ": "
                << e.what()
                << std::endl;
        }
    }

    file.close();

    return records;
}
