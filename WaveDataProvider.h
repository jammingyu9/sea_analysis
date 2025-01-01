#ifndef WAVEDATAPROVIDER_H
#define WAVEDATAPROVIDER_H

#include <QSurfaceDataProxy>
#include <QObject>
#include <QtQml>
#include <QThread>

constexpr int CACHE_SIZE = 5;

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
    QSurfaceDataArray m_data;
    QList<QSurfaceDataArray> m_dataCache;

    QThread m_workerThread;
};

#endif // WAVEDATAPROVIDER_H
