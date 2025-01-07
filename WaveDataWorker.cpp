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
    const int rows = 120;
    const int columns = 120;

    if (m_dataCache.size() >= CACHE_SIZE)
        return;

    QSurfaceDataArray *dataArray = new QSurfaceDataArray();
    dataArray->reserve(rows);

    const float baseAmplitude = 3.5f;   // Base height of the wave
    const float waveFrequency = 0.1f; // Frequency for the waves
    const float waveSpeed = 2.0f;      // Speed of the waves
    const float wavePhase = m_wavePhase; // Current wave phase

    const float centerX = columns / 2.0f;       // Center of the grid in the X-axis
    const float maxDistance = columns / 2.0f;   // Maximum distance from the center on the X-axis

    const int shoreThreshold = rows / 2; // Extend the shoreline damping region to half the grid

    for (int i = 0; i < rows; ++i) {
        QSurfaceDataRow row(columns);

        // Compute Z-based shoreline damping factor (now extending to z < rows / 2)
        float zDamping = (i < shoreThreshold)
                             ? 1.0f - (static_cast<float>(shoreThreshold - i) / shoreThreshold) // Gradual damping near z = 0
                             : 1.0f; // No damping for z > rows / 2

        for (int j = 0; j < columns; ++j) {
            float z = static_cast<float>(i); // Map rows to Z-axis
            float x = static_cast<float>(j); // Map columns to X-axis

            // Apply X-based damping
            float xDistance = std::abs(x - centerX);
            float xDamping = 1.0f - (xDistance / maxDistance);
            xDamping = std::max(0.2f, xDamping); // Ensure minimum damping

            // Combine Z-damping and X-damping
            float combinedDamping = zDamping * xDamping;

            // Calculate wave height
            float wave1 = baseAmplitude * combinedDamping * std::sin(waveFrequency * z + wavePhase * waveSpeed);
            float wave2 = baseAmplitude * combinedDamping * 0.6f * std::sin(waveFrequency * x - wavePhase * waveSpeed);

            // Combine the waves
            float y = wave1 + wave2;

            // Ensure Y-axis range [-10, 10]
            y = qBound(-10.0f, y, 10.0f);

            row[j].setPosition(QVector3D(x, y, z));
        }
        dataArray->append(row);
    }

    m_dataCache.enqueue(dataArray);

    // Update phase for animation
    m_wavePhase += 0.03f; // Increment phase for wave motion
}
