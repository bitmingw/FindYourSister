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
a file, please set `outputJsonFile` to Null in configuration.
"""

import sys
import json
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
    print json.JSONEncoder(indent = 4).encode(configJson)

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
    print infoNode

    # TODO: Add each label file into the json structure


def setupJsonRoot():
    root = {}
    root[u"train"] = []
    root[u"validate"] = []
    root[u"test"] = []
    return root


def addInfo(node, filepath):
    fd = open(filepath, "r")
    data = json.load(fd)
    group = None
    if u"train" in data.keys():
        group = u"train"
    elif u"validate" in data.keys():
        group = u"validate"
    elif u"test" in data.keys():
        group = u"test"

    if group == None:
        return
    else:
        # Add all image info into database
        for item in data[group]:
            node[group].append(item)


def getDirectFolder(path):
    """
    This function returns the direct folder name of a file.
    It is used to match files given different types of path.
    """
    pattern = "/\w+"
    result = re.findall(pattern, path)
    return result[-1][1:]  # [1:] remove the '/' char at the beginning


if __name__ == "__main__":
    main()

