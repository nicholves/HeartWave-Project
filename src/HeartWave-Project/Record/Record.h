#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>
#include <QUuid>
#include <QString>

class Record {
public:
    // Constructor
    Record(QUuid id = QUuid::createUuid(), QDateTime time = QDateTime::currentDateTime(), int chlvl = 1, int low = 0, int med = 0,
            int high = 0, int avgCoh = 0, int length = 0, int achiev = 0);

    QString toString() const;

    // Getters
    QUuid getID() const;
    QDateTime getTime() const;
    int getChallengeLevel() const;
    float getLowPercentage() const;
    float getMedPercentage() const;
    float getHighPercentage() const;
    float getAVGCoherance() const;
    float getLengthOfSession() const;
    float getAchievementScore() const;

    // Setters
    void setID(const QUuid& id);
    void setTime(const QDateTime &time);
    void setChallengeLevel(int level);
    void setLowPercentage(float percentage);
    void setMedPercentage(float percentage);
    void setHighPercentage(float percentage);
    void setAVGCoherance(float coherence);
    void setLengthOfSession(float length);
    void setAchievementScore(float score);

private:
    QUuid sessionID;
    QDateTime m_time;
    int m_challengeLevel;
    float m_lowPercentage;
    float m_medPercentage;
    float m_highPercentage;
    float m_avgCoherance;
    float m_lengthOfSession;
    int m_achievementScore;
};

#endif // RECORD_H
