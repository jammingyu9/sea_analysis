#include "WaveDataWorker.h"
#include <QRandomGenerator>
#include <QtConcurrent>

WaveDataWorker::WaveDataWorker(QObject *parent)
    : QObject(parent), m_running(true)
{
    qDebug() << "Constructor of WaveDataWorker";
}

WaveDataWorker::~WaveDataWorker() {
    qDebug() << "Destructor of WaveDataWorker";
    stopDataGeneration();
    QMutexLocker locker(&m_cacheMutex);
    while (!m_dataCache.isEmpty()) {
        delete m_dataCache.dequeue();
    }
}

void WaveDataWorker::startDataGeneration() {
    QtConcurrent::run([this]() {
        while (m_running) {
            generateData();
            QThread::msleep(100);
        }
    });
}

void WaveDataWorker::stopDataGeneration() {
    QMutexLocker locker(&m_cacheMutex);
    m_running = false;
    m_cacheCondition.wakeAll();
}

bool WaveDataWorker::dataAvailable() {
    return m_dataCache.size() != 0;
}

std::unique_ptr<QSurfaceDataArray> WaveDataWorker::fetchData() {
    QMutexLocker locker(&m_cacheMutex);
    if (m_dataCache.isEmpty()) {
        return nullptr;
    }

    std::unique_ptr<QSurfaceDataArray> data(m_dataCache.dequeue());
    m_cacheCondition.wakeAll();
    return data;
}

void WaveDataWorker::generateData() {
    const int rows = 50;
    const int columns = 50;

    if (m_dataCache.size() >= CACHE_SIZE)
        return;

    QSurfaceDataArray *dataArray = new QSurfaceDataArray();
    dataArray->reserve(rows);

    const float waveAmplitude = 3.0; // Height of the wave
    const float waveFrequency = 0.5; // Controls the number of waves
    const float wavePhase = m_wavePhase; // Animates the wave over time

    for (int i=0; i<rows; ++i) {
        QSurfaceDataRow row(columns);
        for (int j=0; j<columns; ++j) {
            float x = i;
            float z = j;
            float y = waveAmplitude * std::sin(waveFrequency * x + waveFrequency * z + wavePhase);
            row[j].setPosition(QVector3D(x, y, z));
        }
        dataArray->append(row);
    }

    m_dataCache.enqueue(dataArray);

    m_wavePhase += 0.1f;
    if (m_wavePhase > 2 * M_PI) {
        m_wavePhase -= 2 * M_PI; // Keep the phase within a 0-2π range
    }
}
