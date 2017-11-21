# Graph from links

From Ale's stack of project cards:

Exercise:

Create a program that will create a graph or network from a series of links.

##Implementation
```bash
./graph URL
```

# Example:
```bash
./graph https://richardeigenmann.github.io/simplepage/links.htm
```

##Compiling

Note I have done away with old compilers and outdated standards. This
code is for C++17 and will only compile on up-to-date compilers.

Dependencies:
libxml2
Boost

```bash
cd build
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang ..
make -j2
```

##Visual Studio
```bash
cmake .. -G "Visual Studio 15 Win64"
```

##Webserver
I'm using the simple web server from Ole Christian Eidheim at
https://github.com/eidheim/Simple-Web-Server
Which is licensed under the MIT license.

No: I am using the git submodule way of including it and dependency
management.
I ran
git submodule add https://github.com/eidheim/Simple-Web-Server.git
git submodule init
git submodule update

This affects the entire cpp-co-learning repo so I have copied the header file
only.


##Json
I love Niels Lohmann's Json library. I lifted the file from here:
https://github.com/nlohmann/json
He has licensed it under the MIT license

##D3 visualisation
see https://bl.ocks.org/mbostock/4339083

##Documentation
```bash
mkdir -p build
cd build
doxygen ../Doxyfile
```
