/*!
 * @file BlockCourse.h
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"

/*!
 * @class BlockCourse
 * @brief Represents a block course with specific scheduling details.
 */
class BlockCourse: public Course
{
private:
	/*!
	 * @var m_startDate - stores the start date of the block course.
	 */
	Poco::Data::Date m_startDate;

	/*!
	 * @var m_endDate - stores the end date of the block course.
	 */
	Poco::Data::Date m_endDate;
	/*!
	 * @var m_startTime - stores the start time of the block course.
	 */
	Poco::Data::Time m_startTime;

	/*!
	 * @var m_endTime - stores the end time of the block course.
	 */
	Poco::Data::Time m_endTime;

public:
	/*!
	 * @brief Parameterized constructor for BlockCourse.
	 *
	 * Initializes all members of the abstract class and derived class.
	 *
	 * @param courseKey 	Unique identifier for the course.
	 * @param title 		Title of the course.
	 * @param major 		Major associated with the course.
	 * @param creditPoints	Number of credit points for the course.
	 * @param startDate 	Start date of the course.
	 * @param endDate 		End date of the course.
	 * @param startTime		Start time of the course.
	 * @param endTime 		End time of the course.
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, std::string semester, Poco::Data::Date startDate, Poco::Data::Date endDate,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * @brief Default destructor for BlockCourse class.
	 */
	virtual ~BlockCourse();

	/*!
	 * @brief Getter method for the start date of the course.
	 *
	 * @return Poco::Data::Date representing the start date.
	 */
	Poco::Data::Date getStartDate() const;

	/*!
	 * @brief Getter method for the end date of the course.
	 *
	 * @return Poco::Data::Date representing the end date.
	 */
	Poco::Data::Date getEndDate() const;

	/*!
	 * @brief Getter method for the start time of the course.
	 *
	 * @return Poco::Data::Time representing the start time.
	 */
	Poco::Data::Time getStartTime() const;

	/*!
	 * @brief Getter method for the end time of the course.
	 *
	 * @return Poco::Data::Time representing the end time.
	 */
	Poco::Data::Time getEndTime() const;

	/*!
	 * @brief Print method that outputs the data of the block course.
	 *
	 * @return String representation of the course data.
	 */
	std::string printCourse() const override;

	/**
	 * @brief Write the object's data to the provided output stream.
	 *
	 * This method is overridden from the base class. It writes the specific
	 * data of the derived class to the output stream. Objects use this method
	 * to represent themselves in a standardized format when output is needed,
	 * such as writing to a file or printing to the console.
	 *
	 * @param out The output stream where the object's data will be written.
	 */
	void write(std::ostream& out) const override;

	/*!
	 * \brief Reads a BlockCourse object from the specified input stream.
	 *
	 * This static function reads information from the given input stream and
	 * constructs a BlockCourse object based on the data.
	 * The input stream is expected to contain semicolon-separated values
	 * representing course details, including course type, course key, title,
	 * major, credit points, start date, end date, start time, and end time.
	 *
	 * \param in The input stream from which the BlockCourse information will be read.
	 * \return A unique pointer to the constructed BlockCourse object.
	 */
	static std::unique_ptr<BlockCourse> read(std::istream& in);

	/**
	 * @brief Convert the object to a Poco::JSON::Object::Ptr.
	 *
	 * This function converts the current object to a Poco::JSON::Object::Ptr,
	 * representing the object in JSON format.
	 *
	 * @return Poco::JSON::Object::Ptr representing the object in JSON.
	 *
	 * @override
	 */
	Poco::JSON::Object::Ptr toJson() const override;
};

#endif /* BLOCKCOURSE_H_ */
