# The decorator pattern

Give an object responsabibilities wihtout making any code change sto the underlying classes.

Let's have a look to a silly example about selling coffee.  
Or not?

_Open / Closed_: Allow classes to be easily extended to incorporate new behavior without modifiying existing code.

But:  
Be careful when choosing the areas of code that need to be extend: applying the Open-Closed principle everywhere is wasteful, unnecessary, and can lead to complex, hard to understand code.

So:  
Inheritance → Composition
