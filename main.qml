import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import My 1.0

ApplicationWindow {
	id: window
	visible: true
	width: 640
	height: 480
	title: qsTr("Scroll")

	ScrollView {
		anchors.fill: parent

		ListView {
			width: parent.width
			model: 4
			delegate: RowLayout {
				width: parent.width
				ItemDelegate {
					text: ObjectSingleton.fruitToVariant(modelData).toString()
					Layout.preferredWidth: 1
					Layout.fillWidth: true
				}
				ItemDelegate {
					text: ObjectSingleton.nameToVariant(modelData).toString()
					Layout.preferredWidth: 1
					Layout.fillWidth: true
				}
			}

			Component.onCompleted: {
				console.log(ObjectMetaObject.Coral)
				console.log(ObjectStatic.Coral)
				console.log(ObjectSingleton.Coral)
				console.log(typeof(ObjectMetaObject.Coconut))
				console.log(ObjectMetaObject.Coconut)
				console.log(ObjectStatic.Chopin)
				console.log(ObjectStatic.fruitToVariant)
				console.log(ObjectSingleton.fruitToVariant)
				console.log(ObjectSingleton.fruitToVariant(ObjectMetaObject.Coconut))
				console.log(ObjectSingleton.variantOf(ObjectMetaObject.Coconut))
			}
		}
	}
}
