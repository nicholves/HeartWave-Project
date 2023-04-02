#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>

class Record {
public:
    // Constructor
    Record(QDateTime time = QDateTime::currentDateTime(), int chlvl = 1, int low = 0, int med = 0,
            int high = 0, int avgCoh = 0, int length = 0, int achiev = 0);

    // Getters
    QDateTime getTime() const;
    int getChallengeLevel() const;
    float getLowPercentage() const;
    float getMedPercentage() const;
    float getHighPercentage() const;
    float getAVGCoherance() const;
    int getLengthOfSession() const;
    int getAchievementScore() const;

    // Setters
    void setTime(const QDateTime &time);
    void setChallengeLevel(int level);
    void setLowPercentage(float percentage);
    void setMedPercentage(float percentage);
    void setHighPercentage(float percentage);
    void setAVGCoherance(float coherence);
    void setLengthOfSession(int length);
    void setAchievementScore(int score);

private:
    QDateTime m_time;
    int m_challengeLevel;
    float m_lowPercentage;
    float m_medPercentage;
    float m_highPercentage;
    float m_avgCoherance;
    int m_lengthOfSession;
    int m_achievementScore;
};

#endif // RECORD_H
