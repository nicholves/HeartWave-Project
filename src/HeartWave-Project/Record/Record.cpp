#include "Record.h"

// Constructor
Record::Record(QUuid id, QDateTime time, int chlvl, int low, int med,
        int high, int avgCoh, int length, int achiev) :
    sessionID(id),
    m_time(time),
    m_challengeLevel(chlvl),
    m_lowPercentage(low),
    m_medPercentage(med),
    m_highPercentage(high),
    m_avgCoherance(avgCoh),
    m_lengthOfSession(length),
    m_achievementScore(achiev)
{
}

// Getters
QUuid Record::getID() const
{
    return sessionID;
}

QDateTime Record::getTime() const
{
    return m_time;
}

int Record::getChallengeLevel() const
{
    return m_challengeLevel;
}

float Record::getLowPercentage() const
{
    return m_lowPercentage;
}

float Record::getMedPercentage() const
{
    return m_medPercentage;
}

float Record::getHighPercentage() const
{
    return m_highPercentage;
}

float Record::getAVGCoherance() const
{
    return m_avgCoherance;
}

int Record::getLengthOfSession() const
{
    return m_lengthOfSession;
}

int Record::getAchievementScore() const
{
    return m_achievementScore;
}

// Setters
void Record::setID(const QUuid& id)
{
    sessionID = id;
}

void Record::setTime(const QDateTime &time)
{
    m_time = time;
}

void Record::setChallengeLevel(int level)
{
    m_challengeLevel = level;
}

void Record::setLowPercentage(float percentage)
{
    m_lowPercentage = percentage;
}

void Record::setMedPercentage(float percentage)
{
    m_medPercentage = percentage;
}

void Record::setHighPercentage(float percentage)
{
    m_highPercentage = percentage;
}

void Record::setAVGCoherance(float coherence)
{
    m_avgCoherance = coherence;
}

void Record::setLengthOfSession(int length)
{
    m_lengthOfSession = length;
}

void Record::setAchievementScore(int score)
{
    m_achievementScore = score;
}
