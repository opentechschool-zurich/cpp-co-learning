/**
 * references:
 * - An empirical study on the impact of C++ lambdas and programmer experience: http://dl.acm.org/citation.cfm?id=2884849&CFID=683385793&CFTOKEN=15520895
 * - HN discussion: https://news.ycombinator.com/item?id=12741229
 */
#include <vector>
#include <iostream>

void naiveProcedural(std::vector<int> v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum;
}

void pureIterator(std::vector<int> v)
{
    float retVal = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        retVal += it->price;
    }
    return retVal;
}

/**
 * no, side effects are not a good idea...
 */
void naiveLambda(std::vector<int> v)
{
    float retVal = 0;
    std::for_each(v.cbegin(), v.cend(), [&](item x) { retVal += item.price; });
    return retVal;
}

void bestIdiomaticLambda(std::vector<int> v)
{
    return std::accumulate(v.cbegin(), v.cend(), 0f,
            [](float acc, item x) { return acc + x.price; });

}


int main()
{
    std::vector<int> v{5,3,4,2};

    std::cout << "naive procedural: " << naiveProcedural(v) std::endl;
    std::cout << "naive iterator: " << naiveProcedural(v) std::endl;
    std::cout << "pureIterator lambda: " << pureIterator(v) std::endl;
    std::cout << "naive lambda: " << naiveLambda(v) std::endl;
    std::cout << "best idiomatic lambda: " << bestIdiomaticLambda() << std::endl;
}
