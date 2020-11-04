//
// Created by mano233 on 2020/11/4.
//

#include "ProdConsService.h"
#include <QTimerEvent>
#include <QDateTime>
#include <QRandomGenerator>

ProdConsService::ProdConsService(QObject *parent)
        : QObject(parent)
        , m_algorithm(RandomRGB)
        , m_currentColor(Qt::black)
        , m_nColorTimer(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

ProdConsService::~ProdConsService()
{
}

QColor ProdConsService::color() const
{
    return m_currentColor;
}

void ProdConsService::setColor(const QColor &color)
{
    m_currentColor = color;
    emit colorChanged(m_currentColor);
}

QColor ProdConsService::timeColor() const
{
    QTime time = QTime::currentTime();
    int r = time.hour();
    int g = time.minute()*2;
    int b = time.second()*4;
    return QColor::fromRgb(r, g, b);
}

ProdConsService::GenerateAlgorithm ProdConsService::algorithm() const
{
    return m_algorithm;
}

void ProdConsService::setAlgorithm(GenerateAlgorithm algorithm)
{
    m_algorithm = algorithm;
}

void ProdConsService::start()
{
    if(m_nColorTimer == 0)
    {
        m_nColorTimer = startTimer(100);
    }
}

void ProdConsService::stop()
{
    if(m_nColorTimer > 0)
    {
        killTimer(m_nColorTimer);
        m_nColorTimer = 0;
    }
}

void ProdConsService::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_nColorTimer)
    {
        switch(m_algorithm)
        {
            case RandomRGB:
                m_currentColor.setRgb(qrand() % 255, qrand() % 255, qrand() % 255);
                break;
            case RandomRed:
                m_currentColor.setRed(qrand() % 255);
                break;
            case RandomGreen:
                m_currentColor.setGreen(qrand() % 255);
                break;
            case RandomBlue:
                m_currentColor.setBlue(qrand() % 255);
                break;
            case LinearIncrease:
            {
                int r = m_currentColor.red() + 10;
                int g = m_currentColor.green() + 10;
                int b = m_currentColor.blue() + 10;
                m_currentColor.setRgb(r % 255, g % 255, b % 255);
            }
                break;
        }
        emit colorChanged(m_currentColor);
        emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        QObject::timerEvent(e);
    }
}