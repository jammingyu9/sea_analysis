import QtQuick
import QtGraphs

Item {
    DataSource {
        id: dataSource
    }

    property alias dataSource : dataSource

    Surface3D {
        id: seaSurfaceGraph

        anchors.fill: parent

        Surface3DSeries {
            id: surfaceSeries
            itemLabelFormat: "@xLabel, @zLabel: @yLabel"
        }
    }
}
