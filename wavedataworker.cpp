#include "WaveDataWorker.h"
#include <QRandomGenerator>

WaveDataWorker::WaveDataWorker(QObject *parent)
    : QObject(parent), m_running(true)
{
}

WaveDataWorker::~WaveDataWorker() {
    stop();
    QMutexLocker locker(&m_cacheMutex);
    while (!m_dataCache.isEmpty()) {
        delete m_dataCache.dequeue();
    }
}

void WaveDataWorker::startGenerating() {

}

void WaveDataWorker::stop() {
    QMutexLocker locker(&m_cacheMutex);
    m_running = false;
    m_cacheCondition.wakeAll();
}

void WaveDataWorker::generateData() {
    const int rows = 50;
    const int columns = 50;

    QSurfaceDataArray *dataArray = new QSurfaceDataArray();
    dataArray->reserve(rows);

    for (int i=0; i<rows; ++i) {
        QSurfaceDataRow row;
        for (int j=0; j<columns; ++j) {
            float x = i;
            float z = j;
            float y = QRandomGenerator::global()->bounded(5.0);
            row[j].setPosition(QVector3D(x, y, z));
        }
        dataArray->append(row);
    }
}

QSurfaceDataArray *WaveDataWorker::fetchData() {
    QMutexLocker locker(&m_cacheMutex);
    if (m_dataCache.isEmpty()) {
        return nullptr;
    }

    QSurfaceDataArray *data = m_dataCache.dequeue();
    m_cacheCondition.wakeAll();
    return data;
}
