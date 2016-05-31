#include "dump_list.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(DumpList, dumping_vector_works)
{
    auto vec = std::vector<int>{{1, 2, 3}};

    ASSERT_THAT(dump_list(vec), StrEq("[1, 2, 3]"));
}

TEST(DumpList, dumping_array_works)
{
    auto arr = std::array<int, 3>{{1, 2, 3}};

    ASSERT_THAT(dump_list(arr), StrEq("[1, 2, 3]"));
}
