#include "DataSource.h"

#include <cmath>
#include <stdlib.h>
#include <time.h>

#define PI M_PI

// Constructor
DataSource::DataSource() :
    m_period(DEFAULT_PERIOD),
    m_amplitude(DEFAULT_AMPLITUDE),
    m_progress(0),
    m_translation(DEFAULT_TRANSLATION)
{
    srand(time(NULL));
}

float DataSource::getNextValue() {
    /*
    This Function is called repeatedly (it is designed for 1 per second but the input values could be changed to make it different)


    In this equation the terms are:
        PI: The constant pi
        m_amplitude: The distance from the middle to the top of the sin wave
        m_progress: How far along the sin wave we are (how many seconds)
        m_period: The amount of m_progress that needs to occur for a full occilation
        m_translation: a vertical translation up (constant modifier for the middle of the sin wave)
    */
    float randomModifier = static_cast<float> (rand() / (static_cast<float>(RAND_MAX/MODIF_MAX)));

    float answer = m_amplitude * sin(2 * PI * m_progress * m_period) + m_translation + randomModifier;

    m_progress += 1.0f;

    return answer;
}


// Getters
float DataSource::getPeriod() const
{
    return m_period;
}

float DataSource::getAmplitude() const
{
    return m_amplitude;
}

float DataSource::getProgress() const
{
    return m_progress;
}

float DataSource::getTranslation() const 
{
    return m_translation;
}

// Setters
void DataSource::setPeriod(float period)
{
    m_period = period;
}

void DataSource::setAmplitude(float amplitude)
{
    m_amplitude = amplitude;
}

void DataSource::setProgress(float progress)
{
    m_progress = progress;
}

void DataSource::setTranslation(float translation)
{
    m_translation = translation;
}

float DataSource::getWorryModifier() const {
    return m_modifNum;
}
