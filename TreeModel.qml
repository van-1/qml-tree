import QtQuick 2.9


Item {

  property var tree: ({})
  id: root
  ListView {
    anchors.fill: parent
    model: tree
    delegate: Component {
      Loader {
        sourceComponent: treeItemsList
        onLoaded: item.modelDataForNode = modelData
      }
    }
  }

  Component {
    id: treeItemsList

    Row {
      id: treeItemsRow
      property var modelDataForNode: ({})
      spacing: 2

      Text {
        width: 10
        height: 10
        text: modelDataForNode.hasChild ? modelDataForNode.open ? "⏷" : "⏵" : ""
        MouseArea {
          anchors.fill: parent
          onClicked: modelDataForNode.open = !modelDataForNode.open
        }
      }

      Column {
        Text {
          text: modelDataForNode.content
          onTextChanged: {
            console.log(JSON.stringify(modelDataForNode))
          }

          MouseArea {
            anchors.fill: parent
            onClicked: modelDataForNode.open = !modelDataForNode.open
          }
        }

        Loader {
          sourceComponent: modelDataForNode.open ? treeItems : emptyItem
          onLoaded: item.modelDataForNode = modelDataForNode
        }
      }
    }
  }

  Component {
    id: emptyItem
    Item {
      property var modelDataForNode: ({})
    }
  }

  Component {
    id: treeItems
    Column {
      property var modelDataForNode: ({})
      Repeater {
        model: modelDataForNode.childItems
        delegate: Component {
          Loader {
            sourceComponent: treeItemsList
            onLoaded: item.modelDataForNode = modelData
          }
        }
      }
    }
  }
}
