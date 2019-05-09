libmanabu - The Manabu client library for GAKU Engine
=====================================================
libmanabu is a client library to interface with GAKU Engine written in C++, with interfaces for 
C, Java, Python and PHP (*coming soon*). For native Ruby interfaces use the native 
[Manabu](https://github.com/GAKUEngine/manabu) client.

Building
========
libmanabu requires CMake, the Boost development libraries and headers, OpenSSL development 
libraries and headers, msgpack-c, and possibly a few other tools depending on your system.  
  
*System specific preparation guides are listed below.*  
  
After cloning the repository, you can build libmanabu with the following standard CMake build steps:

```sh
cd libmanabu
mkdir build
cd build
cmake ..
make
```

This will build the libmanabu dynamic library (and specs).

If you wish to build libmanabu without building specs/tests then invoke cmake with 
-DBUILD_TESTS=OFF, like this: ```cmake -DBUILD_TESTS=OFF```.
  
System specific preparation notes follow:

Linux Build Notes
-----------------
There are no particular build notes for Linux other than that you will need to install 
CMake, Boost development libraries, OpenSSL development libraries, and msgpack-c.

On Ubuntu or Debian based systems you can generally install all of the required packages 
with:
```sh
sudo apt-get install cmake g++ libboost-all-dev libssl-dev libmsgpack-dev
```


Windows Build Notes
-------------------
We recommend you compile on MSYS2 on Windows. If you already have MSYS2, make sure you are 
up to date by running ```pacman -Syu```. You likely already have build tools installed, 
but just in case you may want to run: 
```pacman -S mingw-w64-x86_64-toolchain base-devel cmake gcc```.
You'll need the development libraries for Boost, CURL, and OpenSSL. You can do most of this 
with the following command: 
```pacman -S openssl openssl-devel libcurl libcurl-devel mingw-w64-x86_64-msgpack-c```
Note that we didn't install Boost - at the time of this writing the Boost distribution 
available in MSYS2 is missing several components we need. The best solution is to 
compile Boost yourself. For the impatient:

```sh
cd opt
git clone --recursive https://github.com/boostorg/boost.git
cd boost
./bootstrap.sh
./b2
./b2 headers
```

There's a more detailed guide available on the Boost website. _A pre-compiled Boost 
distribution may work, but we have yet to try it._
!NOTE! Cloning and compiling Boost can take a *very* long time.
  
CMake will check for opt/boost and ../boost - if you have boost in another location 
you'll need to specify the BOOST_ROOT or BOOST_INCLUDEDIR and BOOST_LIBDIR attributes 
when you call the cmake command.


OS X Build Notes
----------------
If you are using a package management tool like HomeBrew you can get up and running with 
libmanabu fairly quickly. Just make sure you have the required libraries and tools 
installed: CMake, Boost, OpenSSL/libssl, msgpack-c. You can install these quickly with 
```brew install cmake boost openssl msgpack```.

Testing
=======
After building libmanabu with cmake, start up a gaku testing container instance with:

```sh
gaku container start
gaku container testing
```

Then, run the specs built during the make process:
```sh
./bin/libmanabu_spec --log_level=all
```

License & Contribution
======================
libmanabu is Copyright 2012 K.K. GenSouSha of Aichi, Japan  
All rights reserved.

This software is dual licensed under the GNU GPL version 3 and the AGPL version 3.  
The full text of these licenses can be found here:  
[GPL](https://gnu.org/licenses/gpl.html) [AGPL](https://gnu.org/licenses/agpl.html)  

When submitting code, patches, or pull requests to official GAKU Engine repositories you agree to 
transfer copyright to your code to the GAKU Engine project. This is to prevent an external party 
from controlling code incorporated into GAKU Engine in such a way as to influence the development 
or sub-licensing of GAKU Engine. 

Alternative licenses can be granted upon consultation.  
Please contact info@gakuengine.com for details.
