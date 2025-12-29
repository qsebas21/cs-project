# Docking
## Development container
run
```
$ sudo docker build -f Dockerfile.dev -t ubuntu_mandel_dev .
```
 in the directory `/cs-project` to build the docker image.

run with docker volume
```
sudo docker run -it -v $HOME/cs-project/project/:/workspace ubuntu_mandel_dev
```

The directoy `/cs-project/project` is mounted into the docker at `/workspace`. 

## Production container
run
```
$ sudo docker build -f Dockerfile.prod -t ubuntu_mandel_prod .
```
run with docker volume
```
sudo docker run -it -v $HOME/cs-project/project/:/workspace ubuntu_mandel_prod
```
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