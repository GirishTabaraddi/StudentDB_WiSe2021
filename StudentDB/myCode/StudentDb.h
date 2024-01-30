/*!
 * @file StudentDb.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include "Student.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

/*!
 * @class StudentDb
 * @brief Represents a database of students and
 * courses with various operations.
 */
class StudentDb
{
private:
	/*!
	 * @var m_students - A map variable that maps the student
	 * entered into the database with an integer key.
	 */
	std::map<int, Student> m_students;

	/*!
	 * @var m_courses - A map variable that stores the list of
	 * courses using a unique pointer and an integer as a key.
	 */
	std::map<int, std::unique_ptr<const Course>> m_courses;

private:
	/*!
	 * @brief Processes courses data from the input stream.
	 *
	 * This function processes courses data read from the input stream.
	 * It parses the input and updates the internal data structures accordingly.
	 *
	 * @param in The input stream containing courses data.
	 */
	void readCoursesData(std::string &str);

	/*!
	 * @brief Processes students data from the input stream.
	 *
	 * This function processes students data read from the input stream.
	 * It parses the input and updates the internal data structures accordingly.
	 *
	 * @param in The input stream containing students data.
	 */
	void readStudentsData(std::string &str);

	/*!
	 * @brief Processes enrollment data from the input stream.
	 *
	 * This function processes enrollment data read from the input stream.
	 * It parses the input and updates the internal data structures accordingly.
	 *
	 * @param in The input stream containing enrollment data.
	 */
	void readEnrollmentData(std::string &str);

	/*!
	 * @brief Print all Courses in the entire database.
	 *
	 * This method prints the details of all courses in the database
	 * to the specified output stream.
	 *
	 * @param out The output stream where course data will be printed.
	 */
	void writeCoursesData(std::ostream &out) const;

	/*!
	 * @brief Print all Students in the entire database.
	 *
	 * This method prints the details of all students in the database
	 * to the specified output stream.
	 *
	 * @param out The output stream where student data will be printed.
	 */
	void writeStudentsData(std::ostream &out) const;

	/*!
	 * @brief Print all Enrollments of the Student.
	 *
	 * This method prints the details of all enrollments for each student
	 * in the database to the specified output stream.
	 *
	 * @param out The output stream where enrollment data will be printed.
	 */
	void writeEnrollmentsData(std::ostream &out) const;

	/*!
	 * @brief Parses JSON data.
	 *
	 * This function uses POCO C++ JSON for parsing data.
	 *
	 * @param JSONData The JSON data to be parsed.
	 */
	void parsingJSONData(std::string& JSONData);

	/*!
	 * @brief Checks if the provided string is a valid server data string.
	 *
	 * @param eachStr The string to be checked.
	 * @return True if the string is valid, false otherwise.
	 */
	bool isValidServerDataString(const std::string& eachStr);

public:
	/**
	 * @brief Enum class representing return codes for
	 * Student Database operations.
	 */
	enum class RC_StudentDb_t
	{
		RC_Success,               ///< Operation completed successfully.
		RC_Wrong_Course_Key,      ///< Provided course key is incorrect or not found.
		RC_Wrong_MatrikelNumber,  ///< Provided matrikel number is incorrect or not found.
		RC_Student_Exists,        ///< Student with the given details already exists in the database.
		RC_Course_Exists,         ///< Course with the given details already exists in the database.
		RC_Enrollment_Exists,      ///< Enrollment for the student and course already exists in the database.
        RC_Invalid_Semester_Added
	};


	/*!
	 * @brief Default constructor for StudentDb class.
	 */
	StudentDb();

    /**
     * @brief Virtual destructor for the StudentDb class.
     *
     * This virtual destructor is responsible for cleaning up any resources held by the
     * StudentDb object. It is automatically called when a derived class instance goes out
     * of scope or when explicitly deleted using the `delete` keyword.
     */
    virtual ~StudentDb();

	/*!
	 * @brief Getter method to fetch the students.
	 *
	 * @return Map representing the students.
	 */
	const std::map<int, Student>& getStudents() const;

	/*!
	 * @brief Getter method to fetch the courses.
	 *
	 * @return Map representing the courses.
	 */
	const std::map<int, std::unique_ptr<const Course>>& getCourses() const;

