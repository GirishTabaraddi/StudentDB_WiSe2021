/*!
 * @file WeeklyCourse.cpp
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "WeeklyCourse.h"

using namespace std;

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, std::string semester,
		Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
				Course(courseKey, title, major, creditPoints, semester), m_daysOfWeek(daysOfWeek),
						m_startTime(startTime), m_endTime(endTime)
{
}

WeeklyCourse::~WeeklyCourse()
{
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDaysOfWeek() const
{
	return this->m_daysOfWeek;
}

Poco::Data::Time WeeklyCourse::getStartTime() const
{
	return this->m_startTime;
}

Poco::Data::Time WeeklyCourse::getEndTime() const
{
	return this->m_endTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";

	Course::write(out);

	out << ";" << to_string(this->m_daysOfWeek)
				<< ";" << timetoString(this->m_startTime)
				<< ";" << timetoString(this->m_endTime) << endl;
}

std::unique_ptr<WeeklyCourse> WeeklyCourse::read(std::istream &in)
{
	string inStr;

	getline(in, inStr);

	string courseKey = splitAt(inStr, ';');
	string title = splitAt(inStr, ';');
	string major = splitAt(inStr, ';');
	string creditPoints = splitAt(inStr, ';');
    string semester = splitAt(inStr, ';');
	string dayOfWeek = splitAt(inStr, ';');
	string startTime = splitAt(inStr, ';');
	string endTime = splitAt(inStr, '\n');

	return make_unique<WeeklyCourse>
	(stoi(courseKey), title, major, stof(creditPoints), semester, getDayOfWeekFromString(dayOfWeek),
			timeFromString(startTime), timeFromString(endTime));
}

Poco::JSON::Object::Ptr WeeklyCourse::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	Poco::JSON::Object::Ptr courseJSON = Course::toJson();

	Poco::Dynamic::Var courseType("W");

	returnObj->set("courseType", courseType);

	for(const string& key: courseJSON->getNames())
	{
		returnObj->set(key, courseJSON->get(key));
	}

	returnObj->set("dayOfWeek", static_cast<int>(this->m_daysOfWeek));
	returnObj->set("startTime", timetoString(this->m_startTime));
	returnObj->set("endTime", timetoString(this->m_endTime));

	return returnObj;
}
