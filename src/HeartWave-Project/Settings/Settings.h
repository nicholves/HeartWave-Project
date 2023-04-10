#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:
    // Constructor
    Settings();

    // Getters
    int getChallengeLevel() const;
    float getBreathPace() const;

    // Setters
    void setChallengeLevel(int level);
    void setBreathPace(float pace);

private:
    int m_challengeLevel = 1;
    float m_breathPace;
};

#endif // SETTINGS_H
