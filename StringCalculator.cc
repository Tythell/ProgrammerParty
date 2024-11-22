/*
Problem: String Calculator
Description: Implement a simple string calculator that can take in a comma-separated list of numbers and return their sum.
 
For example:
The input "" (an empty string) should return 0.
The input "1,2,5" should return 8.
You may also support custom delimiters, so “//;\n1;2;3” should return 6, where the ; delimiter is specified at the beginning.

Requirements:
An empty string returns 0.
A single number returns the value itself.
Two numbers separated by a comma return their sum.
Allow the addition of an arbitrary number of numbers.
Support custom delimiters, which are specified in the format //[delimiter]\n[numbers…].
Bonus Features (optional):
Handle Negative Numbers: If the string contains any negative numbers, throw an exception with a message listing all negative numbers found.
Ignore Numbers Greater than 1000: For instance, “2,1001,6” should return 8
*/

//Please implement c++17 code to fulfill this unit test!

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <vector>

#include <iostream>

// Helper function to join elements of a vector into a single string
std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << delimiter;
        }
    }
    return oss.str();
}

// Function to implement
int calculate(const std::string& input) {
    if (input.empty()) {
        return 0; // Return 0 if the input is an empty string
    }

    // Check for custom delimiter pattern: "//<delimiter>\n"
    if (input.size() > 3u && input.substr(0, 2) == "//") {
        const auto delimiter_end_pos = input.find('\n', 2); // Find the position of the newline after the delimiter
        if (delimiter_end_pos != std::string::npos) {
            const auto delimiter = input.substr(2, delimiter_end_pos - 2); // Extract delimiter
            auto numbers = input.substr(delimiter_end_pos + 1); // Extract numbers part

            if (numbers.empty()) {
                return 0; // If no numbers are provided after the delimiter, return 0
            }

            // Replace the custom delimiter with a comma for splitting
            size_t pos = 0;
            while ((pos = numbers.find(delimiter, pos)) != std::string::npos) {
                numbers.replace(pos, delimiter.length(), ","); // Replace delimiter with commas
                pos += delimiter.length();
            }

            return calculate(numbers); // Recursively calculate with replaced delimiters
        }
    }

    // Validate input for invalid characters and numbers
    for (char ch : input) {
        if (!std::isdigit(ch) && ch != ',' && ch != '-') {
            std::cout << "Invalid character[" << ch << "] was found" << std::endl;
            return 0; // Stop processing and return 0 if invalid character is found
        }
    }

    // Process numbers separated by commas and calculate their sum
    std::stringstream ss(input);
    std::string token;
    int sum = 0;
    std::vector<std::string> negativeNumbers;

    while (std::getline(ss, token, ',')) {
        try {
            int number = std::stoi(token); // Convert each token to an integer
            if (number < 0) {
                negativeNumbers.push_back(token); // Collect negative numbers
            } else if (number <= 1000) {          // Ignore numbers greater than 1000
                sum += number;
            }
        } catch (...) {
            std::cout << "token [" << token << "] is not a number" << std::endl;

            return 0; // Return 0 if conversion fails
        }
    }

    if (!negativeNumbers.empty()) {
        throw std::invalid_argument("Negative numbers not allowed: " + join(negativeNumbers, ", "));
    }

    return sum;
}

TEST(StringCalculatorTest, verifyEmptyStringReturnsZero)
{
    EXPECT_EQ(0, calculate(""));
}

TEST(StringCalculatorTest, verifyDelimiter) {
    // Delimiters must be followed by numbers. This test ensures empty numbers after the delimiter will return 0.
    EXPECT_EQ(0, calculate("//;\n"));
}

TEST(StringCalculatorTest, singularNumberReturnsNumber)
{
    EXPECT_EQ(1, calculate("1"));
}

TEST(StringCalculatorTest, invalidCharacterShouldStopProcessingTheString)
{
    EXPECT_EQ(0, calculate("n1")); // Invalid character in the input string
    EXPECT_EQ(0, calculate("1n1")); // Invalid character in the input string
}

TEST(StringCalculatorTest, shouldNumbersSummarized)
{
    EXPECT_EQ(7, calculate("3,4"));
    EXPECT_EQ(13, calculate("3,4,1,2,3"));
}

TEST(StringCalculatorTest, verifyNumbersWithMultipleDigits)
{
    EXPECT_EQ(22, calculate("10,12"));
}

TEST(StringCalculatorTest, numberGreaterThan1000Ignore){
    EXPECT_EQ(1012, calculate("1,2000,5,1000,1001,6"));
}

TEST(StringCalculatorTest, verifyCustomDelimiters)
{
    EXPECT_EQ(6, calculate("//f\n1f2f3"));
    EXPECT_EQ(6, calculate("//;\n1;2;3"));
    EXPECT_EQ(6, calculate("//kamuhab\n1kamuhab2kamuhab3"));
}

TEST(StringCalculatorTest, verifyDelimiterWithoutNumber)
{
    EXPECT_EQ(0, calculate("//kamuhab\n"));
}

TEST(StringCalculatorTest, verifyTheNegativeNumbersThrow)
{
    try {
        calculate("-1,-12,23");
        FAIL() << "Expected exception not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Negative numbers not allowed: -1, -12", e.what());
    }
}
