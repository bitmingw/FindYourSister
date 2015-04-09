#!/usr/bin/env python
"""
Copyright (c) 2015, Ming Wen

This program saves size of images into a json file.

Usage: ./sizeof_images.py IMAGE_FILE | IMAGE_DIR [JSON_FILE]

The program reads one image file "IMAGE_FILE", or reads some
image files from "IMAGE_DIR". Then it generates a json format
string containing image folder, name and size.

If "JSON_FILE" is given, the json string will be written into
the file (old file will be truncated), otherwise the json string
will be displayed in the terminal.
"""

import sys
from os.path import isfile, isdir, dirname, basename, join, splitext
from os import listdir
from PIL import Image
import json

# Global variables
IMAGE_TYPES = set([".jpg", ".jpeg", ".png", ".bmp", ".tif", ".tiff"])


def main():
    if len(sys.argv) < 2:
        raise IOError("More arguments are required.")

    if not (isdir(sys.argv[1]) or isfile(sys.argv[1])):
        raise IOError("Given path is not a file or directory.")

    path = sys.argv[1]

    rootNode = setupJsonRoot()

    # Case isfile()
    if isfile(path):
        addImage(rootNode, path)
    # Case isdir()
    elif isdir(path):
        files = listdir(path)
        for eachFile in files:
            addImage(rootNode, join(path, eachFile))

    # Display or Save
    s = json.JSONEncoder(indent = 4).encode(rootNode)

    if len(sys.argv) >= 3:
        outfile = open(sys.argv[2], "w")
        outfile.write(s)
    else:
        print s


def setupJsonRoot():
    root = {}
    root[u"sizes"] = []
    return root


def addImage(root, path):
    """
    Read an image file, and add an entry in the json structure.
    """

    _, extension = splitext(path)
    if extension in IMAGE_TYPES:
        img = Image.open(path)
        imgSize = img.size

        li = root[u"sizes"]
        node = {}
        node[u"folder"] = dirname(path)
        node[u"filename"] = basename(path)
        node[u"size"] = {}
        node[u"size"][u"nrows"] = imgSize[1]  # height
        node[u"size"][u"ncols"] = imgSize[0]  # width
        li.append(node)

if __name__ == "__main__":
    main()

