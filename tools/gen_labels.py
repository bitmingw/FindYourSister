#!/usr/bin/env python
"""
Copyright (c) 2015, Ming Wen

This program translate sloth json annotations to
FindYourSister json annotations.

Usage: ./gen_labels.py [gen_labels.json]

This program generates json file that FindYourSister can understand
from other files. They are specified in a json configuration file.

The default configuration file is `gen_labels.json` in current directory.

If you want to display the json info in screen rather than write to
a file, please set `outputJsonFile` to null in configuration.
"""

import sys
import json
from os.path import split
import re

# Global variables
GROUP_TYPES = set(["train", "validate", "validation", "test"])
CONFIG_FILE = "gen_labels.json"


def main():
    global CONFIG_FILE

    if len(sys.argv) == 2:
        CONFIG_FILE = sys.argv[2]

    configDoc = open(CONFIG_FILE, "r")
    configJson = json.load(configDoc)
    # print json.JSONEncoder(indent = 4).encode(configJson)

    # Parse config file
    outfile = configJson[u"outputJsonFile"]

    labelFiles = []
    numLabelFiles = len(configJson[u"imgLabelFiles"])
    i = 0
    while i < numLabelFiles:
        labelFiles.append(configJson[u"imgLabelFiles"][i][u"filename"])
        i += 1

    infoFiles = []
    numInfoFiles = len(configJson[u"imgInfoFiles"])
    i = 0
    while i < numInfoFiles:
        infoFiles.append(configJson[u"imgInfoFiles"][i][u"filename"])
        i += 1

    # Setup the root node of output
    rootNode = setupJsonRoot()

    # Setup the image info database
    infoNode = setupJsonRoot()
    i = 0
    while i < numInfoFiles:
        addInfo(infoNode, infoFiles[i])
        i += 1
    # print infoNode

    # Process each label file
    i = 0
    while i < numLabelFiles:
        processLabels(rootNode, labelFiles[i], infoNode)
        i += 1

    # Write the results
    if outfile is None:
        print json.JSONEncoder(indent = 4).encode(rootNode)
    else:
        out = open(outfile, "w")
        out.write(json.JSONEncoder(indent = 4).encode(rootNode))


def setupJsonRoot():
    root = {}
    root[u"train"] = []
    root[u"validate"] = []
    root[u"test"] = []
    return root


def addInfo(root, filepath):
    fd = open(filepath, "r")
    data = json.load(fd)
    group = None
    if u"train" in data.keys():
        group = u"train"
    elif u"validate" in data.keys():
        group = u"validate"
    elif u"test" in data.keys():
        group = u"test"

    if group is None:
        return
    else:
        # Add all image info into database
        for item in data[group]:
            root[group].append(item)


def processLabels(root, filepath, refInfo):
    fd = open(filepath, "r")
    data = json.load(fd)
    # Each image is stored as a dict, collected in a list
    for img in data:
        processImage(root, img, refInfo)


def processImage(root, imgDict, refInfo):
    imgDir, imgFile = split(imgDict[u"filename"])
    imgDir = getDirectFolder(imgDir)
    group, node = findInfo(imgDir, imgFile, refInfo)
    objID = 0

    if group is not None:
        node[u"objects"] = []
        for label in imgDict[u"annotations"]:
            obj = {}
            obj[u"name"] = label[u"class"]
            obj[u"id"] = objID
            objID += 1
            obj[u"region"] = {}
            obj[u"region"][u"xmin"] = int(label[u"x"])
            obj[u"region"][u"xmax"] = int(label[u"x"] + label[u"width"])
            obj[u"region"][u"ymin"] = int(label[u"y"])
            obj[u"region"][u"ymax"] = int(label[u"y"] + label[u"height"])
            node[u"objects"].append(obj)
        root[group].append(node)


def findInfo(imgDir, imgFile, refInfo):
    """
    Helper function

    Returns (group, refInfo_node) if query image is in refInfo.
    Otherwise returns (None, None)
    """
    if u"train" in refInfo:
        for info in refInfo[u"train"]:
            if info[u"filename"] == imgFile and \
                    (imgDir == "" or \
                    getDirectFolder(info[u"folder"]) == imgDir):
                return (u"train", info)
    if u"validate" in refInfo:
        for info in refInfo[u"train"]:
            if info[u"filename"] == imgFile and \
                    (imgDir == "" or \
                    getDirectFolder(info[u"folder"]) == imgDir):
                return (u"validate", info)
    if u"test" in refInfo:
        for info in refInfo[u"train"]:
            if info[u"filename"] == imgFile and \
                    (imgDir == "" or \
                    getDirectFolder(info[u"folder"]) == imgDir):
                return (u"test", info)
    return (None, None)


def getDirectFolder(path):
    """
    Helper function

    This function returns the direct folder name of a file.
    It is used to match files given different types of path.
    """
    pattern = "/\w+"
    result = re.findall(pattern, path)
    if len(result):
        return result[-1][1:]  # [1:] remove the '/' char at the beginning
    else:
        return ""


if __name__ == "__main__":
    main()

