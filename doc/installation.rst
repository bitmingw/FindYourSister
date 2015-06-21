Installation
============

Requirements
------------

The following packages are required by the program.

* OpenCV
* pkg-config (building helper)
* RapidJSON
* pip
* Pillow (collecting image info)

Some packages are not required but recommended.

* virtualenv (python environment manager)
* SIP and PyQt4 (launching sloth image annotation tool)
* Sphinx (documentation builder)

For Debian/Ubuntu users, two scripts are provided for installation.

1. ``tools/InstallOpencvDeb.sh`` installs OpenCV and related packages.
2. ``tools/InstallPyQt4Deb.sh`` installs SIP and PyQt4. However,
   you should download their source code first from
   http://riverbankcomputing.com/software/ to your home directory,
   then use the script to install them. Please note that this script
   relies on virtualenv which is assumed to be named as ``cv``.
   For detailed info, please look at the file itself.

RapidJSON can be obtained from https://github.com/miloyip/rapidjson.

Pillow and Sphinx are installed using pip.

1. ``pip install Pillow``
2. ``pip install Sphinx``

Build Program 
-------------

When all requirements are satisfied, the program can be built
via ``make`` command.

To use sloth annotation tool

.. code-block:: sh

   cd sloth
   python setup.py install

To build documentation for this project and sloth

.. code-block:: sh

   cd doc
   make html
   cd ../sloth/doc
   make html

