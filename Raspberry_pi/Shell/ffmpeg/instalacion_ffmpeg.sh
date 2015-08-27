#!bin/bash
#Tutorial seguido: http://www.jeffreythompson.org/blog/2014/11/13/installing-ffmpeg-for-raspberry-pi/

#Bajo las fuentes. Quiero que queden en /usr/src/
cd /usr/src
git clone git://git.videolan.org/x264
git clone git://source.ffmpeg.org/ffmpeg.git

# 1) Compilar e instalar soporte para video H264 video; Este paso no se si es necesario.
cd /usr/src/x264
sudo ./configure --host=arm-unknown-linux-gnueabi --enable-static --disable-opencl
sudo make
sudo make install

# 2) Compilar e instalar ffmpeg.
cd /usr/src/ffmpeg
sudo ./configure --arch=armel --target-os=linux --enable-gpl --enable-libx264 --enable-nonfree
sudo make
sudo make install
