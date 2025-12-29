# Docking
run
```
$ sudo docker build -t ubuntu_mandelbrot .
```
 in the directory `/cs-project/` to build the docker image.

run 
```
$ sudo docker run -it --rm ubuntu_mandelbrot
``` 
to run the docker image. 

The directoy `/project` is copied into the docker. 

# CMake
All `make` commands must be run inside the docker in the directory `/project` 

run 
```
cmake -S . -B build-d -DCMAKE_BUILD_TYPE=Debug
cmake --build build-d
```
or
```
cmake -S . -B build-o -DCMAKE_BUILD_TYPE=Release
cmake --build build-o
```