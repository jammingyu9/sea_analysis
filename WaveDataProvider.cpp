#include "WaveDataProvider.h"

WaveDataProvider::WaveDataProvider()
    : m_dataProxy(std::make_shared<QSurfaceDataProxy>())
{
    qDebug() << "Constructor of WaveDataProvider";
    worker.startDataGeneration();
}

void WaveDataProvider::update()
{
    if (worker.dataAvailable()) {
        std::unique_ptr<QSurfaceDataArray> surfaceData = worker.fetchData();
        if (surfaceData) {
            m_dataProxy->resetArray(*surfaceData); // Pass the data as needed
        }
    }
}

QSurfaceDataProxy* WaveDataProvider::dataProxy()
{
    return m_dataProxy.get();
}
