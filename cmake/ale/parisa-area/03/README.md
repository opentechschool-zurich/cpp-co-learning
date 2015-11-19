# Getting the full `main.cpp` to compile

Now, all the function in the original `main.cpp` compile and run!

My first try at a self made `CMakeFiles.txt` seems to be working!

The best way to compile is:

~~~
cd ale/03/
mkdir build
cd build
cmake ..
make
./Area
~~~

p.s.: `.hpp` files that do not have a matching `.cpp` are simply included as is and do not have to be added to the `CMakeFiles.txt` file.
