#include "HistoryManager.h"

#include <iostream>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QFileInfo>
using namespace std;

HistoryManager::HistoryManager() {
    if (!readRecordsFromFile()) {
        cout << "No previous records were found on disk" << endl; // something failed badly with reading the records
    }
}

HistoryManager::~HistoryManager() {
    writeRecordsToFile();
}


bool HistoryManager::writeRecordsToFile() {
    QDir dir("../HistoryData");

    if (!dir.exists()) {
        auto error = dir.mkpath(".");
        cout << "made directory for heartwave data" << endl;
    }

    QFile file("../HistoryData/Data.dat");
    if (!file.open(QFile::WriteOnly)) {
        auto error = file.error();
        cout << "failed to open data file" << endl;
        return false;
    }

    QDataStream stream(dynamic_cast<QIODevice*>(&file));

    for (const auto& r : m_records) {
        stream << r.getID();
        stream << r.getTime();
        stream << r.getChallengeLevel();
        stream << r.getLowPercentage();
        stream << r.getMedPercentage();
        stream << r.getHighPercentage();
        stream << r.getAVGCoherance();
        stream << r.getLengthOfSession();
        stream << r.getAchievementScore();
    }


    file.close();
    return true;
}

bool HistoryManager::readRecordsFromFile() {
    QDir dir("../HistoryData");

    if (!dir.exists()) {
        return false;
    }

    QFile file("../HistoryData/Data.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        auto error = file.error();
        cout << "failed to open data file" << endl;
        return false;
    }

    QDataStream stream(dynamic_cast<QIODevice*>(&file));

    while (!stream.atEnd()) {
        QUuid id;
        QDateTime time;
        int challengeLevel;
        float lowPercentage;
        float medPercentage;
        float highPercentage;
        float avgCoherance;
        float lengthOfSession;
        float achievementScore;

        stream >> id;
        stream >> time;
        stream >> challengeLevel;
        stream >> lowPercentage;
        stream >> medPercentage;
        stream >> highPercentage;
        stream >> avgCoherance;
        stream >> lengthOfSession;
        stream >> achievementScore;

        m_records.push_back(Record(id, time, challengeLevel, lowPercentage, medPercentage, highPercentage,
                            avgCoherance, lengthOfSession, achievementScore));
    }


    file.close();
    return true;
}

bool HistoryManager::wipeHistory() {
    m_records.clear();
    return true;
}

bool HistoryManager::deleteSession(int sessionIndex) {
    if (sessionIndex >= m_records.size() || sessionIndex < 0) {
        std::cout << "invalid index for deleting session" << std::endl;
        return false;
    }

    m_records.erase(m_records.begin() + sessionIndex);
    return true;
}

std::vector<Record> HistoryManager::getSessions() const {
    return m_records;
}

bool HistoryManager::createRecord(const Record& r) {
    m_records.push_back(r);
    return true;
}
