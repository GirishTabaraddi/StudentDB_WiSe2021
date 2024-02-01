/*!
 * @file helperFunctions.h
 *
 * \n Created on: 11-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>

#include <Poco/DateTimeFormatter.h>
#include <Poco/Data/Date.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeParser.h>
#include <Poco/Timestamp.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Timespan.h>
#include <Poco/JSON/Object.h>
#include <Poco/DynamicStruct.h>
#include <Poco/UTFString.h>

#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>

/*!
 * @brief Converts Poco::Data::Date to a formatted string.
 *
 * @param date Poco::Data::Date object to be converted.
 * @return std::string representing the formatted date.
 */
std::string pocoDateToStringFormatter(const Poco::Data::Date &date);

/*!
 * @brief Converts a string to Poco::Data::Date.
 *
 * @param stringDate std::string containing the date to be converted.
 * @return Poco::Data::Date representing the parsed date.
 */
Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate);

/*!
 * @brief Converts Poco::Data::Time to a formatted string.
 *
 * @param time Poco::Data::Time object to be converted.
 * @return std::string representing the formatted time.
 */
std::string pocoTimeToStringFormatter(const Poco::Data::Time &time);

/*!
 * @brief Converts a string to Poco::Data::Time.
 *
 * @param stringTime std::string containing the time to be converted.
 * @return Poco::Data::Time representing the parsed time.
 */
Poco::Data::Time stringToPocoTimeFormatter(const std::string& stringTime);

/*!
 * @brief Converts a string representation of a day to Poco::DateTime::DaysOfWeek.
 *
 * @param dayString std::string containing the day to be converted.
 * @return Poco::DateTime::DaysOfWeek representing the parsed day of the week.
 */
Poco::DateTime::DaysOfWeek getDayOfWeekFromString(const std::string& dayString);

/*!
 * @brief Split the input string at the specified delimiter.
 *
 * This function takes an input string and splits it at the specified delimiter.
 * It returns the portion of the string before the delimiter, and modifies the input
 * string to contain the remaining portion after the delimiter.
 *
 * @param remainder The input string to be split, modified to contain the remaining portion.
 * @param delimiter The character at which to split the input string.
 * @return The portion of the string before the delimiter.
 */
std::string splitAt(std::string& remainder, char delimiter);

/**
 * @brief Get user input based on a specified prompt and input pattern.
 *
 * This function prompts the user with the provided message, retrieves user input,
 * and validates it against the specified input pattern. The result is stored in the
 * provided string reference.
 *
 * @param prompt The message prompt displayed to the user.
 * @param inputPattern The regular expression pattern for validating user input.
 * @param userInput Reference to store the user input.
 */
void getUserInput(const std::string& prompt, const std::string& inputPattern,
                  std::string& userInput);

/**
 * @brief Assert the truth of a condition and display a message on failure.
 *
 * This function checks the specified condition and displays the provided message
 * if the condition is false.
 *
 * @param condition The condition to check for truth.
 * @param failedMessage The message to display if the condition is false.
 */
void assertTrue(bool condition, std::string failedMessage);

///*!
// * @brief Checks if the given input is a valid integer.
// *
// * @param input The input string to be checked.
// * @return True if the input is a valid integer; otherwise, false.
// */
//bool integerInputCheck(std::string& input);
//
///*!
// * @brief Checks if the given input is a valid string.
// *
// * @param input The input string to be checked.
// * @return True if the input is a valid string; otherwise, false.
// */
//bool stringInputCheck(std::string& input);
//
///*!
// * @brief Checks if the given input is a valid floating-point number.
// *
// * @param input The input string to be checked.
// * @return True if the input is a valid floating-point number; otherwise, false.
// */
//bool floatInputCheck(std::string& input);
//
///*!
// * @brief Checks if the given string is a valid filename.
// *
// * @param filename The string to be checked as a filename.
// * @return True if the input is a valid filename; otherwise, false.
// */
//bool isValidFilename(const std::string& filename);
//
///*!
// * @brief Checks if the given input consists of printable characters.
// *
// * @param input The input string to be checked.
// * @return True if the input consists of printable characters; otherwise, false.
// */
//bool isPrintableInput(std::string& input);

#endif /* HELPERFUNCTIONS_H_ */
