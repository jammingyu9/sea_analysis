#include "WaveDataProvider.h"

WaveDataProvider::WaveDataProvider()
    : m_dataProxy(std::make_shared<QSurfaceDataProxy>()),
      m_dataCache(CACHE_SIZE)
{
    // start loading/generating wave data

    auto *worker = new WaveDataWorker();
}

void WaveDataProvider::update()
{
    // switch cache
    if (m_dataCache.isEmpty())
        return;

    m_data = m_dataCache.takeFirst();
    m_dataProxy->resetArray(m_data);
}

QSurfaceDataProxy *WaveDataProvider::dataProxy()
{
    return m_dataProxy.get();
}
