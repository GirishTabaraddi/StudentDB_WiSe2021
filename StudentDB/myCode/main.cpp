//! Standard (system) header files
#include <iostream>
#include <cstdlib>

using namespace std;

//! Add your project's header files here
#include "SimpleUI.h"

#include "helperFunctions.h"

//! Main program
int main ()
{
	cout << "StudentDB started." << endl << endl;

	StudentDb Database;

	SimpleUI UI(Database);

	UI.run();

	//! Systematic Testing getSemester()

	WeeklyCourse testCourse1 = WeeklyCourse(1234, "APT", "Automation", 5.0, "SoSe2020",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse1.getSemester() == "SoSe2020", "Test case-1 failed");

	WeeklyCourse testCourse2 = WeeklyCourse(1234, "APT", "Automation", 5.0, "Some2022",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse2.getSemester() == "Some2022", "Test case-2 failed");

	WeeklyCourse testCourse3 = WeeklyCourse(1234, "APT", "Automation", 5.0, "WiSe20/21",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse3.getSemester() == "WiSe20/21", "Test case-3 failed");

	WeeklyCourse testCourse4 = WeeklyCourse(1234, "APT", "Automation", 5.0, "WiSe2020",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse4.getSemester() == "WiSe2020", "Test case-4 failed");

	WeeklyCourse testCourse5 = WeeklyCourse(1234, "APT", "Automation", 5.0, "SoSe2021",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse5.getSemester() == "SoSe2021", "Test case-5 failed");

	WeeklyCourse testCourse6 = WeeklyCourse(1234, "APT", "Automation", 5.0, "WiSe2021",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse6.getSemester() == "WiSe2021", "Test case-6 failed");

	WeeklyCourse testCourse7 = WeeklyCourse(1234, "APT", "Automation", 5.0, "SoSe2022",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse7.getSemester() == "SoSe2022", "Test case-7 failed");

	WeeklyCourse testCourse8 = WeeklyCourse(1234, "APT", "Automation", 5.0, "WiSe2022",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse8.getSemester() == "WiSe2022", "Test case-8 failed");

	WeeklyCourse testCourse9 = WeeklyCourse(1234, "APT", "Automation", 5.0, "SoSe2023",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse9.getSemester() == "SoSe2023", "Test case-9 failed");

	WeeklyCourse testCourse10 = WeeklyCourse(1234, "APT", "Automation", 5.0, "WiSe2023",
			Poco::DateTime::MONDAY, stringToPocoTimeFormatter("10:15"), stringToPocoTimeFormatter("11:45"));
	assertTrue(testCourse10.getSemester() == "WiSe2023", "Test case-10 failed");

	return 0;
}








