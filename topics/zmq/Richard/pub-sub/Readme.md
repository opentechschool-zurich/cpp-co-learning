# Publish-Subscribe from C++ to Java

This project creates a C++ publisher which constantly pushes out messages that start 
with a three char code.

There is a C++ client that subscribes to messages that start with some codes.

And there is a Java client that subscribes to the messages that start with some 
(other) codes.

To build the C++ part:

```bash
mkdir -p build
cd build
cmake .. 
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CC_COMPILER=/usr/bin/clang .. 
# or cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-6 -DCMAKE_CC_COMPILER=/usr/bin/gcc .. 
make
```

To build the Java part:

```bash
cd ..  #go to the top level directory (where the .java file is)
javac -cp jeromq-0.3.4.jar  javaclient.java
```


Running it all:

It will probably me most illustrative to open 3 command prompt windows.

In the first one run the C++ server:

```bash
build/hwserver
```

In the second one run the C++ client:

```bash
build/hwclient
```

In the third one run the Java client:

```bash
java -cp jeromq-0.3.4.jar:. javaclient
```

Note jeromq is a Java native implementation of the ZeroMQ: https://github.com/zeromq/jeromq
