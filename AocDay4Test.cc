#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

/*
Exercise suggestion for programming practice tomorrow
 
Taken from Advent of Code 2024 Day4 
 
Tl;dr: Given a multilined input text (consisting of 'X', 'M', 'A' and 'S') 
Find and count the occurrences of the word "XMAS" in 
all 8 directions: Right, Left, Up, Down, and diagonals: Up Left, Up Right, Down Left and Down Right 

and count the number of occurrences
 
Lore text here:S
*/

uint32_t FindXLength(const std::string& buffer)
{
    auto xLen = buffer.find('\n');
    if(xLen == std::string::npos)
    {
        return buffer.size();
    }
    else
    {
        return xLen + 1;
    }
}

TEST(FindXLengthTest, verifySingleline)
{
    EXPECT_EQ(7u, FindXLength("kamuhab"));
}

TEST(FindXLengthTest, verifyMutliline)
{
    EXPECT_EQ(8u, FindXLength("kamuhab\nkamuhab"));
}

uint32_t ConvertXYCoordToIndex(const std::string& buffer, uint32_t x, uint32_t y)
{
//    x + (y*xLen)
    const auto xLen = FindXLength(buffer);
    return xLen * y + x;
}



std::pair<uint32_t, uint32_t> ConvertIndexToXY(const std::string& input, uint32_t index)
{
    const auto xLen = FindXLength(input);
    assert(xLen > 0);
    const auto y = index / xLen;
    const auto x = (index % xLen);
    return std::make_pair(x,y);
}

TEST(ConvertCoordTest, verify)
{
    constexpr auto input = "kamuhab";
    EXPECT_EQ(3u, ConvertXYCoordToIndex(input, 3u, 0u));
}

TEST(ConvertCoordTest, verifyConvertIndexToXYSingleLine)
{
    constexpr auto input = "kamuhab";
    const auto [x, y] = ConvertIndexToXY(input, 3u);
    EXPECT_EQ(3, x);
    EXPECT_EQ(0, y);
}

TEST(ConvertCoordTest, verifyConvertIndexToXY)
{
    constexpr auto input = "kamuhab\nkamuhab";
    const auto [x, y] = ConvertIndexToXY(input, 9u);
    EXPECT_EQ(0, x);
    EXPECT_EQ(1, y);
}

TEST(ConvertCoordTest, verifyConvertVicaVersa)
{
    constexpr auto input = "kamuhab\nkamuhab";
    const auto [x, y] = ConvertIndexToXY(input, 9u);
    EXPECT_EQ(9u, ConvertXYCoordToIndex(input, x, y));
}

TEST(ConvertCoordTest, verifyIndexToCoordMultipleLines)
{
    constexpr auto input = 
                      "MMMSXXMASM\n"
                      "MSAMXMSMSA\n"
                      "AMXSXMAAMM\n"
                      "MSAMASMSMX\n"
                      "XMASAMXAMM\n"
                      "XXAMMXXAMA\n"
                      "SMSMSASXSS\n"
                      "SAXAMASAAA\n"
                      "MAMMMXMMMM\n"
                      "MXMXAXMASX";
    const auto [x, y] = ConvertIndexToXY(input, 35u);
    EXPECT_EQ(2, x);
    EXPECT_EQ(3, y);
}


TEST(ConvertCoordTest, verifyMultipleLines)
{
    constexpr auto input = 
                      "MMMSXXMASM\n"
                      "MSAMXMSMSA\n"
                      "AMXSXMAAMM\n"
                      "MSAMASMSMX\n"
                      "XMASAMXAMM\n"
                      "XXAMMXXAMA\n"
                      "SMSMSASXSS\n"
                      "SAXAMASAAA\n"
                      "MAMMMXMMMM\n"
                      "MXMXAXMASX";
    EXPECT_EQ(36u, ConvertXYCoordToIndex(input, 3u, 3u));
}

// uint8_t NextLetterDown(const std::string& input, int32_t currentXPos, int32_t currentYPos)
// {
//     std::vector<std::string> bufferMap;
//     std::stringstream ss(input);

//     std::string line;
//     while (std::getline(ss, line))
//     {
//         bufferMap.emplace_back(line);
//     }
    

// }

uint32_t countWordDownward(const std::string& input, const std::string& word)
{
    return 0;
    const auto lineLength = input.find('\n');
    if (lineLength == std::string::npos)
    {
        return 0u;
    }

    size_t pos = input.find(word[0u]);
    while (pos < input.size() - (3 * lineLength))
    {
        //Convert pos to 2d coordinate (x,y)
        // From (x,y) find letter index of (x,y+1) (x,y+2) and (x,y+3)
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
    constexpr auto INPUT = 
                      "MMMSXXMASM\n"
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

TEST(Day4Test, DISABLED_guidingTC) {
    constexpr auto input = "S..S..S\n"
                           ".A.A.A.\n"
                           "..MMM..\n"
                           "SAMXMAS\n"
                           "..MMM..\n"
                           ".A.A.A.\n"
                           "S..S..S";
    
    ASSERT_EQ(8, countXmas(input));
}

