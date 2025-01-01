#ifndef WAVEDATAWORKER_H
#define WAVEDATAWORKER_H

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

signals:
    void dataAvailable();

public slots:
    void startGenerating();
    void stop();
    QSurfaceDataArray *fetchData();

private:
    void generateData();

    QQueue<QSurfaceDataArray*> m_dataCache;
    QMutex m_cacheMutex;
    QWaitCondition m_cacheCondition;
    bool m_running;
};

#endif // WAVEDATAWORKER_H
