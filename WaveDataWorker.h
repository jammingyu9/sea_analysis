#ifndef WAVEDATAWORKER_H
#define WAVEDATAWORKER_H

#include <QDebug>
#include <QObject>
#include <QSurfaceDataProxy>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

constexpr int CACHE_SIZE = 5;

class WaveDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit WaveDataWorker(QObject *parent = nullptr);
    ~WaveDataWorker();

public:
    void startDataGeneration();
    void stopDataGeneration();
    bool dataAvailable();
    std::unique_ptr<QSurfaceDataArray> fetchData();

private:
    void generateData();

private:
    QQueue<QSurfaceDataArray*> m_dataCache;
    QMutex m_cacheMutex;
    QWaitCondition m_cacheCondition;
    bool m_running;
    float m_wavePhase = 0.0;
};

#endif // WAVEDATAWORKER_H
