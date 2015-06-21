Configuration
=============

All the configurations are saved in ``config`` folder.
By default there are two files, ``features.json`` and ``images.json``.
The later one is obtained using sloth and our script decorators.
The former one is discussed in this section.

Three algorithms should be provided for the point mapping procedure.
They are in charge of "detection", "description"/"extraction"
and "matching", separately.
Detection means finding some feature points on the image.
Description then generates unique vectors to represent their
surrounding areas. Finally matching algorithm compares those vectors
in two images.

This framework currently supports these algorithms.

* Detection

  1. SIFT
  2. SURF
  3. BRISK

* Extraction

  1. SIFT
  2. SURF
  3. BRISK
  4. FREAK

* Matching

  1. Brute Force

The algorithms and their parameters can be adjusted using the json file.

