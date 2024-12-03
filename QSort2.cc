#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <cstdint>
#include <utility>
#include <cassert>

namespace {

    using Container_t = std::vector<std::uint32_t>;

    std::pair<Container_t, Container_t> split(const Container_t& container)
    {
        Container_t smaller;
        Container_t bigger;
        const auto pivot = container.front();
        const auto isSmaller = [pivot](const std::uint32_t elem){
            return elem < pivot;    
        };
        std::copy_if(container.begin() + 1, container.end(), back_inserter(smaller), isSmaller);
        const auto isNotSmaller = [pivot](const std::uint32_t elem){  
            return elem >= pivot;
        };
        std::copy_if(container.begin() + 1, container.end(), back_inserter(bigger), isNotSmaller);

        if (smaller.empty())
        {
            smaller.push_back(pivot);
        }
        else if (bigger.empty())
        {
            bigger.push_back(pivot);
        }
        else
        {
            bigger.insert(bigger.begin(), pivot);
        }

        return {smaller, bigger};
    }

    Container_t qsort(const Container_t& container) 
    {
        static std::uint32_t safety{0u};
        assert(++safety < 1000u and "Probable infinite recursion");
        if (container.size() < 2u)
        {
            return container;
        }

        auto [smaller, bigger] = split(container);
        
        auto smaller_sorted = qsort(smaller);
        const auto bigger_sorted = qsort(bigger);
        smaller_sorted.insert(smaller_sorted.end(), bigger_sorted.begin(), bigger_sorted.end());
        return smaller_sorted;
    }

    size_t split(std::uint32_t numbers[], size_t begin, size_t end)
    {
        assert(begin != end);
        const auto pivot{numbers[0]};
        size_t low = begin;
        for(; low < end; ++low)
        {
            if (numbers[low] >= pivot)
            {
                //we found something to swap
            }
        }
        size_t high = end - 1;
        for(size_t high = end - 1; high > begin; --high)
        {
            if (numbers[high] < pivot)
            {
                //we found something to swap
            }
        }
        if (low < high)
        {
            std::swap(numbers[low], numbers[high]);
        }
        return low;
    }

    void qsort(std::uint32_t numbers[], size_t begin, size_t end)
    {
        static std::uint32_t safety{0u};
        assert(++safety < 1000u and "Probable infinite recursion");

        if ((end - begin) < 2u)
        {
            return;
        }

        const auto middlePos = split(numbers, begin, end);
        qsort(numbers, begin, middlePos);
        qsort(numbers + middlePos, middlePos, end);
    }

class SplitTest : public testing::TestWithParam<std::tuple<Container_t, std::pair<Container_t, Container_t>>>
{
public:
    const Container_t& getInput() const
    {
        return std::get<0>(GetParam());
    }

    const Container_t& getExpectedSmaller() const
    {
        return std::get<1>(GetParam()).first;
    }

    const Container_t& getExpectedBigger() const
    {
        return std::get<1>(GetParam()).second;
    }
};

TEST_P(SplitTest, verify)
{
    const auto [smaller, bigger] = split(getInput());
    EXPECT_THAT(smaller, testing::UnorderedElementsAreArray(getExpectedSmaller()));
    EXPECT_THAT(bigger, testing::UnorderedElementsAreArray(getExpectedBigger()));
}

const std::vector<std::tuple<Container_t, std::pair<Container_t, Container_t>>> toSplit{
    {Container_t{4, 3, 2, 1}, {Container_t{1, 2, 3}, Container_t{4}}},
    {Container_t{1, 2, 3, 4}, {Container_t{1}, Container_t{2, 3, 4}}},
    {Container_t{4, 4, 4, 4}, {Container_t{4}, Container_t{4, 4, 4}}}};

INSTANTIATE_TEST_SUITE_P(t,
                        SplitTest,
                        testing::ValuesIn(toSplit));

class QSortTest : public testing::TestWithParam<std::tuple<Container_t, Container_t>>
{
public:
    const Container_t& getInput() const
    {
        return std::get<0>(GetParam());
    }

    const Container_t& getSorted() const
    {
        return std::get<1>(GetParam());
    }
};

TEST_P(QSortTest, verifyProperSorting)
{
    ASSERT_EQ(getSorted(), qsort(getInput()));
}
}

const std::vector<std::tuple<Container_t, Container_t>> toSort{
    {Container_t{4, 3, 2, 1}, Container_t{1, 2, 3, 4}},
    {Container_t{1, 2, 3, 4}, Container_t{1, 2, 3, 4}},
    {Container_t{4, 4, 4, 1}, Container_t{1, 4, 4, 4}}};
INSTANTIATE_TEST_SUITE_P(t,
                        QSortTest,
                        testing::ValuesIn(toSort));

TEST(QSortInPlace, verify)
{
    std::uint32_t descendingNumbers[]{4, 3, 2, 1};
    qsort(descendingNumbers, 0u, 4u);
    std::uint32_t sortedNumbers[]{1, 2, 3, 4};
    for(size_t i = 0u; i<4u; ++i)
    {
        EXPECT_EQ(sortedNumbers[i], descendingNumbers[i]);
    }
}