======================================
 OpenCV EEG Signal processing library
======================================

Introduction
============


<TODO - make it short>


Install
=======

Prerequests
-----------

OpenCV ... <TODO>


Cmake && make
-------------

::

    // if no build dir
    $ mkdir build
    $ cd build
    $ pwd
    ~/dev/brainappproject/opencvbrain/build
    $ cmake ..
    -- The C compiler identification is Clang 4.1.0
    -- The CXX compiler identification is Clang 4.1.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /Users/pelle/dev/brainappproject/opencvbrain/build
    $ make
    Scanning dependencies of target opencvbrain
    [ 50%] Building CXX object CMakeFiles/opencvbrain.dir/main_brain.cpp.o
    [100%] Building CXX object CMakeFiles/opencvbrain.dir/opencvbrainprocessor.cpp.o
    Linking CXX executable opencvbrain
    [100%] Built target opencvbrain
    $ ./opencvbrain 
    getBrainProcessed(inputArray, samples): 0.252764
    getBrainScore(): 2





Credits
=======


Martin Poulsen and Pelle Krøgholt


