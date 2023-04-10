#include "HeartWave.h"

#include <stdlib.h>
#include <time.h>

CoheranceLevel coheranceNumToEnum(float c) {
    if (c <= 5.0f) {
        return CoheranceLevel::high;
    } else if (c <= 10.0f) {
        return CoheranceLevel::medium;
    } else {
        return CoheranceLevel::low;
    }
}

HeartWave::HeartWave() {
    sessionID = QUuid::createUuid();
    startTime = QDateTime::currentMSecsSinceEpoch();
}

void HeartWave::startSession() {
    amplitudes.clear();
    coherances.clear();
    beatDetected = true;
    startTime = QDateTime::currentMSecsSinceEpoch();
}

void HeartWave::stopSession() {
    if (!beatDetected) {
        return;
    }
    beatDetected = false;
    Record r = generateSummary();

    hm.createRecord(r);
}

void HeartWave::deleteSession(QUuid sessionID) {
    std::vector<Record> records = hm.getSessions();

    for (int i = 0; i < records.size(); ++i) {
        Record r = records[i];
        if (r.getID() == sessionID) {
            hm.deleteSession(i);
            return;
        }
    }
}

Record HeartWave::generateSummary() {
    Record r(sessionID, QDateTime::currentDateTime(), settings.getChallengeLevel());

    qint64 st = getStartTime();
    qint64 totalTime = QDateTime::currentMSecsSinceEpoch() - st;
    float totalTimeD = (float)totalTime / 1000.0f;

    r.setLengthOfSession(totalTimeD);
    r.setAchievementScore(getAchievementScore());


    float coherance = 0;
    float low = 0, med = 0, high = 0;

    for (const auto c : coherances) {
        coherance += c.coheranceLvl;

        switch (c.cl) {
        case CoheranceLevel::high:
            high += 1.0f;
            break;
        case CoheranceLevel::medium:
            med += 1.0f;
            break;

        case CoheranceLevel::low:
            low += 1.0f;
            break;
        }
    }

    coherance = coherance / coherances.size();

    low = low / coherances.size();
    med = med / coherances.size();
    high = high / coherances.size();

    r.setAVGCoherance(coherance);
    r.setLowPercentage(low);
    r.setMedPercentage(med);
    r.setHighPercentage(high);

    return r;
}

void HeartWave::resetApp() {
    hm.wipeHistory();
}

void HeartWave::update() {
    if (getBattery() == 0 || !beatDetected) {
        return;
    }

    qint64 delta = QDateTime::currentMSecsSinceEpoch() - lastUpdate;

    if (delta < 100) {
        return;
    } else {
        lastUpdate = QDateTime::currentMSecsSinceEpoch();
    }

    float next = ds.getNextValue();

    amplitudes.push_back(std::pair<float, float>(length, next));

    // if it has been 5 secs since we last calculated coherance or coherance has never been calculated
    if (coherances.size() == 0) {
        if (length >= 5) {
            float coherance = getCurrentCoherance();
            coherances.push_back(CoheranceEntry(length, coherance, coheranceNumToEnum(coherance)));
        }
    } else {
        if ((length - coherances[coherances.size() - 1].time) >= 5) { // it has been 5 seconds or more since the last update
            float coherance = getCurrentCoherance();
            coherances.push_back(CoheranceEntry(length, coherance, coheranceNumToEnum(coherance)));
        }
    }

    length++;

    emit readyToUpdateDisplay();
}



float HeartWave::getAchievementScore() {
    // This might be wrong
    float sum;
    for (const auto c : coherances) {
        sum += c.coheranceLvl;
    }

    return sum;
}

float HeartWave::getCurrentCoherance() {
    float wm = ds.getWorryModifier();

    srand(time(NULL));

    float coherance = (float) rand() / (RAND_MAX / ds.getWorryModifier());

    return coherance;
}



// getters
QUuid HeartWave::getID() {
    return sessionID;
}

qint64 HeartWave::getStartTime() {
    return startTime;
}

bool HeartWave::beatIsDetected() {
    return beatDetected;
}

int HeartWave::getLength() {
    return length;
}

int HeartWave::getBattery() {
    return batteryLvl;
}

std::vector<CoheranceEntry> HeartWave::getCoherances() {
    return coherances;
}

std::vector<std::pair<float, float>> HeartWave::getAmplitudes() const {
    return amplitudes;
}

// setters
void HeartWave::setBeatDetected(bool b) {
    beatDetected = b;
}

void HeartWave::setBattery(int b) {
    batteryLvl = b;
}
