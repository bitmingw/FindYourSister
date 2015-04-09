"""
Copyright (c) 2015, Ming Wen

This program translate sloth json annotations to
FindYourSister json annotations.
"""

import sys
import json

# Global variables
VALID_TYPES = set(["train", "validate", "validation", "test"])

def main():
    if len(sys.argv) < 3:
        raise IOError("More arguments are required.")
    if sys.argv[1] not in VALID_TYPES:
        raise ValueError("Group name is not valid.")

    doc = open(sys.argv[2])

    s = json.load(doc)
    print s

    # TODO: collect the size of images in another json file
    # TODO: separate folder names from file names
    # TODO: parse pixel values in double format (in C++)

if __name__ == "__main__":
    main()

