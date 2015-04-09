"""
Copyright (c) 2015, Ming Wen

This program translate sloth json annotations to
FindYourSister json annotations.

Usage: ./gen_labels.py (train | validate | test)
    SLOTH_FILE MISC_FILE [OUT_JSON_FILE]

This program generates json file that FindYourSister can understand
from other files: "SLOTH_FILE" and "IMAGE_SIZE_FILE".

If "OUT_JSON_FILE" is provided, the resulting json will be written
into that file (old content will be truncated), otherwise result
will be displayed in the console.
"""

import sys
import json

# Global variables
GROUP_TYPES = set(["train", "validate", "validation", "test"])


def main():
    if len(sys.argv) < 4:
        raise IOError("More arguments are required.")
    if sys.argv[1] not in GROUP_TYPES:
        raise ValueError("Group type is not valid.")

    slothDoc = open(sys.argv[2], "r")
    sizeDoc = open(sys.argv[3], "r")

    slothJson = json.load(slothDoc)
    sizeJson = json.load(sizeDoc)


    # TODO: collect the size of images in another json file
    # TODO: separate folder names from file names
    # TODO: parse pixel values in double format (in C++)


def setupJsonRoot(groupType):
    root = {}
    if groupType == "train":
        root[u"train"] = []
    elif groupType == "validate" or groupType == "validation":
        root[u"validate"] = []
    else:
        root[u"test"] = []


if __name__ == "__main__":
    main()

