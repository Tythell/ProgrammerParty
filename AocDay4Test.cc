#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <sstream>

/*
Exercise suggestion for programming practice tomorrow
 
Taken from Advent of Code 2024 Day4 
 
Tl;dr: Given a multilined input text (consisting of 'X', 'M', 'A' and 'S') 
Find and count the occurrences of the word "XMAS" in 
all 8 directions: Right, Left, Up, Down, and diagonals: Up Left, Up Right, Down Left and Down Right 

and count the number of occurrences
 
Lore text here:S
*/

uint8_t NextLetterDown(const std::string& input, int32_t currentXPos, int32_t currentYPos)
{
    std::vector<std::string> bufferMap;
    std::stringstream ss(input);

    std::string line;
    while (std::getline(ss, line))
    {
        bufferMap.emplace_back(line);
    }
    

}

uint32_t countWordDownward(const std::string& input, const std::string& word)
{
    const auto lineLength = input.find('\n');
    if (lineLength == std::string::npos)
    {
        return 0u;
    }
    
    size_t pos = input.find(word[0u]);
    while (pos < input.size() - (3 * lineLength))
    {
    find 'X' until end of input
    if input[pos of 'X' + lineLength] == word[0u] and
       input[pos of 'X' + 2 * lineLength] == word[1u] and ...
       count++

    }

}

uint32_t countWord(const std::string& input, const std::string& word)
{
    std::uint32_t count{0u};
    size_t offset = input.find(word);
    while (offset != std::string::npos)
    {
        ++count;
        offset = input.find(word, offset + 4u);
    }
    return count;
}

uint32_t countXmas(const std::string& input) {
    return countWord(input, "XMAS") + 
    countWord(input, "SAMX") + 
    countWordDownward(input, "XMAS") + 
    countWordDownward(input, "SAMX");
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

TEST(Day4Test, twoLinesXmas){
    ASSERT_EQ(2, countXmas("XMAS\nXMAS"));
}

TEST(Day4Test, FiveXMasMultiline){
    ASSERT_EQ(5, countXmas("XMASXMASXMAS\nXMASXMASMMMM"));
}

TEST(Day4Test, xmasBackwards){
    ASSERT_EQ(1, countXmas("SAMX"));
}

TEST(Day4Test, xmasBackwardsForwards){
    ASSERT_EQ(2, countXmas("XMASAMX"));
}

TEST(Day4Test, xmasForwardsBackwards){
    ASSERT_EQ(2, countXmas("SAMXMAS"));
}

TEST(Day4Test, xmasDown) {
    constexpr auto input = "X\n"
                           "M\n"
                           "A\n"
                           "S";
    ASSERT_EQ(1, countXmas(input));
}

TEST(Day4Test, DISABLED_xmasDiagonalDownRight) {
    constexpr auto input = "X...\n"
                           ".M..\n"
                           "..A.\n"
                           "...S";
    ASSERT_EQ(1, countXmas(input));
}

