
#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observable.h"

class Subject : public Observable
{
private:
    int myStateX;

public:
    explicit Subject(int initialState = 0);

    /**
     * @brief setState member param accessor
     * @param newValue the value to set
     */
    void setStateX(int newValue);
    /**
     * @brief notifyStateX notification loop for myStateX
     */
    void notifyStateX();
};

#endif // SUBJECT_H
