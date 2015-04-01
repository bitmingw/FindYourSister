# FindYourSister

This is a collection of tools for object detection.

## Installation

These packages are required by the program:
- build-essential
- OpenCV
- python2.7
- pip
- numpy

These packages are needed if you want to use image annotation tool `sloth`:
- Pillow (from pip)
- SIP (to build Qt projects)
- PyQt4

These packages are recommended to install:
- virtualenv (from pip)

If you are using Debian/Ubuntu/Raspbian, there are two scripts provided.

`InstallOpencvDeb.sh` in `tools` folder will install required packages and virtualenv.

`InstallPyQt4Deb.sh` in `tools` folder will install SIP and PyQt4
if you have already download the source code.

Install `Pillow` is easy with
```
pip install Pillow
```

To build the program, type
```
make
```
in current directory.

To install annotation tool `sloth`, type
```
cd sloth
python setup.py install
```

