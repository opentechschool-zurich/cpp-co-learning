//  g++ -O2 -o alignas alignas.cpp && ./alignas | grep -v Ignore
//  g++ -O3 -o alignas alignas.cpp && ./alignas | grep -v Ignore
//  g++ -O3 -o alignas -march=native alignas.cpp  && ./alignas | grep -v Ignore
//  clang++ -O2 -o alignas alignas.cpp && ./alignas | grep -v Ignore
//  clang++ -O3 -o alignas alignas.cpp && ./alignas | grep -v Ignore
//  clang++ -O3 -o alignas -march=native alignas.cpp && ./alignas | grep -v Ignore

#include <sys/time.h>
#include <iostream>
#include <vector>

using namespace std;

class WallClockTimer {
public:
    struct timeval t1, t2;
    WallClockTimer() :
        t1(), t2() {
        gettimeofday(&t1, 0);
        t2 = t1;
    }
    void reset() {
        gettimeofday(&t1, 0);
        t2 = t1;
    }
    int elapsed() {
        return (t2.tv_sec * 1000 + t2.tv_usec / 1000) - (t1.tv_sec * 1000 + t1.tv_usec / 1000);
    }
    int split() {
        gettimeofday(&t2, 0);
        return elapsed();
    }
};

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

template <class T>
void busywork() {
    int manytimes { 400000000 };
    WallClockTimer timer;
    T object;
    for ( int i=0; i<manytimes; ++i) {
        object.a += object.b;
        ++object.b;
    }
    // prevent optimiser from deleting vars
    std::cout << "Ignore this: " << object.a << object.b << std::endl;
    std::cout << "Time: " << timer.split() << " sizeof: " << sizeof(object) << std::endl;
}
 

int main() {
    std::cout << "Unaligned (Object sizeof: "<< sizeof(UnalignedClass) << ')' << std::endl;
    for (int i = 0; i <10; ++i) { 
        cout << "Run: " << i;
        busywork<UnalignedClass>();
    }
    std::cout << "\nAligned (Object sizeof: "<< sizeof(AlignedClass) << ')' << std::endl;
    for (int i = 0; i <10; ++i) { 
        busywork<AlignedClass>();
    }
}