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

Linux Build Notes
-----------------
There are no particular build notes for Linux other than that you will need to install 
CMake, Boost development libraries, OpenSSL development libraries, and msgpack-c.


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
