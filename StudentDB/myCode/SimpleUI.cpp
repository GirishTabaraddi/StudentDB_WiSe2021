/*!
 * @file SimpleUI.cpp
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb &db) : m_db(db)
{
}

SimpleUI::~SimpleUI()
{
}

void SimpleUI::run() const
{
	bool exitFlag = false;

	cout << "Main Menu: Below are the properties of Student Database : " << endl << endl;

	cout << "\t 0	-> To Exit Main Menu" << endl;
	cout << "\t 1 	-> To Add New Course" << endl;
	cout << "\t 2 	-> To List the Courses" << endl;
	cout << "\t 3 	-> To Add new Student" << endl;
	cout << "\t 4 	-> To Add Enrollment" << endl;
	cout << "\t 5 	-> To Print Student Details" << endl;
	cout << "\t 6 	-> To Search Student in Database" << endl;
	cout << "\t 7 	-> To Update Student Details" << endl;
	cout << "\t 8 	-> To Write Student Database to a text file" << endl;
	cout << "\t 9 	-> To Read Student Database from a file" << endl;
	cout << "\t 10 	-> To Read Student Database from a server" << endl;
	cout << "\t 11 	-> To Write Student Data in JSON Format" << endl;
	cout << "\t 12 	-> To Read Student Data from JSON Format" << endl;

	while(exitFlag == false)
	{
		string choice;

		getUserInput("\t Enter your choice to perform the respective "
				"operation between 0 and 12: ", "\\d+", choice);

		int numericChoice = stoi(choice);

		if(numericChoice >= 0 && numericChoice <= 12)
		{
			switch(numericChoice)
			{
			case 0:
			{
				cout << endl << "Exited Main Menu : " << numericChoice << endl;
				exitFlag = true;
			}
			break;
			case 1:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to add new course." <<endl;

				this->getUserInputsforNewCourse();
			}
			break;
			case 2:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to list all courses." <<endl;

				this->listCourses();
			}
			break;
			case 3:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to add new student to the database." <<endl;

				this->getUserInputsforNewStudent();
			}
			break;
			case 4:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to add new enrollment." <<endl;

				this->getUserInputforNewEnrollment();
			}
			break;
			case 5:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to print the details of the student." <<endl;

				this->printStudent();
			}
			break;
			case 6:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to search specific student in database." <<endl;

				this->searchStudent();
			}
			break;
			case 7:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to update the student details." <<endl;

				this->getUserInputforStudentUpdate();
			}
			break;
			case 8:
			{
				string filename = "fileData.txt";

				getUserInput("\t Enter the file name to write the data(.txt): ",
						R"([a-zA-Z0-9_-]+\.[tT][xX][tT])", filename);

				ofstream writeFile(filename, ios::trunc);

				if(writeFile.is_open())
				{
					this->m_db.write(writeFile);

					writeFile.close();

					cout << "\n\t Student Database is written to the file" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			case 9:
			{
				string filename = "read_StudentDb.txt";

				getUserInput("\t Enter the file name to read the data from(.txt): ",
						R"([a-zA-Z0-9_-]+\.[tT][xX][tT])", filename);

				ifstream readFile(filename);

				if(readFile.is_open())
				{
					this->m_db.read(readFile);

					readFile.close();

					cout << "\n\t Read the Student Database from the file" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			case 10:
			{
				string noOfUserDate;

				getUserInput("Enter the number of Student Data to be "
						"extracted from the server: ", "\\d+", noOfUserDate);

				this->m_db.readStudentDataFromServer(stoul(noOfUserDate));
			}
			break;
			case 11:
			{
				string filename = "write_JSONData.txt";

				getUserInput("\t Enter the file name to write JSON Data(.txt): ",
						R"([a-zA-Z0-9_-]+\.[tT][xX][tT])", filename);

				ofstream writeFile(filename, ios::trunc);

				if(writeFile.is_open())
				{
					Poco::JSON::Object::Ptr jsondata = this->m_db.toJson();

					ostringstream jsonStream;

					Poco::JSON::Stringifier::stringify(jsondata, jsonStream, 2, 2);

					writeFile << jsonStream.str();

					writeFile.close();

					cout << "\n\t Student Database is written to the file" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			case 12:
			{
				string filename = "read_fromJSON.txt";

//				getUserInput("\t Enter the file name to read the data from(.txt): ",
//						R"([a-zA-Z0-9_-]+\.[tT][xX][tT])", filename);

				ifstream readFile("read_fromJSON.txt");

				if(readFile.is_open())
				{
					Poco::JSON::Parser parser;

					Poco::Dynamic::Var result = parser.parse(readFile);

//					if(result.isStruct())
//					{
						this->m_db.fromJson(result.extract<Poco::JSON::Object::Ptr>());
//					}

					readFile.close();

					cout << "\n\t Read the Student Database from the JSON format" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			default:
			{
				cout << endl << "ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-12]" << endl;
			}
			}
		}
		else
		{
			cout << endl << "ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-12]" << endl;
		}
	}
}

void SimpleUI::getUserInputsforNewCourse() const
{
	string courseKey, title, major, credits, startTime,
	endTime, startDate, endDate, dayOfWeek, courseType, semester;

	getUserInput("\t \t Enter CourseKey - (0-9): ", "\\d+", courseKey);

	getUserInput("\t \t Enter Title of the Course - (a-z/A-Z): ",
			"[a-zA-Z]+", title);

	bool isValidMajor = false;

	while (!isValidMajor)
	{
		getUserInput("\t \t Available Majors are : Automation, Embedded Systems,"
				" Communication and Power\n \t \t Enter the Major in which "
				"the Course belongs to: ", "[a-zA-Z]+", major);

		for (const auto &itr : Course::getmajorById())
		{
			if (boost::algorithm::icontains(itr.second, major))
			{
				isValidMajor = true;
				break;
			}
		}

		if (!isValidMajor)
		{
			cout << endl << "\t You entered a wrong Major" << endl;
		}
	}

	getUserInput("\t \t Enter the credit points of the Course - (0-9): ", "\\d+", credits);

	getUserInput("\t \t Enter the Semester of the Student "
			"studying currently - (hint: WiSe2023/SoSe2024): ", "^(SoSe|WiSe)\\d{4}", semester);

	getUserInput("\t \t Enter the Course Type - Weekly(W/w)/Block(B/b): ", "[BbWw]", courseType);
	if(courseType != "B" && courseType != "b" && courseType != "W" && courseType != "w")
	{
		cout << endl << "\t You entered an invalid course type (hint: B/W/b/w)" << endl;
		return;
	}

	getUserInput("\t \t Enter the Course Start Time - HH:MM : ", R"(\d{1,2}\:\d{1,2})", startTime);
	getUserInput("\t \t Enter the Course End Time - HH:MM : ", R"(\d{1,2}\:\d{1,2})", endTime);

	if(courseType == "B" || courseType == "b")
	{
		getUserInput("\t \t Enter the Course Start Date - dd.mm.YYYY : ",
				R"((\d{1,2})\.(\d{1,2})\.(\d{4}))", startDate);
		getUserInput("\t \t Enter the Course End Date - dd.mm.YYYY : ",
				R"((\d{1,2})\.(\d{1,2})\.(\d{4}))", endDate);
	}
	else if(courseType == "W" || courseType == "w")
	{
		getUserInput("\t \t Enter the Course Week - (Monday-Sunday) : ", "[a-zA-Z]+", dayOfWeek);
	}

	//! Call the addNewCourse function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addNewCourse(courseKey, title, major, credits, semester,
					courseType, startTime, endTime, startDate,
					endDate, dayOfWeek);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Course Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Course_Exists:
	{
		cout << "\t \t \nCourse with the given details already exists in the database." << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Invalid_Semester_Added:
	{
		cout << "\t \t \nThe course tried to add has a invalid semester entry" << endl;
		break;
	}
	default:
	{
		cout << "\t \t \nUnexpected error during add course" << endl;
		break;
	}
	}
}

void SimpleUI::listCourses() const
{
	cout << "No of Courses in Database: "<< this->m_db.getCourses().size() << endl << endl;

	for(const pair<const int, unique_ptr<const Course>>& courses: this->m_db.getCourses())
	{
		const Course* course = courses.second.get();

		if (const BlockCourse* blockcourse = dynamic_cast<const BlockCourse*>(course))
		{
			cout << "[Type: Block] | ";
			cout << "[key: " << course->getcourseKey() << "] | ";
			cout << "[Title: " << course->gettitle() << "] | ";
			cout << "[Major: " << course->getmajorById().at(course->getmajor()) << "] | ";
			cout << "[Credits: " << course->getcreditPoints() << "] | ";

			cout << endl << "\t";

			cout << "[StartDate: " << pocoDateToStringFormatter(blockcourse->getStartDate()) << "] | ";
			cout << "[EndDate: " << pocoDateToStringFormatter(blockcourse->getEndDate()) << "] | ";
			cout << "[StartTime: " << pocoTimeToStringFormatter(blockcourse->getStartTime()) << "] | ";
			cout << "[EndTime: " << pocoTimeToStringFormatter(blockcourse->getEndTime()) << "]";
		}
		else if (const WeeklyCourse* weeklycourse = dynamic_cast<const WeeklyCourse*>(course))
		{
			cout << "[Type: Weekly] | ";
			cout << "[key: " << course->getcourseKey() << "] | ";
			cout << "[Title: " << course->gettitle() << "] | ";
			cout << "[Major: " << course->getmajorById().at(course->getmajor()) << "] | ";
			cout << "[Credits: " << course->getcreditPoints() << "] | ";

			cout << endl << "\t";

			cout << "[WeekDay: " << weeklycourse->getDaysOfWeek() << "] | ";
			cout << "[StartTime: " << pocoTimeToStringFormatter(weeklycourse->getStartTime()) << "] | ";
			cout << "[EndTime: " << pocoTimeToStringFormatter(weeklycourse->getEndTime()) << "]";
		}

		cout << endl << endl;
	}
}

void SimpleUI::getUserInputsforNewStudent() const
{
	string firstName, lastName, DoBstring, streetName, postalCode, cityName, additionalInfo;

	getUserInput("\t \t Enter First Name of the Student - (a-z/A-Z): ", "[a-zA-Z]+", firstName);
	getUserInput("\t \t Enter Last Name of the Student - (a-z/A-Z): ", "[a-zA-Z]+", lastName);
	getUserInput("\t \t Enter Date of Birth of the Student - (dd.mm.YYYY): ",
			R"((\d{1,2})\.(\d{1,2})\.(\d{4}))", DoBstring);
	getUserInput("\t \t Enter Street Name of the Student's Address - (a-z/A-Z): ",
			"[a-zA-Z0-9\\s\\p{P}]+", streetName);
	getUserInput("\t \t Enter Post Code of the Student's Address - (0-9): ",
			"\\d+", postalCode);
	getUserInput("\t \t Enter City Name of the Student's Address - (a-z/A-Z): ",
			"[a-zA-Z\\s]+", cityName);
	getUserInput("\t \t Enter Additional Info of Student's Address - (0-9/a-z/A-Z): ",
			"[a-zA-Z0-9\\s\\p{P}]+", additionalInfo);

	//! Call the addnewstudent function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addNewStudent(firstName, lastName, DoBstring,
					streetName, postalCode, cityName, additionalInfo);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Student Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Student_Exists:
	{
		cout << "\t \t \nStudent with the given details already exists in the database." << endl;
		break;
	}
	default:
	{
		cout << "\t \t \nUnexpected error during add student" << endl;
		break;
	}
	}
}

void SimpleUI::getUserInputforNewEnrollment() const
{
	string matrikelNumber, semester, courseKey;

	getUserInput("\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - (0-9): ", "\\d+", matrikelNumber);

	getUserInput("\t \t Enter the Semester of the Student "
			"studying currently - (hint: WiSe2023/SoSe2024): ", "^(SoSe|WiSe)\\d{4}", semester);

	getUserInput("\t \t Enter the Course Key, "
			"to which he/she wants to enroll - 0-9: ", "\\d+", courseKey);

	//! Call the addEnrollment function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addEnrollment(matrikelNumber, semester, courseKey);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Enrollment Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Wrong_Course_Key:
	{
		cout << "\t \t \nProvided course key is incorrect or not found" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Wrong_MatrikelNumber:
	{
		cout << "\t \t \nProvided matrikel number is incorrect or not found." << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Enrollment_Exists:
	{
		cout << "\t \t \nEnrollment for the student and course already exists in the database." << endl;
		break;
	}
	default:
	{
		cout << "\t \t \nUnexpected error during add enrollment" << endl;
		break;
	}
	}
}

void SimpleUI::printStudent() const
{
	string matrikelNumber;

	getUserInput("\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - (0-9): ", "\\d+", matrikelNumber);

	map<int, Student>::const_iterator matrikelNumberItr =
			this->m_db.getStudents().find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_db.getStudents().end())
	{
		const Student& student = matrikelNumberItr->second;

		cout << endl << "[MatrikelNumber: " << student.getMatrikelNumber() << "] | ";
		cout << "[FirstName: " << student.getFirstName() << "] | ";
		cout << "[LastName: " << student.getLastName() << "] | ";
		cout << "[DateOfBirth: " << pocoDateToStringFormatter(student.getDateOfBirth()) << "] | ";

		cout << endl << "\t";

		cout << "[Street: " << student.getAddress()->getstreet() << "] | ";
		cout << "[PostalCode: " << student.getAddress()->getpostalCode() << "] | ";
		cout << "[City: " << student.getAddress()->getcityName() << "] | ";
		cout << "[AdditionalInfo: " << student.getAddress()->getadditionalInfo() << "] | ";

		cout << endl << "\t";

		for(const Enrollment& enrollment : student.getEnrollments())
		{
			cout << "[CourseKey: " << enrollment.getcourse()->getcourseKey() << "] | ";
			cout << "[Semester: " << enrollment.getsemester() << "] | ";
			cout << "[Grade: " << enrollment.getgrade() << "] | ";
		}
	}
	else
	{
		cout << "\n\t \t Entered Matrikel Number does not match "
				"any student in the database." << endl;
	}

	cout << endl << endl;
}

void SimpleUI::searchStudent() const
{
	string searchString;

	getUserInput("\t \t Enter Student Name to search in the Database - a-z/A-Z: ",
			"[a-zA-Z]", searchString);

	bool matchFound = false;

	for(const pair<const int,Student> & studentsItr : this->m_db.getStudents())
	{
		const Student& student = studentsItr.second;

		string firstName = student.getFirstName();
		string lastName = student.getLastName();

		if (boost::algorithm::icontains(firstName, searchString) ||
				boost::algorithm::icontains(lastName, searchString))
		{
			cout << endl << "[MatrikelNumber: " << student.getMatrikelNumber() << "] | ";
			cout << "[FirstName: " << student.getFirstName() << "] | ";
			cout << "[LastName: " << student.getLastName() << "] | ";
			cout << "[DateOfBirth: " << pocoDateToStringFormatter(student.getDateOfBirth()) << "] | ";

			cout << endl << "\t";

			cout << "[Street: " << student.getAddress()->getstreet() << "] | ";
			cout << "[PostalCode: " << student.getAddress()->getpostalCode() << "] | ";
			cout << "[City: " << student.getAddress()->getcityName() << "] | ";
			cout << "[AdditionalInfo: " << student.getAddress()->getadditionalInfo() << "] | ";

			cout << endl << endl;
		}
	}
	if(matchFound == false)
	{
		cout << "\t \t Entered string doesn't match the Student Name "
				"or the Student does not exist in the Database" << endl;
	}
}

void SimpleUI::getUserInputforStudentUpdate() const
{
	string matrikelNumber;

	getUserInput("\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - (0-9): ", "\\d+", matrikelNumber);

	auto studentItr =  this->m_db.getStudents().find(stoi(matrikelNumber));

	if(studentItr != this->m_db.getStudents().end())
	{
		cout << endl << "\t \t UPDATE STUDENT MENU: "
				"Below are the index number to update the details" << endl << endl;

		cout << "\t \t \t 0 -> To Exit Update Student Menu" << endl;
		cout << "\t \t \t 1 -> Update First Name" << endl;
		cout << "\t \t \t 2 -> Update Last Name" << endl;
		cout << "\t \t \t 3 -> Update Date of Birth" << endl;
		cout << "\t \t \t 4 -> Update Address" << endl;
		cout << "\t \t \t 5 -> Update Enrollment" << endl;

		const Student& updateStudent = studentItr->second;

		this->performStudentUpdate(studentItr->first, updateStudent);
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}
}

void SimpleUI::performStudentUpdate(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		getUserInput("\t \t \t Enter your choice to perform "
				"the respective operation between 0 and 5: ", "\\d+", choice);

		int numericChoice = stoi(choice);

		if(numericChoice >= 0 && numericChoice <= 5)
		{
			switch(numericChoice)
			{
			case 0:
			{
				cout << endl << "\t \t Exited Student Update Menu : "
						<< numericChoice <<endl;
				exitFlag = true;
			}
			break;
			case 1:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update First Name." <<endl;

				string firstName;

				cout << endl << "\t \t \t \t Existing First Name of the Student: "
						<< updateStudent.getFirstName() << endl;
				getUserInput("\t \t \t \t Enter First Name of the Student to Update - a-z/A-Z: ",
						"[a-zA-Z]+", firstName);

				this->m_db.updateFirstName(firstName, matrikelNumber);
			}
			break;
			case 2:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Last Name." <<endl;

				string lastName;

				cout << endl << "\t \t \t \t Existing Last Name of the Student: "
						<< updateStudent.getLastName() << endl;
				getUserInput("\t \t \t \t Enter Last Name of the Student to Update - a-z/A-Z: ",
						"[a-zA-Z]+", lastName);

				this->m_db.updateLastName(lastName, matrikelNumber);
			}
			break;
			case 3:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Date of Birth." <<endl;

				string DoBstring = "31.12.9999";

				cout << endl << "\t \t \t \t Existing Date of Birth of the Student: "
						<< pocoDateToStringFormatter(updateStudent.getDateOfBirth()) << endl;
				getUserInput("\t \t \t \t Enter Date of Birth of the Student "
						"to Update - dd..mm..YYY : ", R"((\d{1,2})\.(\d{1,2})\.(\d{4}))", DoBstring);

				this->m_db.updateDateOfBirth(stringToPocoDateFormatter(DoBstring), matrikelNumber);
			}
			break;
			case 4:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Address." <<endl;

				this->getUserInputforAddressUpdate(matrikelNumber, updateStudent);
			}
			break;
			case 5:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Enrollment." <<endl << endl;

				this->getUserInputforEnrollmentUpdate(matrikelNumber, updateStudent);
			}
			break;
			default:
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-5]" << endl;
			}
			break;
			}
		}
		else
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-5]" << endl;
		}
	}
}

void SimpleUI::getUserInputforAddressUpdate(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	string streetName, postalCode, cityName, additionalInfo;

	cout << endl << "\t \t \t \t Existing Street Name of the Student's Address: "
			<< updateStudent.getAddress()->getstreet() << endl;
	getUserInput("\t \t \t \t Enter Street Name of the "
			"Student's Address to Update - a-z/A-Z: ",
			"[a-zA-Z0-9\\s\\p{P}]+", streetName);

	cout << endl << "\t \t \t \t Existing Post Code of the Student's Address: "
			<< updateStudent.getAddress()->getpostalCode() << endl;
	getUserInput("\t \t \t \t Enter Postal Code of the "
			"Student's Address to Update - 0-9: ", "\\d+", postalCode);

	cout << endl << "\t \t \t \t Existing City Name of the Student's Address: "
			<< updateStudent.getAddress()->getcityName() << endl;
	getUserInput("\t \t \t \t Enter City Name of the "
			"Student's Address to Update - a-z/A-Z: ", "[a-zA-Z\\s]+", cityName);

	cout << endl << "\t \t \t \t Existing Additional Info of the Student's Address: "
			<< updateStudent.getAddress()->getadditionalInfo() << endl;
	getUserInput("\t \t \t \t Enter Additional Info related "
			"to Student's Address to Update - 0-9/a-z/A-Z: ",
			"[a-zA-Z0-9\\s\\p{P}]+", additionalInfo);

	this->m_db.updateAddress(streetName, stoi(postalCode),
			cityName, additionalInfo, matrikelNumber);
}

void SimpleUI::getUserInputforEnrollmentUpdate(unsigned int matrikelNumber,
		const Student &updateStudent) const
{
	if(updateStudent.getEnrollments().empty())
	{
		cout << endl << "\t \t \t ERROR: Entered Student not "
				"enrolled to update grade or delete enrollment!!!" << endl;
		return;
	}

	string courseKey;

	getUserInput("\t \t \t \t Enter CourseKey to perform Enrollment Update - 0-9: ",
			"\\d+", courseKey);

	auto courseKeyItr = this->m_db.getCourses().find(stoi(courseKey));


	if(courseKeyItr != this->m_db.getCourses().end())
	{
		cout << endl << "\t \t \t \t 0 -> To Exit Update Enrollment Menu" << endl;
		cout << endl << "\t \t \t \t 1 -> Delete Enrollment" << endl;
		cout << endl << "\t \t \t \t 2 -> Update Grade" << endl;

		this->performEnrollmentUpdate(courseKey, updateStudent);
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Course Key "
				"doesn't exist in the database!!!" << endl;
	}
}

void SimpleUI::performEnrollmentUpdate(const std::string& courseKey,
		const Student& updateStudent) const
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		getUserInput("\t \t \t \t Enter your choice to perform the "
				"respective operation between 0-2: ", "\\d+", choice);

		int numericChoice = stoi(choice);

		if(numericChoice >= 0 && numericChoice <= 2)
		{
			switch(numericChoice)
			{
			case 0:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to exit Update Enrollment." <<endl;
				exitFlag = true;
			}
			break;
			case 1:
			{
				cout << endl << "\t \t \t \t You chose option : " << numericChoice
						<< " to Delete Enrollment." <<endl;

				this->m_db.deleteEnrollment(stoi(courseKey),
						updateStudent.getMatrikelNumber());
			}
			break;
			case 2:
			{
				cout << endl << "\t \t \t \t You chose option : " << numericChoice
						<< " to update Grade." <<endl;

				string grade = "0";

				getUserInput("\t \t \t \t \t Enter Grade to Update - 1.0 to 4.0: ",
						"^[1-3](\\.[037])?$|^4\\.0$", grade);

				this->m_db.updateGrade(stoi(courseKey), (stof(grade)),
						updateStudent.getMatrikelNumber());
			}
			break;
			}
		}
		else
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-2]" << endl;
		}
	}
}
