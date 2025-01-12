import QtQuick

SeaSurfaceForm {
    WaveDataProvider {
        id: waveDataProviderId
    }

    Component.onCompleted: {
        surfaceSeriesId.dataProxy = waveDataProviderId.waveProxy();
        console.log("Data Proxy Set:", surfaceSeriesId.dataProxy !== null);
        updateTimer.start();
    }

    Timer {
        id: updateTimer
        interval: 25 // Update interval in milliseconds (e.g., 1 second)
        repeat: true   // Keep repeating the timer
        onTriggered: {
            waveDataProviderId.update(); // Call the update function of WaveDataProvider
        }
    }

    Connections {
        target: waveDataProviderId
        function onHighestPeakChanged () {
            markerId.visible = true;
            labelId.visible = true;

            // Animate the marker's position
            markerPositionAnimation.from = markerId.position
            markerPositionAnimation.to = waveDataProviderId.highestPeakPos
            markerPositionAnimation.running = true

            // Animate the label's position
            labelPositionAnimation.from = labelId.position
            labelPositionAnimation.to = waveDataProviderId.highestPeakLabelPos
            labelPositionAnimation.running = true

            labelId.text = " Highest Peak: " + waveDataProviderId.highestPeakPos.y.toFixed(1) + " M ";
        }
    }

    Vector3dAnimation {
        id: markerPositionAnimation
        target: markerId
        property: "position"
        duration: 150 // Adjust duration as needed (in milliseconds)
    }

    Vector3dAnimation {
        id: labelPositionAnimation
        target: labelId
        property: "position"
        duration: 150
    }
}
