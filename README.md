# FindYourSister

This is a collection of tools for object detection.

## Installation

These packages are required by the program:

- OpenCV
- pkg-config
- python2.7
- pip
- Pillow (from pip)
- SIP (to build Qt projects)
- PyQt4
- rapidjson

virtualenv is recommended but not mandatory.

&nbsp;

For Debian/Ubuntu/Raspbian users, two scripts are provided.

  1. `InstallOpencvDeb.sh` in `tools` folder installs OpenCV and relative packages.

  2. `InstallPyQt4Deb.sh` in `tools` folder installs SIP and PyQt4. You should download the source code first and run the script.

You need to manually install `rapidjson` and `Pillow`.

  1. To install `rapidjson`, please check
     ```
     https://github.com/miloyip/rapidjson
     ```
 
  2. To install `Pillow`, please use pip
     ```
     pip install Pillow
     ```

&nbsp;

Finally build the program by the following commands
```
make
cd sloth
python setup.py install
```

