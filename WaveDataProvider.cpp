#include "WaveDataProvider.h"
#include <QSurface3DSeries>
#include <QCustom3DItem>

WaveDataProvider::WaveDataProvider()
    : m_waveProxy(std::make_shared<QSurfaceDataProxy>())
{
    qDebug() << "Constructor of WaveDataProvider";
    worker.startDataGeneration();
}

void WaveDataProvider::update()
{
    if (worker.dataAvailable()) {
        std::unique_ptr<QSurfaceDataArray> surfaceData = worker.fetchData();
        if (surfaceData) {
            m_waveProxy->resetArray(*surfaceData); // Pass the data as needed

            QVector3D peak = findHighestPeak(*surfaceData);
            setHighestPeak(peak);
        }
    }
}

QSurfaceDataProxy* WaveDataProvider::waveProxy()
{
    return m_waveProxy.get();
}

QVector3D WaveDataProvider::findHighestPeak(const QSurfaceDataArray &surfaceData)
{
    QVector3D highestPoint;
    float maxHeight = -std::numeric_limits<float>::infinity();

    for (int rowIndex = 0; rowIndex < surfaceData.size(); ++rowIndex) {
        const QSurfaceDataRow &row = surfaceData.at(rowIndex);
        for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
            float height = row.at(colIndex).y(); // Access the y-coordinate (height).

            if (height > maxHeight) {
                maxHeight = height;
                highestPoint = QVector3D(colIndex, height - 0.3, rowIndex);
            }
        }
    }
    return highestPoint;
}

void WaveDataProvider::setHighestPeak(const QVector3D &peak)
{
    if (m_highestPeakPos != peak) {
        m_highestPeakPos = peak;
        m_highestPeakLabelPos = QVector3D(peak.x(), peak.y() + 2, peak.z());
        emit highestPeakChanged();
    }
}
