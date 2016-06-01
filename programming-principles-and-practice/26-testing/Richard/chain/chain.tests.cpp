#include "chain.h"
#include <gmock/gmock.h>

using namespace ::testing;

using namespace ::testing;

TEST(Chain, chaining_lambdas_works)
{
    auto fn1_called = false;
    auto fn2_called = false;
    auto fn1 = [&] { fn1_called = true; };
    auto fn2 = [&] { fn2_called = true; };

    auto fn = chain(fn1, fn2);
    ASSERT_THAT(fn1_called, Eq(false));
    ASSERT_THAT(fn2_called, Eq(false));
    fn();
    ASSERT_THAT(fn1_called, Eq(true));
    ASSERT_THAT(fn2_called, Eq(true));
}

struct Functor {
    Functor(bool& called)
        : m_called(called)
    {
    }

    void operator()() const {
        m_called = true;
    }

    bool& m_called;
};

TEST(Chain, chaining_functors_works)
{
    auto fn1_called = false;
    auto fn2_called = false;
    auto fn1 = Functor{fn1_called};
    auto fn2 = Functor{fn2_called};

    auto fn = chain(fn1, fn2);
    ASSERT_THAT(fn1_called, Eq(false));
    ASSERT_THAT(fn2_called, Eq(false));
    fn();
    ASSERT_THAT(fn1_called, Eq(true));
    ASSERT_THAT(fn2_called, Eq(true));
}

size_t global_counter = 0;

void counting_fn() {
    ++global_counter;
}

TEST(Chain, chaining_plain_functions_works)
{
    auto previous = global_counter;

    auto fn = chain(counting_fn, counting_fn);
    ASSERT_THAT(global_counter, Eq(previous));
    fn();
    ASSERT_THAT(global_counter, Eq(previous + 2));
}
