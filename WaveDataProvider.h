#ifndef WAVEDATAPROVIDER_H
#define WAVEDATAPROVIDER_H

#include <QDebug>
#include <QSurfaceDataProxy>
#include <QObject>
#include <QtQml>
#include <QThread>
#include "WaveDataWorker.h"

class WaveDataProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    WaveDataProvider();

    Q_INVOKABLE void update();
    Q_INVOKABLE QSurfaceDataProxy* dataProxy();

private:
    void generateData();

private:
    std::shared_ptr<QSurfaceDataProxy> m_dataProxy;

    WaveDataWorker worker;
    QThread m_workerThread;
};

#endif // WAVEDATAPROVIDER_H
