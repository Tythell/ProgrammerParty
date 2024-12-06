#include <gtest/gtest.h>
#include <cstdint>
#include <string>

/*
Exercise suggestion for programming practice tomorrow
 
Taken from Advent of Code 2024 Day4 
 
Tl;dr: Given a multilined input text (consisting of 'X', 'M', 'A' and 'S') 
Find and count the occurrences of the word "XMAS" in 
all 8 directions: Right, Left, Up, Down, and diagonals: Up Left, Up Right, Down Left and Down Right 

and count the number of occurrences
 
Lore text here:S
*/

uint32_t countXmas(const std::string& input) {
    std::uint32_t count{0u};
    size_t offset = input.find("XMAS");
    while (offset != std::string::npos)
    {
        ++count;
        offset = input.find("XMAS", offset + 4u);
    }
    return count;
}

TEST(Day4Test, DISABLED_verify_problem1Solution) {
    constexpr auto INPUT = "MMMSXXMASM\n"
                      "MSAMXMSMSA\n"
                      "AMXSXMAAMM\n"
                      "MSAMASMSMX\n"
                      "XMASAMXAMM\n"
                      "XXAMMXXAMA\n"
                      "SMSMSASXSS\n"
                      "SAXAMASAAA\n"
                      "MAMMMXMMMM\n"
                      "MXMXAXMASX";

    ASSERT_EQ(18u ,countXmas(INPUT));
}

TEST(Day4Test, singleXMAS){

    std::string input = "XMAS";
    EXPECT_EQ(1, countXmas(input));
}

TEST(Day4Test, noXMAS){

    std::string input = "ASJLCNJKLA";
    EXPECT_EQ(0, countXmas(input));
}

TEST(Day4Test, twoXMAS){
    EXPECT_EQ(2, countXmas("XMASXMAS"));
}

