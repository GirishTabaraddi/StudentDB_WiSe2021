/*!
 * @file Address.cpp
 *
 * \n Created on: 10-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Address.h"

using namespace std;

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo) :
		m_street(street), m_postalCode(postalCode),
		m_cityName(cityName), m_additionalInfo(additionalInfo)
{
}

Address::~Address()
{
}

const std::string& Address::getstreet() const
{
	return this->m_street;
}

const unsigned short Address::getpostalCode() const
{
	return this->m_postalCode;
}

const std::string& Address::getcityName() const
{
	return this->m_cityName;
}

const std::string& Address::getadditionalInfo() const
{
	return this->m_additionalInfo;
}

void Address::write(std::ostream &out) const
{
	out << this->m_street
			<< ";" << to_string(this->m_postalCode)
			<< ";" << this->m_cityName
			<< ";" << this->m_additionalInfo;
}

std::shared_ptr<Address> Address::read(std::istream &in)
{
	string inStr;
	getline(in, inStr);

	string street = splitAt(inStr, ';');
	unsigned int postalCode = stoi(splitAt(inStr, ';'));
	string city = splitAt(inStr, ';');
	string additionalInfo = splitAt(inStr, ';');

	return make_shared<Address>(street, postalCode, city, additionalInfo);
}

Poco::JSON::Object::Ptr Address::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	returnObj->set("street", this->m_street);
	returnObj->set("postalCode", this->m_postalCode);
	returnObj->set("cityName", this->m_cityName);
	returnObj->set("additionalInfo", this->m_additionalInfo);

	return returnObj;
}

std::shared_ptr<Address> Address::fromJson(Poco::JSON::Object::Ptr data)
{
	Poco::DynamicStruct jsonDataStruct = *data;

	string street = jsonDataStruct["street"].toString();

	unsigned int postalCode = jsonDataStruct["postalCode"];

	string city = jsonDataStruct["cityName"].toString();

	string additionalInfo = jsonDataStruct["additionalInfo"].toString();

	return make_shared<Address>(street, postalCode, city, additionalInfo);
}