/*!
 * @startuml

	class SimpleUI
	{
		-m_db : StudentDb&

		+SimpleUI(StudentDb& db)
		+~SimpleUI()
		+run() : void

		-getUserInputsforNewCourse() : void {query}
		-listCourses() : void {query}
		-getUserInputsforNewStudent() : void {query}
		-getUserInputforNewEnrollment() : void {query}
		-printStudent() : void {query}
        -searchStudent() : void {query}
        -getUserInputforStudentUpdate() : void {query}
        -performStudentUpdate(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
//        -getUserInputforFirstName(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
//        -getUserInputforLastName(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
//        -getUserInputforDateOfBirth(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
        -getUserInputforAddressUpdate(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
        -getUserInputforEnrollmentUpdate(unsigned int matrikelNumber, \n const Student& updateStudent) : void {query}
        -performEnrollmentUpdate(const std::string& courseKey, \n const Student& updateStudent) : void {query}
	}

	class StudentDb
	{
		-m_students : std::map<int, Student>
		-m_courses : std::map<int, std::unique_ptr<const Course>>

		+StudentDb()
        +getStudents() : std::map<int , Student>& {query}
        +getCourses() : std::map<int , std::unique_ptr<const Course>>& {query}
		+addNewCourse(std::string& courseKey, std::string& title, std::string& major, \n std::string& credits, std::string& courseType, \n std::string& startTime, std::string& endTime, \n std::string& startDate, std::string& endDate, \n std::string& dayOfWeek) : StudentDb::RC_StudentDb_t
		+addNewStudent(std::string& firstName, std::string& lastName, std::string& DoBstring, \n std::string& streetName, std::string& postalCode, \n std::string& cityName, std::string& additionalInfo) : StudentDb::RC_StudentDb_t
		+addEnrollment(std::string& matrikelNumber, std::string& semester, \n std::string& courseKey) : StudentDb::RC_StudentDb_t
        +updateFirstName(const std::string& newFirstName, unsigned int matrikelNumber) : void
        +updateLastName(const std::string& newLastName, unsigned int matrikelNumber) : void
        +updateDateOfBirth(const Poco::Data::Date& dateOfBirth, unsigned int matrikelNumber) : void
        +updateAddress(const std::string& street, const unsigned int& postalCode, \n const std::string& cityName, const std::string& additionalInfo, \n unsigned int matrikelNumber) : void
        +deleteEnrollment(const unsigned int& courseKey, const unsigned int matrikelNumber) : void
        +updateGrade(const unsigned int& courseKey, const float& newGrade, \n const unsigned int matrikelNumber) : void
        +write(std::ostream& out) : void {query}
        +read(std::istream& in) : void
        +readStudentDataFromServer(unsigned int noOfUserData) : void

        -readCoursesData(std::string& str) : void
        -readStudentsData(std::string& str) : void
        -readEnrollmentData(std::string& str) : void
        -writeCoursesData(std::ostream& out) : void {query}
        -writeStudentsData(std::ostream& out) : void {query}
        -writeEnrollmentsData(std::ostream& out) : void {query}
        -parsingJSONData(std::string& JSONData) : void
        -isValidServerDataString(const std::string& eachStr) : bool
	}

	class Student
	{
		-{static} m_nextMatrikelNumber : static unsigned int
		-m_matrikelNumber : unsigned int
		-m_firstName : std::string
		-m_lastName : std::string
		-m_dateOfBirth : Poco::Data::Date
		-m_enrollments : std::vector<Enrollment>
		-m_address : std::shared_ptr<Address>

		+Student(std::string firstName, std::string lastName,\n Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address)
		+~Student()
		+getMatrikelNumber() : unsigned int {query}
		+getFirstName() : std::string& {query}
        +getLastName() : std::string& {query}
		+getDateOfBirth() : Poco::Data::Date {query}
		+getEnrollments() : std::vector<Enrollment>& {query}
		+getAddress() : std::shared_ptr<Address> {query}
		+{static} setNextMatrikelNumber(unsigned int newMatrikelNumber) : void
        +setFirstName(const std::string& firstName) : void
        +setLastName(const std::string& lastName) : void
        +setDateOfBirth(const Poco::Data::Date& dateOfBirth) : void
        +setAddress(const std::shared_ptr<Address> address) : void
		+printStudent() : std::string {query}
		+addEnrollment(const std::string& semester, const Course* courseId) : void
		+deleteEnrollment(const unsigned int& courseKey) : void
		+updateGrade(const float& grade, const unsigned int& courseKey) : void
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in) : Student
	}

	class Address
	{
		-m_street : std::string
		-m_postalCode : unsigned short
		-m_cityName : std::string
		-m_additionalInfo : std::string

		+Address(std::string street, unsigned short postalCode,\n std::string cityName, std::string additionalInfo)
		+~Address()
		+getstreet() : std::string& {query}
		+getpostalCode() : unsigned short {query}
		+getcityName() : std::string& {query}
		+getadditionalInfo() : std::string& {query}
		+printAddress() : std::string {query}
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in) : std::shared_ptr<Address>
	}

	class Enrollment
	{
		-m_grade : float
		-m_semester : std::string
		-m_course : const Course*

		+Enrollment(std::string semester, const Course* courseObj)
		+~Enrollment()
		+getgrade() : float {query}
		+getsemester() : std::string& {query}
		+getcourse() : Course* {query}
		+setgrade(float grade) : void
		+printEnrollment() : std::string {query}
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in, const Course* courseobj) : Enrollment
	}

	abstract class Course
	{
		-{static} m_majorById : static std::map<unsigned char, std::string>
		-m_courseKey : unsigned int
		-m_title : std::string
		-m_major : unsigned char
		-m_creditPoints : float

		-setMajor(std::string major) : void

		+Course(unsigned int courseKey, std::string title,\n std::string major, float creditPoints)
		+~Course()
		+{static} getmajorById() : static std::map<unsigned char , std::string> {query}
		+getcourseKey() : unsigned int {query}
		+gettitle() : std::string {query}
		+getmajor() : unsigned char {query}
		+printCourse() : std::string {query}
		+getcreditPoints() : float {query}
		+printCourse() : std::string {query}
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in) : std::unique_ptr<Course>
	}

	class BlockCourse
	{
		-m_startDate : Poco::Data::Date
		-m_endDate : Poco::Data::Date
		-m_startTime : Poco::Data::Time
		-m_endTime : Poco::Data::Time

		+BlockCourse( unsigned int courseKey, std::string title, std::string major, \n float creditPoints, Poco::Data::Date startDate, Poco::Data::Date endDate, \n Poco::Data::Time startTime, Poco::Data::Time endTime)
		+~BlockCourse()
		+getStartDate() : Poco::Data::Date {query}
		+getEndDate() : Poco::Data::Date {query}
		+getStartTime() : Poco::Data::Time {query}
		+getEndTime() : Poco::Data::Time {query}
		+printCourse() : std::string {query}
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in) : std::unique_ptr<BlockCourse>
	}

	class WeeklyCourse
	{
		-m_daysOfWeek : Poco::DateTime::DaysOfWeek
		-m_startTime : Poco::Data::Time
		-m_endTime : Poco::Data::Time

		+WeeklyCourse(unsigned int courseKey, std::string title,\n std::string major, float creditPoints, Poco::DateTime::DaysOfWeek daysOfWeek, \n Poco::Data::Time startTime, Poco::Data::Time endTime)
		+~WeeklyCourse()
		+getDaysOfWeek() : Poco::DateTime::DaysOfWeek {query}
		+getStartTime() : Poco::Data::Time {query}
		+getEndTime() : Poco::Data::Time {query}
		+printCourse() : std::string {query}
		+write(std::ostream& out) : void {query}
		+{static} read(std::istream& in) : std::unique_ptr<WeeklyCourse>
	}

enum StudentDb::RC_StudentDb_t {
        RC_Course_Exists
        RC_Enrollment_Exists
        RC_Student_Exists
        RC_Success
        RC_Wrong_Course_Key
        RC_Wrong_MatrikelNumber
}

 * SimpleUI 	-d->  	StudentDb 	: Association
 * StudentDb 	*-d-> 	Student 	: Composition
 * StudentDb 	*-d-> 	Course 		: Composition
 * Student 		*-r-> 	Enrollment	: Composition
 * Enrollment 	o-r-> 	Course 		: Aggregation
 * Student 		*-d-> 	Address 	: Composition
 * BlockCourse 	-u-|> 	Course 		: Inheritance
 * WeeklyCourse	-u-|> 	Course 		: Inheritance

 * @enduml
 */
