#!/bin/bash
# Copyright (c) 2015, Ming Wen
#
# Install PyQt4 to Debian/Ubuntu machine
# IMPORTANT: assume you have downloaded the lastest version of SIP and PyQt4
# from http://sourceforge.net/projects/pyqt in your home directory
#
# Set working directory
cd ~
#
# Update packages
sudo apt-get update
sudo apt-get upgrade -y
#
# Load virtualenv for python
# IMPORTANT: assume you have setup virtualenv for python2.7 called "cv"
source ~/.profile
workon cv
#
# Install relative packages
sudo apt-get install -y libqt4-dev python-qt4 python-qt4-dev qt4-dev-tools pyqt4-dev-tools
#
# unzip SIP
tar zxvf sip-*.tar.gz
#
# unzip PyQt4
tar zxvf PyQt-x11-*.tar.gz
#
# Build SIP
cd sip-*
python2.7 configure.py
make
sudo make install
#
# Build PyQt4
cd ../PyQt-x11-*
python2.7 configure.py
make
sudo make install

