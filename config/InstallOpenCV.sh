# Copyright (c) 2015, Ming Wen
#
# Install OpenCV to Debian/Ubuntu machine, and Raspberry Pi
#
# Set working directory
cd ~
#
# Update packages
sudo apt-get update
sudo apt-get upgrade -y
sudo rpi-update # Update Raspberry Pi firmware
#
# Install basic tools
sudo apt-get install -y build-essential pkg-config
sudo apt-get install -y cmake
#
# Install graphic libraries
sudo apt-get install -y libjpeg8-dev libtiff4-dev libjasper-dev libpng12-dev
#
# Install GUI library
sudo apt-get install -y libgtk2.0-dev
#
# Install video libraries
sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
#
# Install calculation libraries
sudo apt-get install -y libatlas-base-dev gfortran
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
# Setup virtualenv and activate
mkvirtualenv cv
workon cv
#
# Install python dev tools
sudo apt-get install -y python2.7-dev
pip install numpy # Install numpy in virtualenv
#
# Download OpenCV
wget -O opencv-2.4.10.zip http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip/download
unzip opencv-2.4.10.zip
cd opencv-2.4.10
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

