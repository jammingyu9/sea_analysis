#ifndef WAVEDATAPROVIDER_H
#define WAVEDATAPROVIDER_H

#include <QDebug>
#include <QSurfaceDataProxy>
#include <QObject>
#include <QtQml>
#include <QThread>
#include <QVector3D>
#include "WaveDataWorker.h"

class WaveDataProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QVector3D highestPeakPos READ highestPeakPos NOTIFY highestPeakChanged)
    Q_PROPERTY(QVector3D highestPeakLabelPos READ highestPeakLabelPos CONSTANT)

public:
    WaveDataProvider();

    QVector3D highestPeakPos() const { return m_highestPeakPos; }
    QVector3D highestPeakLabelPos() const { return m_highestPeakLabelPos; }

    Q_INVOKABLE void update();
    Q_INVOKABLE QSurfaceDataProxy* waveProxy();

    QVector3D findHighestPeak(const QSurfaceDataArray &surfaceData);

private:
    void setHighestPeak(const QVector3D &peak);

signals:
    void highestPeakChanged();

private:
    std::shared_ptr<QSurfaceDataProxy> m_waveProxy;

    WaveDataWorker worker;
    QThread m_workerThread;
    QVector3D m_highestPeakPos;
    QVector3D m_highestPeakLabelPos;
};

#endif // WAVEDATAPROVIDER_H
