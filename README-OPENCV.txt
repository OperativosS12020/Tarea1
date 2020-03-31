los pasos son los siguientes 

> sudo apt install build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb2 libtbb-dev libdc1394-22-dev
> mkdir ~/opencv_build && cd ~/opencv_build

> git clone https://github.com/opencv/opencv.git

> cd ~/opencv_build/opencv

> mkdir build && cd build

> cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_GENERATE_PKGCONFIG=ON \

> make -j4

> sudo make install

> sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'

> sudo ldconfig

**reiniciar la maquina**

**para revisar que este instalado bien**
> pkg-config --modversion opencv4

**bandera para compilacion, es mejor hacerlo con g++, se agrega al final de la instruccion de compilacion, se incluyen las comillas**
> `pkg-config --cflags --libs opencv4`
