#Learning CMake

## Introductions

http://www2.informatik.uni-freiburg.de/~jakobro/files/cmake-an-introduction.pdf

##General steps (for Mac OS X only):

###1. Download and Install CMake
  * download CMake from the CMake [download page](https://cmake.org/download/). In this particular example, would be the *"cmake-3.5.2-Darwin-x86_64.dmg"* file for Mac.

  * launch the installer by double-clicking on the *.dmg* file, then drag&drop the CMake logo onto the Applications folder image to install it ( quick'n easy! ).
  * Once installed, launch CMake ( for example, from Spotlight, etc ).

  * :heavy_exclamation_mark:**Add CMake to path**: From the **"Tools"** menu select **"How to Install For Command Line Use"**. From the popup dialog box, note the cmake-gui path—which in our case: `/Applications/CMake.app/Contents/bin/cmake-gui`

    :heavy_exclamation_mark:**Open your Terminal and type the following**:
    ```
    sudo mkdir -p /usr/local/bin
    sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
    ```
    Verify that CMake has been correctly installed to PATH:
    ```
    cmake --version
    ```
    If it's correct, it will show you the CMake version 3.5.2 ( in our case )

###2. Build Up Your First C++ Project ( we'll do this in Terminal—no worries… )
  * In your Terminal, switch your path to "Desktop" by entering the following:
  `cd ~/Desktop`. ( instead of "Desktop" you can of course chose anywhere else to follow alone, as long as you can easily find and access all of your files once they've been created. )
  * The following one-liner command will creat an empty directory, give it a name: "myTest" ( or anything you like ), and switch into it. Type:

  ```
  mkdir myTest && cd $_
  ```

  * Creat two empty files by typing **exactly** the following code:
  ```
  touch main.cpp CMakeLists.txt
  ```
  * Now go and open up the **main.cpp** in your favorite text editor ( but don't close the Terminal just yet! We'll need to come back later… ), write or copy&paste the following code—a very simple trivial program in C++:
  ```cpp
  // This program outputs the message "Hello World!"

  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <fstream>

  using namespace std;

  int main() 
  {
    cout << "Hello World!\n";    
    return 0;
  }

  ```

  * Open the other empty file CMakeLists.txt and write or copy&paste the following plain text:
  ```
  cmake_minimum_required(VERSION 2.6)
  project(helloWorld)
  
  add_definitions("-std=c++11")
  add_executable(helloWorld main.cpp)
  
  target_link_libraries(helloWorld)
  ```
  ######Notice that the "helloWorld" in the code above is the project name we've defined in the "CMakeLists.txt" file, it can be anything else but it must be consistently the same! This is important as you will see later on.

###3. Let CMake Build Everything for Us
  * Save and close both "main.cpp" and "CMakeLists.txt" files. Back to your Terminal, creat and jump into an empty subdirectory with the name "build". Type:

  ```
  mkdir build && cd $_
  ```
  * Now type the following command:

  ```
  cmake ..
  ```
  * … and when it's done, enter another command (  i.e. finally to build ):

  ```
  make
  ```

(If everything goes well, you should see a line like `[100%] Built target helloWorld` at the end of the output! I keep my finger crossed for you…)

###4. Run Our first C++!!

Finally enter the CMake command to run main.cpp:

```
./helloWorld
```
**Here! "helloWorld" is exactly the name we've given to our project and defined in the CMakeLists.txt file.**

#"Congrats!"



~~Our session of November will be / has been about cmake.~~

Official [CMake Tutorial](https://cmake.org/cmake-tutorial/) pages. 

