import QtQuick
import QtGraphs
import QtQuick3D.Helpers
import QtQuick3D

Item {
    property alias surfaceSeriesId : surfaceSeriesId
    property alias surfaceWarningSeriesId : surfaceWarningSeriesId
    property alias seaSurfaceGraph : seaSurfaceGraph

    anchors.fill: parent

    Surface3D {
        id: seaSurfaceGraph

        anchors.fill: parent

        theme : GraphsTheme {
            id: surfaceTheme
            colorScheme: Qt.Dark
            plotAreaBackgroundVisible: true
            labelsVisible: true
            gridVisible: false
            singleHighlightColor: "red"
            multiHighlightColor: "blue"
            //! [scatter theme]
        }

        environment: ExtendedSceneEnvironment {
            backgroundMode: ExtendedSceneEnvironment.Color
            clearColor: "black"
            tonemapMode: ExtendedSceneEnvironment.TonemapModeNone
            glowEnabled: true
            //! [scene environment]
            glowStrength: 0.8
            glowIntensity: 8
            glowBloom: 1
            glowUseBicubicUpscale: true
            glowLevel: ExtendedSceneEnvironment.GlowLevel.One
                       | ExtendedSceneEnvironment.GlowLevel.Two
                       | ExtendedSceneEnvironment.GlowLevel.Three
                       //| ExtendedSceneEnvironment.GlowLevel.Four
        }


        axisX: Value3DAxis {
            max: 120
            min: 0
        }

        axisY: Value3DAxis {
            max: 10
            min: -10
        }

        axisZ: Value3DAxis {
            max: 120
            min: 0
        }

        Surface3DSeries {
            id: surfaceSeriesId
            itemLabelFormat: "Wave Height: (@xLabel, @zLabel) @yLabel Meters"

            drawMode: Surface3DSeries.DrawSurface
            textureFile: "/home/nicolas/Workspace/sea_analysis/image/ocean_texture.jpg"
        }

        Surface3DSeries {
            id: surfaceWarningSeriesId

            drawMode: Surface3DSeries.DrawWireframe
            wireframeColor: "aquamarine"

        }
    }
}


