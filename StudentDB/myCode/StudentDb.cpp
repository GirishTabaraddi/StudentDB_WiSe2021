/*!
 * @file StudentDb.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "StudentDb.h"

using namespace std;

StudentDb::StudentDb()
{
}

StudentDb::~StudentDb()
{
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return this->m_students;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return this->m_courses;
}

StudentDb::RC_StudentDb_t
StudentDb::addNewCourse(std::string &courseKey, std::string &title,
		std::string &major, std::string &credits, std::string& semester, std::string &courseType,
		std::string &startTime, std::string &endTime, std::string &startDate,
		std::string &endDate, std::string &dayOfWeek)
{
	//! using for loop to iterate over each of the courses in map
	for(const pair<const int, unique_ptr<const Course>>& itr : this->m_courses)
	{
		const Course& courseref = *(itr.second);

		if((courseref.getcourseKey() == stoul(courseKey))
				|| (courseref.gettitle() == title))
		{
			return RC_StudentDb_t::RC_Course_Exists;
		}
	}

	if(courseType == "B" || courseType == "b")
	{
		unique_ptr<BlockCourse> blockCourse =
				make_unique<BlockCourse>(stoi(courseKey), title,
							major, stof(credits), semester,
						stringToPocoDateFormatter(startDate),
						stringToPocoDateFormatter(endDate),
						stringToPocoTimeFormatter(startTime),
						stringToPocoTimeFormatter(endTime));

		this->m_courses.insert(make_pair(blockCourse->getcourseKey(), move(blockCourse)));
	}
	else if(courseType == "W" || courseType == "w")
	{
		Poco::DateTime::DaysOfWeek dayOfWeekinPoco = getDayOfWeekFromString(dayOfWeek);

		unique_ptr<WeeklyCourse> weeklyCourse =
				make_unique<WeeklyCourse>(stoi(courseKey),
							title, major, stof(credits), semester, dayOfWeekinPoco,
						stringToPocoTimeFormatter(startTime),
						stringToPocoTimeFormatter(endTime));

		this->m_courses.insert(make_pair(weeklyCourse->getcourseKey(), move(weeklyCourse)));
	}

	return RC_StudentDb_t::RC_Success;
}

std::string StudentDb::listCourses() const
{
	ostringstream output;

	for(const pair<const int, unique_ptr<const Course>>& course : this->m_courses)
	{
		output << course.second->printCourse() << endl;
	}

	return output.str();
}

StudentDb::RC_StudentDb_t
StudentDb::addNewStudent(std::string &firstName, std::string &lastName,
		std::string &DoBstring, std::string &streetName,
		std::string &postalCode, std::string &cityName,
		std::string &additionalInfo)
{
	//! using for loop to find m_students if they exist already.
	for(const pair<const int,Student>& itr : this->m_students)
	{
		const Student& student = itr.second;

		if(student.getFirstName() == firstName &&
				student.getLastName() == lastName &&
				student.getAddress()->getstreet() == streetName &&
				student.getAddress()->getcityName() == cityName &&
				student.getAddress()->getpostalCode() == stoi(postalCode) &&
				student.getAddress()->getadditionalInfo() == additionalInfo)
		{
			return RC_StudentDb_t::RC_Student_Exists;
		}
	}

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	Student student(firstName, lastName, stringToPocoDateFormatter(DoBstring), address);

	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));

	return RC_StudentDb_t::RC_Success;
}

StudentDb::RC_StudentDb_t
StudentDb::addEnrollment(std::string &matrikelNumber,
		std::string &semester, std::string &courseKey)
{
	map<int, Student>::iterator findStudent = this->m_students.find(stoul(matrikelNumber));

	if(findStudent != this->m_students.end())
	{
		map<int, unique_ptr<const Course>>::iterator findCourse = this->m_courses.find(stoul(courseKey));

		if(findCourse != this->m_courses.end())
		{
			const vector<Enrollment>& enrollments = findStudent->second.getEnrollments();

			for(const Enrollment& enrollmentItr : enrollments)
			{
				if(enrollmentItr.getcourse()->getcourseKey() == stoul(courseKey) &&
						enrollmentItr.getsemester() == semester)
				{
					return RC_StudentDb_t::RC_Enrollment_Exists;
				}
			}

			const Course& courseref = *(findCourse->second);

			findStudent->second.addEnrollment(semester, &courseref);

			return RC_StudentDb_t::RC_Success;
		}
		else
		{
			return RC_StudentDb_t::RC_Wrong_Course_Key;
		}
	}
	else
	{
		return RC_StudentDb_t::RC_Wrong_MatrikelNumber;
	}
}

void StudentDb::updateFirstName(const std::string &newFirstName,
		unsigned int matrikelNumber)
{
	this->m_students.at(matrikelNumber).setFirstName(newFirstName);
}

void StudentDb::updateLastName(const std::string &newLastName,
		unsigned int matrikelNumber)
{
	this->m_students.at(matrikelNumber).setLastName(newLastName);
}

void StudentDb::updateDateOfBirth(const Poco::Data::Date &dateOfBirth,
		unsigned int matrikelNumber)
{
	this->m_students.at(matrikelNumber).setDateOfBirth(dateOfBirth);
}

void StudentDb::updateAddress(const std::string &street,
		const unsigned int &postalCode, const std::string &cityName,
		const std::string &additionalInfo, unsigned int matrikelNumber)
{
	shared_ptr<Address> address =
			make_shared<Address>(street, postalCode, cityName, additionalInfo);

	this->m_students.at(matrikelNumber).setAddress(address);
}

void StudentDb::deleteEnrollment(const unsigned int &courseKey,
		const unsigned int matrikelNumber)
{
	this->m_students.at(matrikelNumber).deleteEnrollment(courseKey);
}

void StudentDb::updateGrade(const unsigned int &courseKey, const float &newGrade,
		const unsigned int matrikelNumber)
{
	this->m_students.at(matrikelNumber).updateGrade(newGrade, courseKey);
}

void StudentDb::write(std::ostream &out) const
{
	this->writeCoursesData(out);
	this->writeStudentsData(out);
	this->writeEnrollmentsData(out);
}

void StudentDb::writeCoursesData(std::ostream &out) const
{
	out << this->m_courses.size() << endl;

	for(const pair<const int, unique_ptr<const Course>>& coursesPair: this->m_courses)
	{
		coursesPair.second.get()->write(out);
	}
}

void StudentDb::writeStudentsData(std::ostream &out) const
{
	out << this->m_students.size() << endl;

	for(const pair<const int,Student>& studentsPair: this->m_students)
	{
		const Student& student = studentsPair.second;

		student.write(out);

		out << endl;
	}
}

void StudentDb::writeEnrollmentsData(std::ostream &out) const
{
	map<unsigned int, vector<Enrollment>> StudentEnrollments;

	for(const pair<const int,Student>& eachStudent: this->m_students)
	{
		unsigned int matrikelNumber = eachStudent.second.getMatrikelNumber();

		for(const Enrollment& enrollment : eachStudent.second.getEnrollments())
		{
			StudentEnrollments[matrikelNumber].push_back(enrollment);
		}
	}

	out << StudentEnrollments.size() << endl;

	for(pair<int, vector<Enrollment>> itr: StudentEnrollments)
	{
		for(const Enrollment& enrItr: itr.second)
		{
			out << itr.first << ";";

			enrItr.write(out);
		}

		out << endl;
	}
}

void StudentDb::read(std::istream &in)
{
	//! Clearing the database.
	this->m_courses.clear();
	this->m_students.clear();

	string LineStr;
	unsigned int count = 0;
	unsigned char caseChar;

	while(getline(in, LineStr))
	{
		if(LineStr.find(";") == string::npos)
		{
			if(count == 0)
			{
				caseChar = 'C';
			}
			if(count == 1)
			{
				caseChar = 'S';
			}
			if(count == 2)
			{
				caseChar = 'E';
			}
			count++;
		}
		else if(LineStr.find(";") != string::npos)
		{
			switch(caseChar)
			{
			case 'C':
			{
				this->readCoursesData(LineStr);
			}
			break;
			case 'S':
			{
				this->readStudentsData(LineStr);
			}
			break;
			case 'E':
			{
				this->readEnrollmentData(LineStr);
			}
			break;
			default:
			{
				break;
			}
			}
		}
	}
}

void StudentDb::readCoursesData(std::string &str)
{
	istringstream iss(str);

	unique_ptr<Course> course = Course::read(iss);

	if(course != nullptr)
	{
		this->m_courses[course->getcourseKey()] = move(course);
	}
}

void StudentDb::readStudentsData(std::string &str)
{
	istringstream iss(str);

	Student readStudent = Student::read(iss);

	this->m_students.insert(make_pair(readStudent.getMatrikelNumber(), readStudent));
}

void StudentDb::readEnrollmentData(std::string &str)
{
	unsigned int matrikelNumber = stoul(splitAt(str, ';'));

	for(const pair<const int, unique_ptr<const Course>>& pairItr : this->m_courses)
	{
		const Course& courseref =  *(pairItr.second.get());

		map<int, Student>::iterator checkMatrikel = this->m_students.find(matrikelNumber);

		if(checkMatrikel->second.getMatrikelNumber() == matrikelNumber)
		{
			istringstream iss(str);

			Enrollment readEnrollment = Enrollment::read(iss, &courseref);

			if(readEnrollment.getcourse() != nullptr)
			{
				checkMatrikel->second.addEnrollment(readEnrollment.getsemester(),
						readEnrollment.getcourse());
				checkMatrikel->second.updateGrade(readEnrollment.getgrade(),
						readEnrollment.getcourse()->getcourseKey());
			}
		}
	}
}

//void StudentDb::readStudentDataFromServer(unsigned int noOfUserData)
//{
//	string hostname = "www.hhs.users.h-da.cloud";
//	string port = "4242";
//
//	boost::asio::ip::tcp::iostream stream;
//
//	stream.connect(hostname, port);
//
//	if(!stream)
//	{
//		cerr << "Connection to server unsuccessful!!" << stream.error().message() << endl;
//	}
//
//	for(unsigned int idx = 0; idx < noOfUserData; idx++)
//	{
//		stream << "generate" << endl;
//		stream.flush();
//
//		string line1, line2, line3;
//
//		getline(stream, line1);
//
//		getline(stream, line2);
//
//		getline(stream, line3);
//
//		this->parsingJSONData(line2);
//
//	}
//
//	stream << "quit" << endl;
//	stream.flush();
//}
//
//void StudentDb::parsingJSONData(std::string &JSONData)
//{
//
//	istringstream iss(JSONData);
//
//	boost::property_tree::ptree parsedData;
//
//	boost::property_tree::read_json(iss, parsedData);
//
//	if(this->isValidServerDataString(parsedData.get<string>("name.firstName")) &&
//			this->isValidServerDataString(parsedData.get<string>("name.lastName")) &&
//			this->isValidServerDataString(parsedData.get<string>("location.city")) &&
//			this->isValidServerDataString(parsedData.get<string>("location.street")) &&
//			this->isValidServerDataString(parsedData.get<string>("location.state")) &&
//			this->isValidServerDataString(parsedData.get<string>("dateOfBirth.year")) &&
//			this->isValidServerDataString(parsedData.get<string>("dateOfBirth.month")) &&
//			this->isValidServerDataString(parsedData.get<string>("dateOfBirth.date")) &&
//			this->isValidServerDataString(parsedData.get<string>("location.postCode")))
//	{
//		string firstName = parsedData.get<string>("name.firstName");
//		string lastName = parsedData.get<string>("name.lastName");
//		string yearStr = parsedData.get<string>("dateOfBirth.year");
//		string monthStr = parsedData.get<string>("dateOfBirth.month");
//		string dayStr = parsedData.get<string>("dateOfBirth.date");
//		string postCodeStr = parsedData.get<string>("location.postCode");
//		string city = parsedData.get<string>("location.city");
//		string street = parsedData.get<string>("location.street");
//		string additionalInfo = parsedData.get<string>("location.state");
//
//
//		int year = (all_of(yearStr.begin(), yearStr.end(), ::isdigit))
//				? stoi(yearStr)+1900 : 1900;
//		int month = (all_of(monthStr.begin(), monthStr.end(), ::isdigit))
//				? stoi(monthStr)+1 : 1;
//		int day = (all_of(dayStr.begin(), dayStr.end(), ::isdigit))
//				? stoi(dayStr) : 1;
//		int postCode = (all_of(postCodeStr.begin(), postCodeStr.end(), ::isdigit))
//				? stoi(postCodeStr) : 9999;
//
//		Poco::Data::Date dateOfBirth(year, month, day);
//
//		shared_ptr<Address> address =
//				make_shared<Address>(street, postCode, city, additionalInfo);
//
//		Student student(firstName, lastName, dateOfBirth, address);
//
//		this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
//	}
//}

bool StudentDb::isValidServerDataString(const std::string &eachStr)
{
	if(all_of(eachStr.begin(), eachStr.end(), ::isprint))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StudentDb::readStudentDataFromServer(unsigned int noOfUserData)
{
	//! Create a socket address
	Poco::Net::SocketAddress socketAddress("www.hhs.users.h-da.cloud", 4242);

	string readLine;

	unsigned int loopIdx = 0;

	while(loopIdx < noOfUserData)
	{
		//! Create a stream socket
		Poco::Net::StreamSocket socket;

		try
		{
			socket.connect(socketAddress, Poco::Timespan(5, 0));

			//! Create a SocketStream using the socket
			Poco::Net::SocketStream stream(socket);

			stream << "generate";
			stream.flush();

			//! Calling shutdownSend() indicates that you will no longer be sending data on the socket.
			socket.shutdownSend();

			vector<string> serverData;

			while(getline(stream, readLine))
			{
				serverData.push_back(readLine);
			}

			//! Calling shutdownReceive() indicates that you will no longer be receiving data on the socket.
			socket.shutdownReceive();

			stream << "quit";
			stream.flush();

			//! the socket is no longer in use
			socket.close();

			if(serverData.empty() == false)
			{
				cout << serverData.at(0) << endl; // this prints 100 Generating

				cout << loopIdx+1 << " User Data\n" << endl;

				parsingJSONData(serverData.at(1));	//! This line contains the JSON Data required.

				cout << serverData.at(2) << endl;
			}
		}
		catch(const Poco::Exception& e)
		{
			cerr << "Exception caught: " << e.displayText() << endl;
		}

		loopIdx++;	
	}
}

void StudentDb::parsingJSONData(std::string &JSONData)
{
	Poco::JSON::Parser jsonParser;

	Poco::Dynamic::Var parsedJSONData = jsonParser.parse(JSONData);

	Poco::JSON::Object::Ptr jsonObjectPtr = parsedJSONData.extract<Poco::JSON::Object::Ptr>();

	Poco::DynamicStruct JSONDataStruct = *jsonObjectPtr;

	if(this->isValidServerDataString(JSONDataStruct["name"]["firstName"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["name"]["lastName"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["dateOfBirth"]["year"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["dateOfBirth"]["month"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["dateOfBirth"]["date"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["location"]["street"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["location"]["postCode"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["location"]["city"].toString()) &&
			this->isValidServerDataString(JSONDataStruct["location"]["state"].toString()))
	{
		string firstName = Poco::UTF8::unescape(JSONDataStruct["name"]["firstName"].toString());
		string lastName = Poco::UTF8::unescape(JSONDataStruct["name"]["lastName"].toString());
		int year = JSONDataStruct["dateOfBirth"]["year"].convert<int>()+1900;
		int month = JSONDataStruct["dateOfBirth"]["month"].convert<int>()+1;
		int day = JSONDataStruct["dateOfBirth"]["date"].convert<int>();

		string streetName = Poco::UTF8::unescape(JSONDataStruct["location"]["street"].toString());
		int postalCode = JSONDataStruct["location"]["postCode"].convert<int>();
		string cityName = Poco::UTF8::unescape(JSONDataStruct["location"]["city"].toString());
		string additionalInfo = Poco::UTF8::unescape(JSONDataStruct["location"]["state"].toString());

		shared_ptr<Address> address =
				make_shared<Address>(streetName, postalCode, cityName, additionalInfo);

		Student student = Student(firstName, lastName, Poco::Data::Date(year, month, day), address);

		this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
	}
}

Poco::JSON::Object::Ptr StudentDb::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	Poco::JSON::Array::Ptr coursesArray = new Poco::JSON::Array;

	for(const pair<const int, unique_ptr<const Course>>& course: this->m_courses)
	{
		coursesArray->add(course.second->toJson());
	}

	Poco::JSON::Array::Ptr studentsArray = new Poco::JSON::Array;

	for(const pair<const int,Student>& student: this->m_students)
	{
		studentsArray->add(student.second.toJson());
	}

	returnObj->set("courses", coursesArray);
	returnObj->set("students", studentsArray);

	return returnObj;
}
