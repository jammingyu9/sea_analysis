import QtQuick
import SeaAnalysis

SeaSurfaceForm {

    function loadSeaWaveData() {
        dataSource.loadData();
    }

    Component.onCompleted: loadSeaWaveData()
}
