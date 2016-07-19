#ifndef DATAPOINTS_H
#define DATAPOINTS_H

#include <vector>

using namespace std;

class Datapoints
{
    public:
        Datapoints();
        int get(int i);
        void set(int i, int value);
        int size() {return datapoints.size();}
    private:
        vector<int> datapoints;
};

#endif
