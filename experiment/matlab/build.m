
mex CXXFLAGS="\$CXXFLAGS -Wall -std=c++0x" ...
    -I/home/sschaet/dev/aura/experiment/gpufftmex ...
    -I/home/sschaet/dev/aura/include ...
    -I/usr/local/boost/include ...
    -I/usr/local/cuda/include ...
    -L/usr/local/cuda/lib64 ...
    -lcuda ...
    -lcufft ...
    -g ...
    gpufft.cpp
