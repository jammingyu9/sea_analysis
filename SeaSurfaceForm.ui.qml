import QtQuick
import QtGraphs

Item {
    property alias surfaceSeriesId : surfaceSeriesId

    anchors.fill: parent

    Surface3D {
        id: seaSurfaceGraph

        anchors.fill: parent

        axisX: Value3DAxis {
            max: 50
            min: 0
        }

        axisY: Value3DAxis {
            max: 5
            min: -5
        }

        axisZ: Value3DAxis {
            max: 50
            min: 0
        }

        Surface3DSeries {
            id: surfaceSeriesId
            itemLabelFormat: "@xLabel, @zLabel: @yLabel"


        }
    }
}
