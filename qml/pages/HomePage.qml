import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"
import "qrc:/qml/views"

XTitledPage {
    id: homePage
    statusBarHeight: ApplicationManagerObj.systemStatusBarSize

    titlebar.title: qsTr("XOrm Demo One to Many")
    titlebar.primaryAction: homeNavController.depth > 1
                            ? primaryAction
                            : null

    XAction {
        id: primaryAction
        text: qsTr("Open global drawer")
        icon.source: "qrc:/img/icons/arrow-left.svg"
        onTriggered: homePage.back()
    }

    function back() {
        if(homeNavController.depth > 1) {
            homeNavController.goBack()
            return true
        }
        return false
    }

    XViewNavController {
        id: homeNavController
        anchors.fill: parent

        initialView: MemberListingView {}

        property int memberEditionViewIndex:    0
        property int memberDetailsViewIndex:    1
        property int projectEditionViewIndex:   2
        viewNavigationModel: [
            { view: "views/MemberEditionView.qml",  stacked: true },
            { view: "views/MemberDetailsView.qml",  stacked: true },
            { view: "views/ProjectEditionView.qml", stacked: true }
        ]
    }
}
