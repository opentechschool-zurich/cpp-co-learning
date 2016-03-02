# Timing a vector vs. a list

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/20-containers-and-iterators/Richard/TimingContainers
mkdir build
cd build
cmake ..
make
./TimingContainers
```

# Results on a 64 bit 8 core Intel i7-4770K processor @ 3.50GHz with 32GB Ram
```
timeAContainer of type vector<int> with 10 elements ran << 0ms per cycle (10 cycles)
timeAContainer of type list<int>   with 10 elements ran << 0ms per cycle (10 cycles)
timeAContainer of type vector<int> with 100 elements ran << 0ms per cycle (10 cycles)
timeAContainer of type list<int>   with 100 elements ran << 0ms per cycle (10 cycles)
timeAContainer of type vector<int> with 1000 elements ran << 0ms per cycle (4 cycles)
timeAContainer of type list<int>   with 1000 elements ran << 3ms per cycle (4 cycles)
timeAContainer of type vector<int> with 10000 elements ran << 5ms per cycle (2 cycles)
timeAContainer of type list<int>   with 10000 elements ran << 598ms per cycle (2 cycles)
timeAContainer of type vector<int> with 50000 elements ran << 82ms per cycle (1 cycles)
timeAContainer of type list<int>   with 50000 elements ran << 28233ms per cycle (1 cycles)
timeAContainer of type vector<int> with 100000 elements ran << 312ms per cycle (1 cycles)
timeAContainer of type list<int>   with 100000 elements ran << 127252ms per cycle (1 cycles)
timeAContainer of type vector<int> with 200000 elements ran << 1234ms per cycle (1 cycles)
timeAContainer of type list<int>   with 200000 elements ran << 832570ms per cycle (1 cycles)
timeAContainer of type vector<int> with 500000 elements ran << 8044ms per cycle (1 cycles)
timeAContainer of type list<int>   with 500000 elements ran << 12849840ms per cycle (1 cycles)
```
