/*!
 * @file Enrollment.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Enrollment.h"

using namespace std;

Enrollment::Enrollment(std::string semester, const Course* courseObj) :
		m_grade(0.0), m_semester(semester), m_course(courseObj)
{
}

Enrollment::~Enrollment()
{
}

const float Enrollment::getgrade() const
{
	return this->m_grade;
}

const std::string& Enrollment::getsemester() const
{
	return this->m_semester;
}

const Course* Enrollment::getcourse() const
{
	return this->m_course;
}

void Enrollment::setgrade(const float &grade)
{
	this->m_grade = grade;
}

void Enrollment::write(std::ostream &out) const
{
	ostringstream oss;

	oss << fixed << setprecision(1) << this->m_grade;

	out << to_string(this->m_course->getcourseKey())
					<< ";" << this->m_semester << ";" << oss.str();
}

Enrollment Enrollment::read(std::istream &in, const Course *courseobj)
{
	string inStr;

	getline(in, inStr);

	unsigned int courseKey = stoul(splitAt(inStr, ';'));
	string semester = splitAt(inStr, ';');
	float grade = stof(splitAt(inStr, ';'));

	if(courseobj->getcourseKey() == courseKey)
	{
		Enrollment readEnrollment(semester, courseobj);

		readEnrollment.setgrade(grade);

		return readEnrollment;
	}
	else
	{
		return Enrollment(semester, nullptr);
	}
}

Poco::JSON::Object::Ptr Enrollment::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	returnObj->set("semester", this->m_semester);
	returnObj->set("courseKey", getcourse()->getcourseKey());
	returnObj->set("grade", this->m_grade);

	return returnObj;
}
