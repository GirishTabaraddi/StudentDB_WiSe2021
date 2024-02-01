/*!
 * @file WeeklyCourse.h
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"

/*!
 * @class WeeklyCourse
 * @brief Represents a weekly course with specific scheduling details.
 */
class WeeklyCourse: public Course
{
private:
	/*!
	 * @var m_daysOfWeek - stores the day in which the course takes place.
	 */
	Poco::DateTime::DaysOfWeek m_daysOfWeek;

	/*!
	 * @var m_startTime - stores the start time of the course.
	 */
	Poco::Data::Time m_startTime;

	/*!
	 * @var m_endTime - stores the end time of the course.
	 */
	Poco::Data::Time m_endTime;

public:
	/*!
	 * @brief Parameterized constructor for WeeklyCourse.
	 *
	 * Initializes all members of the abstract class and derived class.
	 *
	 * @param courseKey 	Unique identifier for the course.
	 * @param title 		Title of the course.
	 * @param major 		Major associated with the course.
	 * @param creditPoints 	Number of credit points for the course.
	 * @param daysOfWeek 	Days of the week the course is scheduled (Sunday - 0, Saturday - 6).
	 * @param startTime 	Start time of the course.
	 * @param endTime 		End time of the course.
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, std::string semester, Poco::DateTime::DaysOfWeek daysOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * @brief A Default destructor for WeeklyCourse class.
	 *
	 */
	virtual ~WeeklyCourse();

	/*!
	 * @brief Getter method for the day of the week for the weekly course.
	 *
	 * @return Poco::DateTime::DaysOfWeek (Sunday - 0, Saturday - 6).
	 */
	Poco::DateTime::DaysOfWeek getDaysOfWeek() const;

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
	 * @brief Reads a WeeklyCourse object from the specified input stream.
	 *
	 * This static function reads information from the given input stream and
	 * constructs a WeeklyCourse object based on the data.
	 * The input stream is expected to contain semicolon-separated values representing
	 * course key, title, major, credit points, day of the week, start time, and end time.
	 *
	 * @param in The input stream from which the WeeklyCourse information will be read.
	 * @return A unique pointer to the constructed WeeklyCourse object.
	 */
	static std::unique_ptr<WeeklyCourse> read(std::istream& in);

	/**
	 * @brief Convert the object to a Poco::JSON::Object::Ptr.
	 *
	 * This function overrides the base class method to convert the current object to a
	 * Poco::JSON::Object::Ptr, representing the object in JSON format.
	 *
	 * @return Poco::JSON::Object::Ptr representing the object in JSON.
	 */
	Poco::JSON::Object::Ptr toJson() const override;

};

#endif /* WEEKLYCOURSE_H_ */
