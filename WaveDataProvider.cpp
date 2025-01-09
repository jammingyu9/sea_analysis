#include "WaveDataProvider.h"
#include <QSurface3DSeries>

WaveDataProvider::WaveDataProvider()
    : m_waveProxy(std::make_shared<QSurfaceDataProxy>()),
      m_warnProxy(std::make_shared<QSurfaceDataProxy>())
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

            // Prepare warning data
            auto warningData = std::make_unique<QSurfaceDataArray>();
            warningData->reserve(surfaceData->size());

            const float targetHeight = 3.0f; // Height to highlight
            const float threshold = 0.5f;   // Allowable range for intersection

            for (int rowIndex = 0; rowIndex < surfaceData->size(); ++rowIndex) {
                const QSurfaceDataRow row = surfaceData->at(rowIndex);
                QSurfaceDataRow warningRow(row.size());
                for (int col = 0; col < row.size(); ++col) {
                    QVector3D position = row.at(col).position();
                    if (position.y() > targetHeight) {
                        warningRow[col].setPosition(QVector3D(position.x(), position.y(), position.z())); // Keep point
                    } else {
                        warningRow[col].setPosition(QVector3D(position.x(), -15, position.z()));
                    }
                }
                warningData->append(warningRow);
            }

            m_warnProxy->resetArray(*warningData); // Update warning proxy
        }
    }
}

QSurfaceDataProxy* WaveDataProvider::waveProxy()
{
    return m_waveProxy.get();
}

QSurfaceDataProxy* WaveDataProvider::warnProxy()
{
    return m_warnProxy.get();
}
