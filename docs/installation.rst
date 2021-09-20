Installation
============

Compiling
---------

To compile and test locally in kami/build::

    git clone https://github.com/k3jph/kami.git
    cd kami
    conan install -if build .
    cmake -B build -DBUILD_SHARED_LIBS:BOOL=FALSE
    cmake --build build
    cmake --build build --target test

Conan Installation
------------------

Forthcoming.