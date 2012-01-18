﻿var gDidClearOutputPanel = false;function trace(str){    if (!gDidClearOutputPanel) {        fl.outputPanel.clear();        gDidClearOutputPanel = true;    }        fl.outputPanel.trace(str);}function isInstanceOk(instance){    if (instance.name && instance.name != "") {        return false    }    if (instance.libraryItem) {        // Don't promote piano keys, as we need to maintain their depth        var blackList = [            "Shared/Black Key",            "Shared/Highlighted Black Key",            "Shared/White Key",            "Shared/Highlighted White Key",            "Shared/Small Keyboard - Black Key",            "Shared/Small Keyboard - Highlighted Black Key",            "Shared/Small Keyboard - White Key",            "Shared/Small Keyboard - Highlighted White Key"        ];            var name = instance.libraryItem.name;        for (var i = 0; i < blackList.length; i++) {            if (name == blackList[i]) {                return false;            }        }    }    return true;}function processSymbolInstance(instance, layerID){    if (isInstanceOk(instance)) {        trace("Upgrading " + instance);        if (instance.symbolType == "graphic") {            instance.symbolType = "movie clip";        }        instance.name = "_layer_" + layerID;    }}function processFrame(frame, layerID){    var elements = frame.elements;    for (var i = 0; i < elements.length; i++) {        if (elements[i].symbolType) {            processSymbolInstance(elements[i], layerID);        }    }}function processDocument(document){    var timeline = document.getTimeline();    var layers   = timeline.layers;    var layerID = 0;    for (var i = 0; i < layers.length; i++) {        var frames = layers[i].frames;        var lastWasMotion = false;        var needsNewID    = false;            for (var j = 0; j < frames.length; j++) {            var frame = frames[j];            if (frame.tweenType == "motion") {                if (needsNewID) {                    ++layerID;                    needsNewID = false;                }                processFrame(frame, layerID);                lastWasMotion = true;            } else if (lastWasMotion) {                processFrame(frame, layerID);                lastWasMotion = false;                needsNewID = true;            } else {                needsNewID = true;            }        }    }}processDocument(fl.getDocumentDOM());