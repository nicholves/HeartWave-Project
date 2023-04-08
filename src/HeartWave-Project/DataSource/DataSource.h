#ifndef DATASOURCE_H
#define DATASOURCE_H

#define DEFAULT_PERIOD      0.085
#define DEFAULT_AMPLITUDE   20
#define DEFAULT_TRANSLATION 70

#define WORRYLVL            2

#if WORRYLVL == 0
#define MODIF_MAX           5.5f

#elif WORRYLVL == 1
#define MODIF_MAX           10.5f

#elif WORRYLVL == 2
#define MODIF_MAX           15.5f

#endif

class DataSource {
public:
    // Constructor
    DataSource();

    // Getters
    float getPeriod() const;
    float getAmplitude() const;
    float getProgress() const;
    float getTranslation() const;
    float getWorryModifier() const;

    // Setters
    void setPeriod(float period);
    void setAmplitude(float amplitude);
    void setProgress(float progress);
    void setTranslation(float translation);
    

    float getNextValue();

private:
    float m_period;
    float m_amplitude;
    float m_progress;
    float m_translation; // The translation up of the sin wave

    float m_modifNum = MODIF_MAX;
};

#endif // DATASOURCE_H
