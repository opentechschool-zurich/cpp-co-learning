# Creating a Simple FLTK-Graph on Linux (Debian) in Nine Easy Steps

Thanks to Ale for providing the much improved collection of graphics
files. I tested my procedure on Debian and I still had to comment the
following lines in `Graph.cpp` to make it work
```
    // case Suffix::jpg:
	// 	p = new Fl_JPEG_Image(s.c_str());
	// 	break;
	// case Suffix::gif:
	// 	p = new Fl_GIF_Image(s.c_str());
```
I do not know why I had to do this... (any ideas?) Anyway, in this
version of the support - files, it is commented out. 


1. Install FLTK with your package manager. In Debian, this is done by:

        sudo apt-get install libfltk1.3-dev

2. Save all files in *this* directory in some directory such as
   `<exampledir>`.

3. Check out the path to the FLTK - files. These are files starting
   with *FL*. In Debian, this is directory is `<fltk-path> =
   /usr/include/FL`.

4. In `<exampledir>`, create links to the FLTK-files:

        ```
        ln -s <fltk-path> FL
        ln -s <fltk-path> Fl
        ```

5. Link your cpp-files with 

        g++ -c -std=c++11 GUI.cpp Graph.cpp Window.cpp Simple_window.cpp

6. Create the file `<main.cpp>` in a directory `<maindir>` of your
   choice which contains Bjarne's code to paint the polygon. 

7. Be careful to set the include-directives correctly in
   `<main.cpp>`: 

    ```
    #include "path/to/Simple_window.h"
    #include "path/to/Graph.h"
    ... and so on ...
    ```

8. Change directory to `<exampledir>`, compile with

    ```
    g++ -std=c++11 -o cute.prg Window.o Simple_window.o Graph.o GUI.o
    path/to/<maindir>/<main.cpp> -lfltk 
    ```
    In my case, this was
    ```
    g++ -std=c++11 -o first.prg Window.o Simple_window.o Graph.o GUI.o
    ../Kapitel12/drill/firstexample.cpp -lfltk 
    ```

9. Check whether it works with `./cute.prg`.

