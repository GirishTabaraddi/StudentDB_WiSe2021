/*!
 * @file Student.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Student.h"

using namespace std;

unsigned int Student::m_nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address) :
		m_matrikelNumber(Student::m_nextMatrikelNumber++),
		m_firstName(firstName), m_lastName(lastName),
		m_dateOfBirth(dateOfBirth), m_address(address)
{
}

Student::~Student()
{
}

const unsigned int Student::getMatrikelNumber() const
{
	return this->m_matrikelNumber;
}

const std::string& Student::getFirstName() const
{
	return this->m_firstName;
}

const std::string& Student::getLastName() const
{
	return this->m_lastName;
}

const Poco::Data::Date Student::getDateOfBirth() const
{
	return this->m_dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return this->m_enrollments;
}

const std::shared_ptr<Address> Student::getAddress() const
{
	return this->m_address;
}

void Student::setNextMatrikelNumber(unsigned int newMatrikelnumber)
{
	m_nextMatrikelNumber = newMatrikelnumber;
}

void Student::setFirstName(const std::string &firstName)
{
	this->m_firstName = firstName;
}

void Student::setLastName(const std::string &lastName)
{
	this->m_lastName = lastName;
}

void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->m_dateOfBirth = dateOfBirth;
}

void Student::setAddress(const std::shared_ptr<Address> address)
{
	this->m_address = address;
}

void Student::addEnrollment(const std::string& semester, const Course *newCourseId)
{
	unsigned int courseKey = newCourseId->getcourseKey();

	bool enrollmentFound = false;

	for(const Enrollment& enrollment : this->m_enrollments)
	{
		if(enrollment.getcourse()->getcourseKey() == courseKey)
		{
			enrollmentFound = true;
			break;
		}
	}
	if(!enrollmentFound)
	{
		this->m_enrollments.push_back(Enrollment(semester, newCourseId));
	}
}

void Student::deleteEnrollment(const unsigned int &courseKey)
{
	for(vector<Enrollment>::iterator itr = this->m_enrollments.begin();
			itr != this->m_enrollments.end();)
	{
		if(itr->getcourse()->getcourseKey() == courseKey)
		{
			cout << "Entered Enrollment Deleted!!" << endl;
			itr = this->m_enrollments.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void Student::updateGrade(const float &grade, const unsigned int &courseKey)
{
	for(vector<Enrollment>::iterator itr = this->m_enrollments.begin();
			itr != this->m_enrollments.end(); itr++)
	{
		if(itr->getcourse()->getcourseKey() == courseKey)
		{
			itr->setgrade(grade);
			break;
		}
	}
}

void Student::write(std::ostream &out) const
{
	out << to_string(this->m_matrikelNumber)
						<< ";" << this->m_firstName
						<< ";" << this->m_lastName << ";"
						<< datetoString(this->m_dateOfBirth) + ";";

	this->getAddress()->write(out);
}

Student Student::read(std::istream &in)
{
	string inStr;

	getline(in, inStr);

	unsigned int matrikelNumber = stoul(splitAt(inStr, ';'));

	Student::m_nextMatrikelNumber = matrikelNumber;

	string firstName = splitAt(inStr, ';');
	string lastName = splitAt(inStr, ';');
	Poco::Data::Date dateOfBirth = stringToPocoDateFormatter(splitAt(inStr, ';'));

	istringstream iss(inStr);

	shared_ptr<Address> address = Address::read(iss);

	Student addStudent(firstName, lastName, dateOfBirth, address);

	return addStudent;
}

Poco::JSON::Object::Ptr Student::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	returnObj->set("firstName", this->m_firstName);
	returnObj->set("lastName", this->m_lastName);
	returnObj->set("dateOfBirth", datetoString(this->m_dateOfBirth));
	returnObj->set("matrikelNumber", this->m_matrikelNumber);

	returnObj->set("address", getAddress()->toJson());

	Poco::JSON::Array::Ptr enrollmentArray = new Poco::JSON::Array;

	for(const Enrollment& enrollment : this->m_enrollments)
	{
		enrollmentArray->add(enrollment.toJson());
	}

	returnObj->set("enrollments", enrollmentArray);

	return returnObj;
}

std::string Student::datetoString(const Poco::Data::Date date) const
{
	int year = date.year();
	int month = date.month();
	int day = date.day();

	ostringstream oss;

	oss << setw(2) << setfill('0') << day << "." << setw(2) << setfill('0')
			<< month << "." << year;

	return oss.str();
}

Student Student::fromJson(Poco::JSON::Object::Ptr data)
{
	Poco::DynamicStruct jsonDataStruct = *data;

	string firstName = jsonDataStruct["firstName"].toString();
	string lastName = jsonDataStruct["lastName"].toString();
	string dateOfBirthStr = jsonDataStruct["dateOfBirth"].toString();

	Poco::Data::Date dateOfBirth = stringToPocoDateFormatter(dateOfBirthStr);

	unsigned int matrikelNumber = jsonDataStruct["matrikelNumber"];

	Student::m_nextMatrikelNumber = matrikelNumber;

	const Poco::JSON::Object::Ptr addressData = data->getObject("address");

	std::shared_ptr<Address> address = Address::fromJson(addressData);

	return Student(firstName, lastName, dateOfBirth, address);
}
