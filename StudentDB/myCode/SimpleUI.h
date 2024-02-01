/*!
 * @file SimpleUI.h
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
#include <fstream>

/*!
 * @class SimpleUI
 * @brief Represents a simple user interface for interacting
 * with a Student Database.
 */
class SimpleUI
{
private:
	/*!
	 * @var m_db - A reference to the StudentDb class.
	 */
	StudentDb& m_db;

private:
	/*!
	 * @brief Get user inputs for creating a new course.
	 */
	void getUserInputsforNewCourse() const;

	/*!
	 * @brief List's all courses.
	 */
	void listCourses() const;

	/*!
	 * @brief Get user inputs for adding a new student.
	 */
	void getUserInputsforNewStudent() const;

	/*!
	 * @brief Get user inputs for enrolling a student in a course.
	 */
	void getUserInputforNewEnrollment() const;

	/*!
	 * @brief Print details of a student, including enrolled
	 * courses and results.
	 *
	 * Queries the user for a matrikel number and prints the
	 * corresponding student details.
	 */
	void printStudent() const;

	/*!
	 * @brief Search for students based on a provided string.
	 *
	 * Queries the user for a string and prints the matrikel number,
	 * last name, and first name of all students having the provided
	 * string as a substring in their first or last name.
	 */
	void searchStudent() const;

	/*!
	 * @brief Get user inputs for updating student information.
	 */
	void getUserInputforStudentUpdate() const;

	/*!
	 * @brief Perform updates on a Student object.
	 *
	 * @param updateStudent Reference to a Student object.
	 */
	void performStudentUpdate(unsigned int matrikelNumber,
			const Student& updateStudent) const;

	/*!
	 * @brief Get user inputs for updating student's address information.
	 *
	 * @param matrikelNumber The matrikel number of the student.
	 * @param updateStudent Reference to a Student object.
	 */
	void getUserInputforAddressUpdate(unsigned int matrikelNumber,
			const Student& updateStudent) const;

	/*!
	 * @brief Get user inputs for updating student's enrollment information.
	 *
	 * @param matrikelNumber The matrikel number of the student.
	 * @param updateStudent Reference to a Student object.
	 */
	void getUserInputforEnrollmentUpdate(unsigned int matrikelNumber,
			const Student& updateStudent) const;

	/*!
	 * @brief Perform updates on a student's enrollment information.
	 *
	 * @param courseKey The key of the course to be updated.
	 * @param updateStudent Reference to a Student object.
	 */
	void performEnrollmentUpdate(const std::string& courseKey,
			const Student& updateStudent) const;

public:
	/*!
	 * @brief Parameterized constructor for SimpleUI.
	 *
	 * Initializes the SimpleUI class with a reference
	 * to a StudentDb object.
	 *
	 * @param db A reference to the StudentDb class.
	 */
	SimpleUI(StudentDb& db);

	/*!
	 * @brief Default destructor for the SimpleUI class.
	 */
	virtual ~SimpleUI();

	/*!
	 * @brief Lists all the properties available in the database,
	 * requests input from the user,
	 *        and executes the respective operation.
	 */
	void run() const;
};


#endif /* SIMPLEUI_H_ */
