#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:
    // Constructor
    Settings();

    // Getters
    int getChallengeLevel() const;
    int getBreathPace() const;

    // Setters
    void setChallengeLevel(int level);
    void setBreathPace(int pace);

private:
    int m_challengeLevel = 1;
    int m_breathPace = 30.0f;
};

#endif // SETTINGS_H
