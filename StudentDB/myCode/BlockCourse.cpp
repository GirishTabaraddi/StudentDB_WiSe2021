/*!
 * @file BlockCourse.cpp
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "BlockCourse.h"

using namespace std;

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, std::string semester, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
				Course(courseKey, title, major, creditPoints, semester), m_startDate(startDate),
						m_endDate(endDate), m_startTime(startTime), m_endTime(endTime)
{
}

BlockCourse::~BlockCourse()
{
}

Poco::Data::Date BlockCourse::getStartDate() const
{
	return this->m_startDate;
}

Poco::Data::Date BlockCourse::getEndDate() const
{
	return this->m_endDate;
}

Poco::Data::Time BlockCourse::getStartTime() const
{
	return this->m_startTime;
}

Poco::Data::Time BlockCourse::getEndTime() const
{
	return this->m_endTime;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";

	Course::write(out);

	out << ";" << datetoString(this->m_startDate)
	    				<< ";" << datetoString(this->m_endDate)
						<< ";" << timetoString(this->m_startTime)
						<< ";" << timetoString(this->m_endTime)
						<< endl;
}

std::unique_ptr<BlockCourse> BlockCourse::read(std::istream &in)
{
	string inStr;

	getline(in, inStr);

	string courseKey = splitAt(inStr, ';');
	string title = splitAt(inStr, ';');
	string major = splitAt(inStr, ';');
	string creditPoints = splitAt(inStr, ';');
    string semester = splitAt(inStr, ';');
	string startDate = splitAt(inStr, ';');
	string endDate = splitAt(inStr, ';');
	string startTime = splitAt(inStr, ';');
	string endTime = splitAt(inStr, '\n');

	return make_unique<BlockCourse>(stoi(courseKey), title, major, stof(creditPoints), semester,
			dateFromString(startDate), dateFromString(endDate),
			timeFromString(startTime), timeFromString(endTime));
}

Poco::JSON::Object::Ptr BlockCourse::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	Poco::JSON::Object::Ptr courseJSON = Course::toJson();

	Poco::Dynamic::Var courseType = Poco::Dynamic::Var("B");

	returnObj->set("courseType", courseType);

	for(const string& key: courseJSON->getNames())
	{
		returnObj->set(key, courseJSON->get(key));
	}

	returnObj->set("startDate", datetoString(this->m_startDate));
	returnObj->set("endDate", datetoString(this->m_endDate));
	returnObj->set("startTime", timetoString(this->m_startTime));
	returnObj->set("endTime", timetoString(this->m_endTime));

	return returnObj;
}
