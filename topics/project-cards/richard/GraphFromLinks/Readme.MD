# Graph from links

From Ale's stack of project cards:

Exercise:

Create a program that will create a graph or network from a series of links.

##Implementation
` ` `bash
./graph depth URL

# Example:
./graph 2 https://richardeigenmann.github.io/simplepage/links.htm
` ` `

##Compiling

Note I have done away with old compilers and outdated standards. This
code is for C++17 and will only compile on up-to-date compilers.

` ` `bash
cd build
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang ..
make -j2
` ` `
