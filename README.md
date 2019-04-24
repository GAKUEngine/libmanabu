libmanabu - The Manabu client library for GAKU Engine
=====================================================
libmanabu is a client library to interface with GAKU Engine written in C++, with interfaces for 
C, Java, Python and PHP (*coming soon*). For native Ruby interfaces use the native 
[Manabu](https://github.com/GAKUEngine/manabu) client.

Building
========
libmanabu requires CMake and a few other tools to build. After cloning the repository, you can 
build libmanabu with the following standard CMake build steps:

```sh
cd libmanabu
mkdir build
cd build
cmake ..
make
```

This will build the libmanabu dynamic library (and specs).

Testing
=======
After building libmanabu with cmake, start up a gaku testing container instance with:

```sh
gaku contianer start
gaku container testing
```

Then, run the specs built during the make process:
```sh
./spec/libmanabu_spec --log-level=all
```

Windows
=======
We recommend you compile on MSYS2 on Windows. Assuming you have MSYS2, you'll need to 
install Boost, CURL, and OpenSSL. You can do most of this with the following command: 
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

Building
--------
Assuming you have everything installed and ready, compiling libmanabu is a fairly 
standard CMake procedure:
```sh
mkdir build
cd build
cmake ..
make
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
