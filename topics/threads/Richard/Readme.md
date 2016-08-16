# Threads

Note in the CMakesLists.txt how we have two lines to enable threads in the
compiled result:

```
find_package (Threads)
target_link_libraries(YesNoThreads ${CMAKE_THREAD_LIBS_INIT})
```

The program has issues: It doesn't have any synchronisation on the cout
instruction and some lines are intermingled:

#Output:

```
./YesNoThreads
No (Yes (1)1)    // example of intermingling

Yes (2)
No (2)
No (3)
No (4)
Yes (3)
Yes (4)
No (5)
No (6)
No (7)
Yes (5)
Yes (6)
No (8)
Yes (7)
No (9)
Yes (8)
Yes (9)
```
