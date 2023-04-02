#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include "../Record/Record.h"

class HistoryManager {
public:
    // Constructor
    HistoryManager();
    ~HistoryManager();

    // Member functions
    bool writeRecordsToFile();
    bool readRecordsFromFile();
    bool wipeHistory();
    bool deleteSession(int sessionIndex);
    bool createRecord(const Record& r);
    std::vector<Record> getSessions() const;

private:
    std::vector<Record> m_records;
};

#endif // HISTORYMANAGER_H
