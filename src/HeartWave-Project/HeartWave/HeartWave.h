#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include "Record/Record.h"
#include "DataSource/DataSource.h"
#include "Settings/Settings.h"
#include "HistoryManager/HistoryManager.h"

#include <vector>
#include <utility>

#include <QUuid>
#include <QDateTime>
#include <QObject>


enum CoheranceLevel {
    low,
    medium,
    high
};

CoheranceLevel coheranceNumToEnum(float);

struct CoheranceEntry {
    CoheranceEntry(float t, float coh, CoheranceLevel col) : time(t), coheranceLvl(coh), cl(col)
    {}

    float time;
    float coheranceLvl;
    CoheranceLevel cl;
};

class HeartWave : public QObject {
    Q_OBJECT
public:
    HeartWave();

    void startSession();
    void stopSession();
    void deleteSession(QUuid sessionID);
    Record generateSummary();
    void resetApp();
    void update();

    float getAchievementScore();
    float getCurrentCoherance();

    // getters
    QUuid getID();
    bool beatIsDetected();
    int getLength();
    int getBattery();
    std::vector<CoheranceEntry> getCoherances();

    // setters
    void setBeatDetected(bool b);
    void setBattery(int b);

signals:
    void readyToUpdateDisplay();

private:
    QUuid sessionID;
    bool beatDetected = false;
    int length = 0;
    int batteryLvl = 100;
    std::vector<std::pair<float, float>> amplitudes;
    std::vector<CoheranceEntry> coherances;

    qint64 lastUpdate = 0;

    HistoryManager hm;
    DataSource ds;
    Settings settings;
};

#endif // HEARTWAVE_H