	/*!
	 * @brief Add a new course to the database.
	 *
	 * Queries the user for the required data and
	 * creates a new course in the database.
	 *
	 * @return Return code indicating the success
	 * or failure of the operation.
	 */
	RC_StudentDb_t addNewCourse(std::string& courseKey,std::string& title,
    		std::string& major,std::string& credits, std::string& semester,
			std::string& courseType,std::string& startTime,
			std::string& endTime,std::string& startDate,
			std::string& endDate,std::string& dayOfWeek);

	/*!
	 * @brief List's all courses.
	 */
	std::string listCourses() const;

	/*!
	 * @brief Add a new student to the database.
	 *
	 * Queries the user for the required data
	 * (member data of Student and Address)
	 * and creates a new student in the database.
	 *
	 * @return Return code indicating the success or failure of the operation.
	 */
	RC_StudentDb_t addNewStudent(std::string& firstName,std::string& lastName,
			std::string& DoBstring,std::string& streetName,
			std::string& postalCode,std::string& cityName,
			std::string& additionalInfo);

	/*!
	 * @brief Add enrollment for a student.
	 *
	 * Queries the user for a matrikel number, a course id,
	 * a semester, and adds the enrollment.
	 * If the enrollment already exists, a warning message is printed.
	 *
	 * @return Return code indicating the success or failure of the operation.
	 */
	RC_StudentDb_t addEnrollment(std::string& matrikelNumber,
			std::string& semester, std::string& courseKey);

	/**
	 * @brief Update the first name of a student.
	 *
	 * @param newFirstName New first name.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void updateFirstName(const std::string& newFirstName,
			unsigned int matrikelNumber);

	/**
	 * @brief Update the last name of a student.
	 *
	 * @param newLastName New last name.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void updateLastName(const std::string& newLastName,
			unsigned int matrikelNumber);

	/**
	 * @brief Update the date of birth of a student.
	 *
	 * @param dateOfBirth New date of birth.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void updateDateOfBirth(const Poco::Data::Date& dateOfBirth,
			unsigned int matrikelNumber);

	/**
	 * @brief Update the address of a student.
	 *
	 * @param street Street name.
	 * @param postalCode Postal code.
	 * @param cityName City name.
	 * @param additionalInfo Additional address information.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void updateAddress(const std::string& street, const unsigned int& postalCode,
			const std::string& cityName, const std::string& additionalInfo,
			unsigned int matrikelNumber);

	/**
	 * @brief Delete the enrollment of a student in a course.
	 *
	 * @param courseKey Key of the course to be deleted.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void deleteEnrollment(const unsigned int& courseKey,
			const unsigned int matrikelNumber);

	/**
	 * @brief Update the grade of a student in a course.
	 *
	 * @param courseKey Key of the course.
	 * @param newGrade New grade to be assigned.
	 * @param matrikelNumber Matrikel number of the student.
	 */
	void updateGrade(const unsigned int& courseKey, const float& newGrade,
			const unsigned int matrikelNumber);

	/*!
	 * @brief Write all student and course data to the provided output stream.
	 *
	 * This method writes the data of all students and courses in the database to
	 * the specified output stream. It calls the write method of each student and
	 * course to represent themselves in a standardized format when output is needed,
	 * such as writing to a file or printing to the console.
	 *
	 * @param out The output stream where the student and course data will be written.
	 */
	void write(std::ostream& out) const;

	/*!
	 * @brief Reads data from the input stream.
	 *
	 * This function reads data from the provided input stream and processes
	 * it accordingly. The exact behavior depends on the specific implementation
	 * of the derived class.
	 *
	 * @param in The input stream to read data from.
	 */
	void read(std::istream& in);

	/*!
	 * @brief Reads data from the server.
	 *
	 * @param noOfUserData Number of user data to be read from the server.
	 */
	void readStudentDataFromServer(unsigned int noOfUserData);

	/**
	 * @brief Convert the object to a Poco::JSON::Object::Ptr.
	 *
	 * This virtual function should be implemented by derived classes to convert the
	 * current object to a Poco::JSON::Object::Ptr, representing the object in JSON format.
	 *
	 * @return Poco::JSON::Object::Ptr representing the object in JSON.
	 *
	 * @note Derived classes must override this function to provide their own implementation.
	 * @see DerivedClass::toJson() for an example of implementation.
	 */
	virtual Poco::JSON::Object::Ptr toJson() const;
};

#endif /* STUDENTDB_H_ */
