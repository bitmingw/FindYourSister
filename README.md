# FindYourSister

This is a collection of tools for object detection.

## Installation

These packages are required by the program:
- build-essential
- cmake
- OpenCV
- python2.7
- pip
- numpy
- rapidjson

These packages are needed if you want to use image annotation tool `sloth`:
- Pillow (from pip)
- SIP (to build Qt projects)
- PyQt4

These packages are recommended to install:
- virtualenv (from pip)

If you are using Debian/Ubuntu/Raspbian, there are two scripts provided.

1. `InstallOpencvDeb.sh` in `tools` folder will install required packages and virtualenv, except rapidjson.

2. `InstallPyQt4Deb.sh` in `tools` folder will install SIP and PyQt4
if you have already download the source code.

To install `rapidjson`, please checkout
```
https://github.com/miloyip/rapidjson
```
 
To install `Pillow`, please use pip
```
pip install Pillow
```

To build the program without annotation tool, type
```
make
```
in current directory.

To install annotation tool `sloth`, type
```
cd sloth
python setup.py install
```
You may want to activate virtualenv in this case.

