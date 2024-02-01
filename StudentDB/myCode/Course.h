/*!
 * @file Course.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <map>
#include <iomanip>

#include "helperFunctions.h"

class BlockCourse;  ///< Forward declaration
class WeeklyCourse; ///< Forward declaration

/*!
 * @class Course
 * @brief Represents a course with relevant information
 * such as title, major, and credit points.
 *
 * This class encapsulates the properties of a course,
 * including its title, major, course key, and credit points.
 * It provides methods to access and manipulate these attributes.
 */
class Course
{
private:
	/*!
	 * @var m_majorByID - A map storing major IDs mapped
	 * to their corresponding strings.
	 */
	static std::map<unsigned char, std::string> m_majorById;

	/*!
	 * @var m_courseKey - A variable that stores the course key.
	 */
	unsigned int m_courseKey;

	/*!
	 * @var m_title - A private member to store the course title.
	 */
	std::string m_title;

	/*!
	 * @var m_major - This member stores the major of the course added.
	 */
	unsigned char m_major;

	/*!
	 * @var m_creditPoints - This member stores the credit points of the course.
	 */
	float m_creditPoints;

	/*!
	* @param semester the semester in the format "WiSe2021", "SoSe2022",
	* "WiSe2022" etc. Case is not checked, i.e. "wise2021" or even "wISe2022"
	* are acceptable values
	* @throws invalid_argument if the argument violates the proper format
	*/
	int m_semester;

private:

	/*!
	 * @brief Sets the major based on the first character of the given major string.
	 *
	 * This method is responsible for setting the major attribute based on the first
	 * character of the given major string. It ensures that the major string is not empty
	 * before assigning the first character to m_major.
	 *
	 * @param major A string representing the major.
	 */
	void setMajor(std::string major);

	/**
	 * @brief Set the semester for the enrollment.
	 *
	 * This function sets the semester for the current enrollment based on the provided
	 * string representation of the semester.
	 *
	 * @param semester String representation of the semester to set.
	 */
	void setSemester(std::string semester);

public:
	/*!
	 * @brief Parameterized constructor for initializing a Course object.
	 *
	 * This constructor takes the necessary parameters to initialize a Course object.
	 * It sets the course key, title, major, and credit points using the provided values.
	 * Additionally, it calls setMajor and setCreditPoints methods to set the major and
	 * credit points based on the provided major string and course key.
	 *
	 * @param courseKey 	-	The unique identifier for the course.
	 * @param title 		-	The title of the course.
	 * @param major 		-	The major associated with the course.
	 * @param creditPoints 	-	The credit points assigned to the course.
	 */
	Course(unsigned int courseKey, std::string title, std::string major, float creditPoints, std::string semester);

	/*!
	 * @brief Destructor of class Course.
	 */
	virtual ~Course();

	/*!
	 * @brief Getter method to obtain the map of major IDs.
	 *
	 * This method returns the value of the m_majorById member.
	 *
	 * @return A map containing major IDs and their corresponding strings.
	 */
	static const std::map<unsigned char, std::string> getmajorById();

	/*!
	 * @brief Getter method to obtain the course key.
	 *
	 * This method returns the course key.
	 *
	 * @return An unsigned integer representing the course key.
	 */
	const unsigned int getcourseKey() const;

	/*!
	 * @brief Getter method to obtain the title of the course.
	 *
	 * This method returns the title of the course.
	 *
	 * @return A string representing the title of the course.
	 */
	const std::string gettitle() const;

	/*!
	 * @brief Getter method to obtain the major of the course.
	 *
	 * This method returns the major of the course as an unsigned char.
	 *
	 * @return An unsigned char representing the major of the course.
	 */
	const unsigned char getmajor() const;

	/*!
	 * @brief Getter method to obtain the credit points of the course.
	 *
	 * This method returns the credit points assigned to the course.
	 *
	 * @return A float representing the credit points of the course.
	 */
	const float getcreditPoints() const;

	/*!
	* Returns the semester in which the course takes or took place as an
	* abbreviated string in the format "WiSe2021", "SoSe2022", "WiSe2022" etc.
	*
	* @return the semester
	*/
	std::string getSemester() const;

	/*!
	 * @brief Write the object's data to the provided output stream.
	 *
	 * This method is pure virtual and intended to be overridden by derived classes
	 * to write their specific data to the output stream. It allows objects to
	 * represent themselves in a standardized format when output is needed,
	 * such as writing to a file or printing to the console.
	 *
	 * @param out The output stream where the object's data will be written.
	 */
	virtual void write(std::ostream& out) const;

	/*!
	 * @brief Reads a Course from the input stream.
	 *
	 * This static member function reads a Course from the provided input stream.
	 * It reads a line from the stream, determines the course type, and delegates
	 * the reading process to the corresponding derived class (BlockCourse or WeeklyCourse).
	 * It returns a unique pointer to the dynamically allocated Course object.
	 *
	 * @param in The input stream from which to read the Course.
	 * @return A unique pointer to the dynamically allocated Course object,
	 * or nullptr if an unsupported course type is encountered.
	 */
	static std::unique_ptr<Course> read(std::istream& in);

	/**
	 * @brief Convert the object to a Poco::JSON::Object::Ptr.
	 *
	 * This virtual function should be implemented by derived classes to convert the
	 * current object to a Poco::JSON::Object::Ptr, representing the object in JSON format.
	 *
	 * @return Poco::JSON::Object::Ptr representing the object in JSON.
	 *
	 * @note Derived classes must override this function to provide their own implementation.
	 */
	virtual Poco::JSON::Object::Ptr toJson() const;

protected:
    /**
     * @brief Convert Poco::Data::Time to a string representation.
     *
     * This static function converts a Poco::Data::Time object to its string representation.
     *
     * @param time Poco::Data::Time object to convert.
     * @return String representation of the time.
     */
    static std::string timetoString(const Poco::Data::Time time);

    /**
     * @brief Convert Poco::Data::Date to a string representation.
     *
     * This static function converts a Poco::Data::Date object to its string representation.
     *
     * @param date Poco::Data::Date object to convert.
     * @return String representation of the date.
     */
    static std::string datetoString(const Poco::Data::Date date);

    /**
     * @brief Convert string to Poco::Data::Time.
     *
     * This static function converts a string to a Poco::Data::Time object.
     *
     * @param time String representation of the time.
     * @return Poco::Data::Time object.
     */
    static Poco::Data::Time timeFromString(const std::string time);

    /**
     * @brief Convert string to Poco::Data::Date.
     *
     * This static function converts a string to a Poco::Data::Date object.
     *
     * @param date String representation of the date.
     * @return Poco::Data::Date object.
     */
    static Poco::Data::Date dateFromString(const std::string date);
};

#endif /* COURSE_H_ */
