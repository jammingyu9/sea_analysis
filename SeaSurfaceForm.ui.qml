import QtQuick
import QtGraphs
import QtQuick3D.Helpers


Item {
    property alias surfaceSeriesId : surfaceSeriesId

    anchors.fill: parent

    Gradient {
        id: gradientId
        GradientStop { position: 1.0; color: "blue" } // Qt Brand color; Lemon
        GradientStop { position: 0.0; color: "dodgerblue" } // Qt Brand color; Moss
    }

    Surface3D {
        id: seaSurfaceGraph

        anchors.fill: parent

        theme : GraphsTheme {
            id: scatterTheme
            colorStyle: GraphsTheme.ColorStyle.RangeGradient
            //! [scatter theme]
            baseGradients: [ gradientId ]
            colorScheme: Qt.Dark
            plotAreaBackgroundVisible: false
            labelsVisible: false
            gridVisible: false
            //! [scatter theme]
        }

        environment: ExtendedSceneEnvironment {
            backgroundMode: ExtendedSceneEnvironment.Color
            tonemapMode: ExtendedSceneEnvironment.TonemapModeNone
            clearColor: "dodgerblue"
            glowEnabled: true
            //! [scene environment]
            glowStrength: 1.2
            glowIntensity: 8
            glowBloom: 1
            glowUseBicubicUpscale: true
            glowLevel: ExtendedSceneEnvironment.GlowLevel.One
                       | ExtendedSceneEnvironment.GlowLevel.Two
                       | ExtendedSceneEnvironment.GlowLevel.Three
                       | ExtendedSceneEnvironment.GlowLevel.Four
        }


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
