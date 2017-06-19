load("//tools/build_rules:qt.bzl", "qt_cc_library")
cc_library(
    name = "Res",
    hdrs = ["res.h"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui"
    ],
    copts = ["-fpic"]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = [
        '-fpic', '-lboost_system'
    ],
    linkopts = ['-lboost_system','-lboost_filesystem'],
    deps = [
        ":Res",
        ":MainScreen",
        ":GameView",
        "@local//:local",
        "@qt//:qt_widgets",
        "@qt//:qt_multimedia"
    ],
    linkstatic=1
    
)


cc_library(
    name = "GameView",
    srcs = ["GameView.cpp", "GameEngine.cpp", "Item.cpp", "Bonus.cpp", "Hole.cpp", "Player.cpp", "AIPlayer.cpp", "HumanPlayer.cpp", "TextItem.cpp", "ItemsContainer.cpp","utility.cpp"],
    hdrs = ["GameView.h", "GameEngine.h", "Item.h", "Bonus.h", "Hole.h", "Player.h", "AIPlayer.h", "HumanPlayer.h", "TextItem.h", "ItemsContainer.h","utility.h"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_multimedia",
        "@qt//:qt_gui",
        "//tensorflow/cc:cc_ops",
        "//tensorflow/cc:client_session",
        "//tensorflow/core:tensorflow"
    ],
    copts = ["-fpic"]
)

qt_cc_library(
    name = "MainScreen",
    src = "MainScreen.cpp",
    hdr = "MainScreen.h",
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_multimedia",
        "@qt//:qt_gui",
        ":GameView",
        "//tensorflow/cc:cc_ops",
        "//tensorflow/cc:client_session",
        "//tensorflow/core:tensorflow"
    ],
    copts = ["-fpic"]
)
