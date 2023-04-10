#include "Settings.h"

// Constructor
Settings::Settings() :
    m_challengeLevel(1),
    m_breathPace(0)
{
}

// Getters
int Settings::getChallengeLevel() const
{
    return m_challengeLevel;
}

float Settings::getBreathPace() const
{
    return m_breathPace;
}

// Setters
void Settings::setChallengeLevel(int level)
{
    m_challengeLevel = level;
}

void Settings::setBreathPace(float pace)
{
    m_breathPace = pace;
}
