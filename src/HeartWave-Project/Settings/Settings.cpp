#include "Settings.h"

// Constructor
Settings::Settings() :
    m_challengeLevel(1),
    m_breathPace(30.0f)
{
}

// Getters
int Settings::getChallengeLevel() const
{
    return m_challengeLevel;
}

int Settings::getBreathPace() const
{
    return m_breathPace;
}

// Setters
void Settings::setChallengeLevel(int level)
{
    m_challengeLevel = level;
}

void Settings::setBreathPace(int pace)
{
    m_breathPace = pace;
}
