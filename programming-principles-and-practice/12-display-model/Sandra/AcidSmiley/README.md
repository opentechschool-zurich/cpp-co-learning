# Draw an Acid Smiley using FLTK

see the main.cpp file for the source code

There are a couple of Gotchas with this code!
If we have all the Circle and Ellipse variables in main() we can write
the code like this:

```cpp
Graph_lib::Ellipse nose{ Point{ x,y }, 5,20 };
win.attach(nose);
```

But if we take this code to a function we have to consider
the following:

First we have to pass the Simple_window variable by reference 
so that we attach our shapes to the correct window.
Next if we write the code as above the variable "nose" is destroyed
when our function ends; it is only a local variable! Since the FLTK
system only looks for our shapes when we call wait_for_button they are
gone and FLTK draws nothing.

To create the shape objects and keep them around longer than the 
function exists we need to use the "new" keyword. With new we can ask
for an object to be created and we get back a pointer to it's
memory location. We can then attach the object in that memory 
location to the window with the * operator. I.e.

```cpp
Graph_lib::Ellipse *nosePointer = new Graph_lib::Ellipse { Point{ x,y }, 5,20 };
win.attach( *nosePointer );
```
