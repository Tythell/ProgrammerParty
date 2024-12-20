#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>

namespace {
    using Rules_t = std::vector<std::pair<std::uint64_t, std::uint64_t>>;
    using Update_t = std::vector<std::uint64_t>;
    using Pages_t = std::vector<Update_t>;

    struct Container_t
    {
        Rules_t rules;
        Pages_t pages;
    };

    Container_t parse()
    {
        std::ifstream file("input5.txt");  // Open the file
        if (!file)
        {
            std::cerr << "Unable to open file" << std::endl;
            throw std::invalid_argument("Unable to open the file");
        }

        Container_t input;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                break;
            }
            std::size_t pos;
            const std::uint64_t before = std::stol(line, &pos);
            const std::uint64_t after = std::stol(line.substr(pos + 1));
            input.rules.emplace_back(before, after);
        }

        while (std::getline(file, line))
        {
            std::istringstream iss(line);

            Update_t pages;
            std::uint64_t page;
            while (iss >> page)
            {
                pages.push_back(page);
            }
            input.pages.push_back(std::move(pages));

        }

        file.close();  // Close the file
        return input;
    }

    struct TestData
    {
        std::uint64_t result;
        Container_t input;
    };

    auto generate(const Rules_t& rules)
    {
        std::map<std::uint64_t, std::pair<std::set<std::uint64_t>,std::set<std::uint64_t>>> rulebook;
        for(const auto& [before, after] : rules)
        {
            rulebook[before].second.insert(after);
            rulebook[after].first.insert(before);
        }
        return rulebook;
    }

    class RightOrderTest : public testing::TestWithParam<TestData>
    {
    public:
        auto getExpected() const
        {
            return GetParam().result;
        }

        const auto& getInput() const
        {
            return GetParam().input;
        }
    };

    class PrintOrderChecker
    {
        public:
        PrintOrderChecker(const Container_t& input) :
            m_pages(input.pages),
            m_rulebook(generate(input.rules))
            {
            }

        std::uint64_t countMiddleInRightOrder()
        {
            Pages_t inRightOrder;
            std::copy_if(m_pages.begin(), m_pages.end(),
                        std::back_inserter(inRightOrder),
                        [this](const auto& update)
                        {
                            return isInRightOrder(update);
                        });
            return std::accumulate(inRightOrder.begin(), inRightOrder.end(), 0u,
                                    [](std::uint64_t sum, const auto& pages)
                                    {
                                        if (pages.empty())
                                        {
                                            return sum;
                                        }
                                        const auto middle = (pages.size() + 1) / 2u - 1u;
                                        return sum + pages[middle];
                                    });
        }

        private:
            bool isInRightOrder(const Update_t& pages)
            {
                for(size_t i = 0u; i < pages.size(); ++i)
                {                    
                    const auto& currentPage = pages[i];
                    if (std::any_of(pages.begin(), pages.begin() + i,
                        [this, currentPage](const auto page)
                        {
                            return m_rulebook[currentPage].second.contains(page);
                        }) or
                        std::any_of(pages.begin() + i + 1, pages.end(),
                        [this, currentPage](const auto page)
                        {
                            return m_rulebook[currentPage].first.contains(page);
                        }))
                    {
                        return false;
                    }
                }
                return true;
            }

        Pages_t m_pages;
        std::map<std::uint64_t, std::pair<std::set<std::uint64_t>,std::set<std::uint64_t>>> m_rulebook;
    };

}

TEST(Day5Test, parse)
{
    const auto input = parse();
    EXPECT_EQ(1176u, input.rules.size());
    EXPECT_EQ(200u, input.pages.size());
    EXPECT_TRUE(std::all_of(input.pages.begin(), input.pages.end(), [](const auto& update) { return update.size() % 2u; }));
}

TEST(Day5Test, firstPuzzle)
{
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "**************************************************************************************" << std::endl;
    PrintOrderChecker checker{parse()};
    std::cout <<checker.countMiddleInRightOrder() << std::endl;
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "**************************************************************************************" << std::endl;
}

TEST_P(RightOrderTest, verify)
{
    PrintOrderChecker checker{getInput()};
    EXPECT_EQ(getExpected(), checker.countMiddleInRightOrder());
}

INSTANTIATE_TEST_CASE_P(t,
RightOrderTest,
::testing::Values(
    TestData{0u, Container_t{Rules_t{{12, 14}},
                             Pages_t()}},
    TestData{14u, Container_t{Rules_t{{12, 14}},
                             Pages_t{{12, 14, 16}}}},
    TestData{13u, Container_t{Rules_t{{12, 14}},
                             Pages_t{{11, 13, 111}}}},
    TestData{13u, Container_t{Rules_t{{12, 14}},
                             Pages_t{{11, 13, 12}}}},
    TestData(143u, Container_t{Rules_t{{47,53},
                                    {97,13},
                                    {97,61},
                                    {97,47},
                                    {75,29},
                                    {61,13},
                                    {75,53},
                                    {29,13},
                                    {97,29},
                                    {53,29},
                                    {61,53},
                                    {97,53},
                                    {61,29},
                                    {47,13},
                                    {75,47},
                                    {97,75},
                                    {47,61},
                                    {75,61},
                                    {47,29},
                                    {75,13},
                                    {53,13}},
                            Pages_t{{75,47,61,53,29},
                                    {97,61,53,29,13},
                                    {75,29,13},
                                    {75,97,47,61,53},
                                    {61,13,29},
                                    {97,13,75,29,47}}})

));
