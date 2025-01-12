import QtQuick
import QtGraphs
import QtQuick3D.Helpers
import QtQuick3D

Item {
    property alias surfaceSeriesId : surfaceSeriesId
    property alias seaSurfaceGraph : seaSurfaceGraph
    property alias markerId : markerId
    property alias labelId : labelId

    anchors.fill: parent

    Surface3D {
        id: seaSurfaceGraph

        anchors.fill: parent

        theme : GraphsTheme {
            id: surfaceTheme
            colorScheme: Qt.Dark
            plotAreaBackgroundVisible: false
            labelsVisible: false
            gridVisible: false
        }

        environment: ExtendedSceneEnvironment {
            backgroundMode: ExtendedSceneEnvironment.Color
            tonemapMode: ExtendedSceneEnvironment.TonemapModeNone
            glowEnabled: true
            glowStrength: 0.8
            glowIntensity: 8
            glowBloom: 0.8
            glowUseBicubicUpscale: true
            glowLevel: ExtendedSceneEnvironment.GlowLevel.One
                       | ExtendedSceneEnvironment.GlowLevel.Two
                       | ExtendedSceneEnvironment.GlowLevel.Three
                       | ExtendedSceneEnvironment.GlowLevel.Four
        }


        axisX: Value3DAxis {
            max: 120
            min: 0
        }

        axisY: Value3DAxis {
            max: 13
            min: -5
        }

        axisZ: Value3DAxis {
            max: 120
            min: 0
        }

        Surface3DSeries {
            id: surfaceSeriesId
            itemLabelFormat: "Wave Height: (@xLabel, @zLabel) @yLabel Meters"

            drawMode: Surface3DSeries.DrawSurface
            textureFile: "/Users/jammingyu/Workspace/sea_analysis/image/ocean_texture.jpg"
        }

        customItemList: [
            Custom3DItem {
                id: markerId
                meshFile: "/Users/jammingyu/Workspace/sea_analysis/mesh/buoy.obj"
                textureFile: "/Users/jammingyu/Workspace/sea_analysis/mesh/coral.jpg"
                scaling: Qt.vector3d(0.15, 0.15, 0.15)
                visible: false // Start hidden
            },
            Custom3DLabel {
                id: labelId
                backgroundColor: "black"
                textColor: "orange"
                font.bold: true
                visible: false
                scaling: Qt.vector3d(1.5, 1.5, 1.5)
            }
        ]
    }
}


