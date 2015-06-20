#!/usr/bin/env python
"""
Copyright (c) 2015, Ming Wen

This program saves size of images into a json file.

Usage: ./gen_misc.py (IMAGE_FILE | IMAGE_DIR)
    [train|validate|test] [JSON_FILE]

The program reads one image file "IMAGE_FILE", or reads some
image files from "IMAGE_DIR". Then it generates a json format
string containing image folder, name, group and size.

Group name can be "train", "validate" and "test". The default
group name is "train".

If "JSON_FILE" is given, the json string will be written into
the file (old content will be truncated), otherwise the json string
will be displayed in the terminal.
"""

from __future__ import print_function
from __future__ import unicode_literals
import sys
from os.path import abspath, isfile, isdir, join, split, splitext
from os import listdir
from PIL import Image
import json

# Global variables
IMAGE_TYPES = set([".jpg", ".jpeg", ".png", ".bmp", ".tif", ".tiff"])
GROUP_TYPES = set(["train", "validate", "validation", "test"])


def main():
    if len(sys.argv) < 2:
        raise IOError("More arguments are required.")

    if not (isdir(sys.argv[1]) or isfile(sys.argv[1])):
        raise IOError("Given path is not a file or directory.")

    if len(sys.argv) == 2:
        print("Warning: label as default group 'train'.")
        group = "train"
        jsonPath = None
    if len(sys.argv) == 3:
        if sys.argv[2] not in GROUP_TYPES:
            print("Warning: label as default group 'train'.")
            group = "train"
            jsonPath = sys.argv[2]
        else:
            group = sys.argv[2]
            jsonPath = None
    elif len(sys.argv) >= 4:
        if (sys.argv[2]) not in GROUP_TYPES:
            raise ValueError("Image group type not supported.")
        else:
            group = sys.argv[2]
            jsonPath = sys.argv[3]

    imagePath = sys.argv[1]

    rootNode = setupJsonRoot(group)

    # Case isfile()
    if isfile(imagePath):
        addImage(rootNode, imagePath)
    # Case isdir()
    elif isdir(imagePath):
        files = listdir(imagePath)
        for eachFile in files:
            addImage(rootNode, join(imagePath, eachFile))

    # Display or Save
    s = json.JSONEncoder(indent = 4).encode(rootNode)

    if jsonPath != None:
        outfile = open(jsonPath, "w")
        outfile.write(s)
    else:
        print(s)


def setupJsonRoot(groupType):
    root = {}
    if groupType == "train":
        root[u"train"] = []
    elif groupType == "validate" or groupType == "validation":
        root[u"validate"] = []
    elif groupType == "test":
        root[u"test"] = []
    return root


def addImage(root, path):
    """
    Read an image file, and add an entry in the json structure.
    """

    _, extension = splitext(path)
    if extension in IMAGE_TYPES:
        img = Image.open(path)
        imgSize = img.size

        if u"train" in root.keys():
            li = root[u"train"]
        elif u"validate" in root.keys():
            li = root[u"validate"]
        elif u"test" in root.keys():
            li = root[u"test"]

        node = {}
        node[u"folder"] = split(abspath(path))[0]
        node[u"filename"] = split(abspath(path))[1]
        node[u"size"] = {}
        node[u"size"][u"nrows"] = imgSize[1]  # height
        node[u"size"][u"ncols"] = imgSize[0]  # width
        li.append(node)

if __name__ == "__main__":
    main()

