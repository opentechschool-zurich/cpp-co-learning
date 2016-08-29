# Threads

Note in the CMakesLists.txt how we have two lines to enable threads in the
compiled result:

```
find_package (Threads)
target_link_libraries(YesNoThreads ${CMAKE_THREAD_LIBS_INIT})
```

## YesNoThreads

The program has issues: It doesn't have any synchronisation on the cout
instruction and some lines are intermingled:

### Output:

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


# Escalator problem

## Same as Unisex Toilet problem or Unisex shower problem

We have a Mall with two escalator where one is undergoing maintenance.
People arrive on threads and want to go up or down. If nobody is on the
escalator they are allowed to set the direction and step on. They stay
varying amounts of time on the escalator: Some just step on and wait till
they reach the other end. Others walk thereby reducing the time spent. Some
children walk in the other direction and take longer. There is only space for
3 people to be on the escalator at any time. People wanting to go in the other
direction must wait till nobody is on the elevator before they can change
the direction. If 3 people are on the escalator people need to wait before
someone steps off before they are allowed to step on.

The key functionality is happening in the Escalator class:

```cpp
Direction escalatorDirection = Direction::idle;
std::mutex mtx;
std::condition_variable cv;

/**
* any thread can request a person to ride the escalator
*/
auto ride(Person p) -> void {
  p.describe();

  { // block to ensure the lock is unlocked event when an exception occurs
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [this, p] {
      return (nPersons < 3 && escalatorDirection == p.intendedDirection) ||
             nPersons == 0;
    });
    hopOn(p);
  }
  cv.notify_all();
  usleep(800000);
  stepOff(p);
  cv.notify_all();
}
```

When a person wants to ride the escalator they use the condition_variable to
wait on the lock and atomically check and set the conditions. When something
relevant changed the notify_all is called which tells all waiting threads to
go and have a look at the condition and run if OK.

### Output
```
> ./escalator.prg
Escalator going idle with 0 aboard.
Person 1 wants to ride the escalator up
Person 1 hops on the escalator
Person 1 is changing the direction from idle to up
Escalator going up with 1 aboard.
        Person 2 wants to ride the escalator up
        Person 2 hops on the escalator
        Escalator going up with 2 aboard.
                Person 3 wants to ride the escalator up
                Person 3 hops on the escalator
                Escalator going up with 3 aboard.
                        Person 4 wants to ride the escalator down
Person 1 steps off the escalator
Escalator going up with 2 aboard.
                                Person 5 wants to ride the escalator up
                                Person 5 hops on the escalator
                                Escalator going up with 3 aboard.
        Person 2 steps off the escalator
        Escalator going up with 2 aboard.
                                        Person 6 wants to ride the escalator down
                Person 3 steps off the escalator
                Escalator going up with 1 aboard.
                                                Person 7 wants to ride the escalator down
                                                        Person 8 wants to ride the escalator up
                                                        Person 8 hops on the escalator
                                                        Escalator going up with 2 aboard.
                                Person 5 steps off the escalator
                                Escalator going up with 1 aboard.
                                                                Person 9 wants to ride the escalator down
                                                        Person 8 steps off the escalator
                                                        Escalator going up with 0 aboard.
                        Person 4 hops on the escalator
                        Person 4 is changing the direction from up to down
                        Escalator going down with 1 aboard.
                                        Person 6 hops on the escalator
                                        Escalator going down with 2 aboard.
                                                Person 7 hops on the escalator
                                                Escalator going down with 3 aboard.
                        Person 4 steps off the escalator
                                        Person 6 steps off the escalator
                                        Escalator going down with 1 aboard.
                        Escalator going down with 2 aboard.
                                                                Person 9 hops on the escalator
                                                Person 7 steps off the escalator
                                                                Escalator going down with 2 aboard.
                                                Escalator going down with 1 aboard.
                                                                Person 9 steps off the escalator
                                                                Escalator going down with 0 aboard.
Time ran out.
```
