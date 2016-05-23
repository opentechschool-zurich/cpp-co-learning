#include "memoizer.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(Memoizer, memoizing_with_lambda_works)
{
    size_t amount_of_calls = 0;

    auto expensive_calculation = [&] {
        //track amount of expensive calculations
        ++amount_of_calls;
        return 5; //expensive calculation
    };

    // create memoizer
    auto memoizer = Memoizer<int>{expensive_calculation};

    // memoizer calculates nothing in advance
    ASSERT_THAT(amount_of_calls, Eq(0));

    auto result1 = memoizer.get_value();
    auto result2 = memoizer.get_value();

    ASSERT_THAT(result1, Eq(5));
    ASSERT_THAT(result2, Eq(5));

    // memoizer needs to calculate only once
    ASSERT_THAT(amount_of_calls, Eq(1));
}
