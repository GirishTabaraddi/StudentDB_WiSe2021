/*!
 * @file Address.h
 *
 * \n Created on: 10-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iostream>

#include "helperFunctions.h"

/*!
 * @class Address
 * @brief Represents an address with specific details.
 */
class Address
{
private:
	/*!
	 * @var m_street - a variable to store the street name.
	 */
	std::string m_street;

	/*!
	 * @var m_postalCode - a variable to store the postal code.
	 */
	unsigned short m_postalCode;

	/*!
	 * @var m_cityName - string variable that stores a city name.
	 */
	std::string m_cityName;

	/*!
	 * @var m_additionalInfo - string variable that stores
	 * additional info on address.
	 */
	std::string m_additionalInfo;

public:
	/*!
	 * @brief Parameterized constructor for Address.
	 *
	 * Initializes all private members of the Address class.
	 *
	 * @param street 			The street address.
	 * @param postalCode 		The postal code.
	 * @param cityName 			The city name.
	 * @param additionalInfo 	Additional information about the address.
	 */
	Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfo);

	/*!
	 * @brief Default destructor for the Address class.
	 */
	virtual ~Address();

	/*!
	 * @brief Getter method for the street address.
	 *
	 * @return const std::string& representing the street address.
	 */
	const std::string& getstreet() const;

	/*!
	 * @brief Getter method for the postal code.
	 *
	 * @return unsigned short representing the postal code.
	 */
	const unsigned short getpostalCode() const;

	/*!
	 * @brief Getter method for the city name.
	 *
	 * @return const std::string& representing the city name.
	 */
	const std::string& getcityName() const;

	/*!
	 * @brief Getter method for additional information about the address.
	 *
	 * @return const std::string& representing additional information.
	 */
	const std::string& getadditionalInfo() const;

	/*!
	 * \brief Writes the Address information to the specified output stream.
	 *
	 * This function writes the street, postal code, city name,
	 * and additional information of the Address object to the given output stream.
	 * The information is separated by semicolons.
	 *
	 * \param out The output stream to which the Address information will be written.
	 */
	void write(std::ostream& out) const;

	/*!
	 * @brief Reads an Address from the input stream.
	 *
	 * This static member function reads an Address from the provided input stream.
	 * It expects the address information to be formatted in a specific way within
	 * a single line of the input stream.
	 *
	 * The expected format is "street;postalCode;city;additionalInfo".
	 *
	 * @param in The input stream from which to read the Address.
	 * @return A shared pointer to the dynamically allocated Address object.
	 */
	static std::shared_ptr<Address> read(std::istream& in);

	/*!
	 * @brief Convert the object to a Poco::JSON::Object::Ptr.
	 *
	 * This function converts the current object to a Poco::JSON::Object::Ptr,
	 * representing the object in JSON format.
	 *
	 * @return Poco::JSON::Object::Ptr representing the object in JSON.
	 */
	Poco::JSON::Object::Ptr toJson() const;

	/**
	 * @brief Create an Address object from JSON data.
	 *
	 * This static method takes a Poco::JSON::Object::Ptr representing JSON data
	 * and constructs an Address object from it. The resulting Address object
	 * is wrapped in a std::shared_ptr.
	 *
	 * @param data A pointer to the Poco::JSON::Object containing JSON data.
	 * @return A std::shared_ptr<Address> containing the constructed Address object.
	 */
	static std::shared_ptr<Address> fromJson(Poco::JSON::Object::Ptr data);

};

#endif /* ADDRESS_H_ */
