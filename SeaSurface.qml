import QtQuick

SeaSurfaceForm {
    WaveDataProvider {
        id: waveDataProviderId
    }

    Timer {
        id: updateTimer
        interval: 25 // Update interval in milliseconds (e.g., 1 second)
        repeat: true   // Keep repeating the timer
        onTriggered: {
            waveDataProviderId.update(); // Call the update function of WaveDataProvider
        }
    }

    Component.onCompleted: {
        surfaceSeriesId.dataProxy = waveDataProviderId.waveProxy();
        surfaceWarningSeriesId.dataProxy = waveDataProviderId.warnProxy();
        console.log("Data Proxy Set:", surfaceSeriesId.dataProxy !== null);
        updateTimer.start();
    }
}
