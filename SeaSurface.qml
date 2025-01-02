import QtQuick
import SeaAnalysis

SeaSurfaceForm {
    WaveDataProvider {
        id: waveDataProviderId
    }

    function loadSeaWaveData() {
        waveDataProviderId.update();
    }

    Timer {
        id: updateTimer
        interval: 100 // Update interval in milliseconds (e.g., 1 second)
        repeat: true   // Keep repeating the timer
        running: true  // Start the timer immediately
        onTriggered: {
            waveDataProviderId.update(); // Call the update function of WaveDataProvider
        }
    }

    Component.onCompleted: {
        surfaceSeriesId.dataProxy = waveDataProviderId.dataProxy();
        console.log("Data Proxy Set:", surfaceSeriesId.dataProxy !== null);
        updateTimer.start();
    }
}
