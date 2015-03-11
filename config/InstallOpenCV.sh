# Copyright (c) 2015, Ming Wen
#
# Install OpenCV to Debian/Ubuntu machine, and Raspberry Pi
#
# Set working directory
cd ~
#
# Update packages
sudo apt-get update
sudo apt-get upgrade
sudo rpi-update # Update Raspberry Pi firmware
#
# Install basic tools
sudo apt-get install build-essential cmake pkg-config
#
# Install graphic libraries
sudo apt-get install libjpeg8-dev libtiff4-dev libjasper-dev libpng12-dev
#
# Install GUI library
sudo apt-get install libgtk2.0-dev
#
# Install video libraries
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
#
# Install calculation libraries
sudo apt-get install libatlas-base-dev gfortran
#
# Install pip
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
#
# Install virtualenv for python
sudo pip install virtualenv virtualenvwrapper
#
# Update profile
echo "export WORKON_HOME=$HOME/.virtualenvs" >> ~/.profile
echo "source /usr/local/bin/virtualenvwrapper.sh" >> ~/.profile
#
# Reload .profile
source ~/.profile
#
# Setup virtualenv
mkvirtualenv cv
#
# Install python dev tools
sudo apt-get install python2.7-dev
sudo pip install numpy
#
# Download OpenCV
wget -O opencv-2.4.10.zip http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip/download
unzip opencv-2.4.10.zip
cv opencv-2.4.10
#
# Configure
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D INSTALL_C_EXAMPLES=ON INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON ..
#
# Make - It will take a lot of time
make
#
# Install OpenCV
sudo make install
sudo ldconfig
#
# Link OpenCV library to virtualenv
cd ~./virtualenvs/cv/lib/python2.7/site-packages/
ln -s /usr/local/lib/python2.7/site-packages/cv2.so cv2.so
ln -s /usr/local/lib/python2.7/site-packages/cv.py cv.py

