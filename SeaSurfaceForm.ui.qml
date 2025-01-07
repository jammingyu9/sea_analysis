import QtQuick
import QtGraphs
import QtQuick3D.Helpers


Item {
    property alias surfaceSeriesId : surfaceSeriesId

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
            //! [scatter theme]
        }

        environment: ExtendedSceneEnvironment {
            backgroundMode: ExtendedSceneEnvironment.Color
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
            itemLabelFormat: "@xLabel, @zLabel: @yLabel"

            //flatShadingEnabled: false
            drawMode: Surface3DSeries.DrawSurface
            textureFile: "/Users/jammingyu/Workspace/sea_analysis/image/ocean_texture.jpg"


        }
    }
}
