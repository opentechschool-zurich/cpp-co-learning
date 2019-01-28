# Does alignas work?

As per the chapter "Controlling and querying object alignment" (Page 27) in the book "Modern C++ Programming" by Marius Bancilla [(link)](https://www.packtpub.com/application-development/modern-c-programming-cookbook) aligning the classes by the cache line size of the processor *can* improve performance.

As per Daniel Lemire's blog post [(link)](https://lemire.me/blog/2012/05/31/data-alignment-for-speed-myth-or-reality) there is no measurable difference.

## What is alignas?

alignsas is a keyword that you can use when defining C++ classes. It tells the compiler to pad the reserved memory to as many bytes as specified in the alignas argument. [(cppreference)](https://en.cppreference.com/w/cpp/language/alignas)

## Let's test it

<<<<<<< HEAD
Look at the code in alignas.cpp in this directory. We have two classes, one which has a "packed" representation of 48 bytes and one with just two ints but aligns to the 64 bit cache line of my available cpus. The program does some pointless calculations many times and outputs the result. (Note: outputting is important because otherwise the optimiser catches on to the fact that the calculations serve no purpose and removes them out of the binary!)
=======
Look at the code in alignas.cpp in this directory. We have two classes, one which has a "packed" representation of 48 bytes and one with just two ints but aligns to the 64 bit cache line of my available cpus. The program does some pointless calculations many times and outputs the result. (Note outputting is important because otherwise the optimiser catches on to the fact that the calculations serve no purpose and removes them out of the binary!)
>>>>>>> b6cb5c570c60046c770d7fdac05b50b5b855964a

```cpp
class UnalignedClass {
    public:
        // total: 48 bytes
        char c1 {'a'};                      // 1 byte + 3 bytes padding
        int a {1};                          // 4 bytes
        std::vector<int> v {5,4,3,2,1,0};   // 6 * 4 bytes
        char c2 {'b'};                      // 1 byte + 3 bytes padding
        int b {2};                          // 4 bytes
        int c {2};                          // 4 bytes
        int d {2};                          // 4 bytes
};

class AlignedClass {
    public:
        // total: 128 bytes
        alignas(64) int a {1};  //64 bytes = cache line of CPU
        alignas(64) int b {2};  //64 bytes = cache line of CPU
};
```

<<<<<<< HEAD
### Results from an Intel(R) Core(TM) i9-8950HK CPU @ 2.90GHz
=======
### Results from a Intel(R) Core(TM) i9-8950HK CPU @ 2.90GHz
>>>>>>> b6cb5c570c60046c770d7fdac05b50b5b855964a

```
Unaligned (Object sizeof: 48)
Time: 24 sizeof: 48
Time: 24 sizeof: 48
Time: 24 sizeof: 48
Time: 23 sizeof: 48
Time: 25 sizeof: 48
Time: 25 sizeof: 48
Time: 23 sizeof: 48
Time: 25 sizeof: 48
Time: 25 sizeof: 48
Time: 24 sizeof: 48

Aligned (Object sizeof: 128)
Time: 13 sizeof: 128
Time: 12 sizeof: 128
Time: 12 sizeof: 128
Time: 13 sizeof: 128
Time: 12 sizeof: 128
Time: 14 sizeof: 128
Time: 13 sizeof: 128
Time: 12 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
```

<<<<<<< HEAD
### Results from an Intel(R) Core(TM) i7-4770K CPU @ 3.50GHz
=======
### Results from a  Intel(R) Core(TM) i7-4770K CPU @ 3.50GHz
>>>>>>> b6cb5c570c60046c770d7fdac05b50b5b855964a

```
Unaligned (Object sizeof: 48)
Time: 26 sizeof: 48
Time: 17 sizeof: 48
Time: 17 sizeof: 48
Time: 16 sizeof: 48
Time: 17 sizeof: 48
Time: 15 sizeof: 48
Time: 16 sizeof: 48
Time: 16 sizeof: 48
Time: 17 sizeof: 48
Time: 16 sizeof: 48

Aligned (Object sizeof: 128)
Time: 26 sizeof: 128
Time: 15 sizeof: 128
Time: 17 sizeof: 128
Time: 14 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 14 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 14 sizeof: 128
```

## Results interpretation

The interesting thing is that after some tweaking of the 'UnalignedClass' I was able to construct something that exhibited a real 2x performance drag on the i9-8950HK CPU. Oddly, the older i7-4770K is unfazed.

The more dramatic thing though, is the effect of the optimizer. A 52x speed increase:

### No optimisation --> 730 ms

```
g++ -o alignas  alignas.cpp  && ./alignas | grep -v Ignore

Unaligned (Object sizeof: 48)
Time: 739 sizeof: 48
Time: 731 sizeof: 48
Time: 737 sizeof: 48
Time: 749 sizeof: 48
Time: 734 sizeof: 48
Time: 737 sizeof: 48
Time: 731 sizeof: 48
Time: 733 sizeof: 48
Time: 736 sizeof: 48
Time: 741 sizeof: 48

Aligned (Object sizeof: 128)
Time: 728 sizeof: 128
Time: 728 sizeof: 128
Time: 725 sizeof: 128
Time: 728 sizeof: 128
Time: 726 sizeof: 128
Time: 727 sizeof: 128
Time: 727 sizeof: 128
Time: 726 sizeof: 128
Time: 726 sizeof: 128
Time: 728 sizeof: 128
```

<<<<<<< HEAD
### Optimize level 2 --> 105 ms
=======
### Optimize level 2 --> 105 ms 
>>>>>>> b6cb5c570c60046c770d7fdac05b50b5b855964a

```
g++ -O2 -o alignas  alignas.cpp  && ./alignas | grep -v Ignore

Unaligned (Object sizeof: 48)
Time: 105 sizeof: 48
Time: 104 sizeof: 48
Time: 107 sizeof: 48
Time: 103 sizeof: 48
Time: 108 sizeof: 48
Time: 106 sizeof: 48
Time: 107 sizeof: 48
Time: 103 sizeof: 48
Time: 105 sizeof: 48
Time: 106 sizeof: 48

Aligned (Object sizeof: 128)
Time: 103 sizeof: 128
Time: 109 sizeof: 128
Time: 109 sizeof: 128
Time: 104 sizeof: 128
Time: 106 sizeof: 128
Time: 106 sizeof: 128
Time: 107 sizeof: 128
Time: 108 sizeof: 128
Time: 109 sizeof: 128
Time: 105 sizeof: 128
```

<<<<<<< HEAD
### Optimize level 3 --> 30 ms
=======
### Optimize level 3 --> 30 ms 
>>>>>>> b6cb5c570c60046c770d7fdac05b50b5b855964a

```
g++ -O3 -o alignas  alignas.cpp  && ./alignas | grep -v Ignore

Unaligned (Object sizeof: 48)
Time: 39 sizeof: 48
Time: 29 sizeof: 48
Time: 28 sizeof: 48
Time: 32 sizeof: 48
Time: 29 sizeof: 48
Time: 32 sizeof: 48
Time: 30 sizeof: 48
Time: 30 sizeof: 48
Time: 29 sizeof: 48
Time: 32 sizeof: 48

Aligned (Object sizeof: 128)
Time: 51 sizeof: 128
Time: 33 sizeof: 128
Time: 26 sizeof: 128
Time: 30 sizeof: 128
Time: 31 sizeof: 128
Time: 29 sizeof: 128
Time: 34 sizeof: 128
Time: 27 sizeof: 128
Time: 27 sizeof: 128
Time: 32 sizeof: 128
```

### Optimize level 3 and specify architecture --> 14 ms 

```
g++ -O3 -march=native -o alignas  alignas.cpp  && ./alignas | grep -v Ignore

Unaligned (Object sizeof: 48)
Time: 14 sizeof: 48
Time: 14 sizeof: 48
Time: 14 sizeof: 48
Time: 14 sizeof: 48
Time: 13 sizeof: 48
Time: 14 sizeof: 48
Time: 14 sizeof: 48
Time: 13 sizeof: 48
Time: 14 sizeof: 48
Time: 14 sizeof: 48

Aligned (Object sizeof: 128)
Time: 25 sizeof: 128
Time: 14 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 14 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 13 sizeof: 128
Time: 14 sizeof: 128
```

## Observations

The test doesn't work with the clang compiler. As soon as you turn on the optimizer the runtime drops to zero. Perhaps clang figures out that the whole loop always returns the same result and calculates that at compile time?

## Conclusion

Whilst the alignas keyword might save the day under very specific circumstances turning on the optimizer flags is likely to have the most impact on making your code fast.

Richard Eigenmann,
28 Jan 2019