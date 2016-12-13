# SFML demo with cmake

~~~.sh
$ mkdir build
$ cd build
$ cmake ..
~~~

If cmake does not find the SFML cmake module, you can specify the path in the `cmake` command:

~~~.sh
$ cmake  -DCMAKE_MODULE_PATH=/usr/share/SFML/cmake/Modules/ ..
~~~
