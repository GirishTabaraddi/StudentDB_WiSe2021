/*!
 * @file Course.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Course.h"

#include "BlockCourse.h"
#include "WeeklyCourse.h"

using namespace std;

std::map<unsigned char, std::string> Course::m_majorById =
{
		{'A', "Automation"},
		{'E', "Embedded Systems"},
		{'C', "Communication"},
		{'P', "Power"}
};

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints, std::string semester) : m_courseKey(courseKey), m_title(title),
				m_creditPoints(creditPoints)
{
	setMajor(major);
	setSemester(semester);
}

void Course::setMajor(std::string major)
{
	for(const auto& itr : this->getmajorById())
	{
		if(boost::algorithm::icontains(itr.second, major))
		{
			this->m_major = toupper(major[0]);
		}
	}
}

const std::map<unsigned char, std::string> Course::getmajorById()
{
	return Course::m_majorById;
}

const unsigned int Course::getcourseKey() const
{
	return this->m_courseKey;
}

const std::string Course::gettitle() const
{
	return this->m_title;
}

const unsigned char Course::getmajor() const
{
	return this->m_major;
}

const float Course::getcreditPoints() const
{
	return this->m_creditPoints;
}

Course::~Course()
{
}

void Course::write(std::ostream &out) const
{
	auto itr = this->m_majorById.find(this->m_major);

	if(itr != this->m_majorById.end())
	{
		ostringstream oss;

		oss << fixed << setprecision(1) << this->m_creditPoints;

		string creditpoints = oss.str();

		out << to_string(this->m_courseKey) << ";" << this->m_title << ";"
				<< this->m_majorById.at(this->m_major) << ";" << creditpoints
				<< ";" << this->getSemester();
	}
}

std::unique_ptr<Course> Course::read(std::istream &in)
{
	string inStr;

	getline(in, inStr);

	string courseType = splitAt(inStr, ';');

	if(courseType == "B" || courseType == "b")
	{
		istringstream iss(inStr);

		unique_ptr<BlockCourse> blockCoursePtr = BlockCourse::read(iss);

		return blockCoursePtr;
	}
	else if(courseType == "W" || courseType == "w")
	{
		istringstream iss(inStr);

		unique_ptr<WeeklyCourse> weeklyCoursePtr = WeeklyCourse::read(iss);

		return weeklyCoursePtr;
	}

	return nullptr;
}

void Course::setSemester(std::string semester)
{
	if(boost::algorithm::icontains("SoSe2020", semester))
	{
		this->m_semester = -3;
	}
	else if(boost::algorithm::icontains("WiSe2020", semester))
	{
		this->m_semester = -2;
	}
	else if(boost::algorithm::icontains("SoSe2021", semester))
	{
		this->m_semester = -1;
	}
	else if(boost::algorithm::icontains("WiSe2021", semester))
	{
		this->m_semester = 0;
	}
	else if(boost::algorithm::icontains("SoSe2022", semester))
	{
		this->m_semester = 1;
	}
	else if(boost::algorithm::icontains("WiSe2022", semester))
	{
		this->m_semester = 2;
	}
	else if(boost::algorithm::icontains("SoSe2023", semester))
	{
		this->m_semester = 3;
	}
	else if(boost::algorithm::icontains("WiSe2023", semester))
	{
		this->m_semester = 4;
	}

	else
	{
		cout << "Invalid Argument" << endl;
	}
}

std::string Course::getSemester() const
{
	switch(this->m_semester)
	{
	case -3:
	{
		return ("SoSe2020");
	}
	break;
	case -2:
	{
		return ("WiSe2020");
	}
	break;
	case -1:
	{
		return ("SoSe2021");
	}
	break;
	case 0:
	{
		return ("WiSe2021");
	}
	break;
	case 1:
	{
		return ("SoSe2022");
	}
	break;
	case 2:
	{
		return ("WiSe2022");
	}
	break;
	case 3:
	{
		return ("SoSe2023");
	}
	break;
	case 4:
	{
		return ("WiSe2023");
	}
	break;
	default:
	{
		return ("Invalid argument");
		break;
	}
	}
}

Poco::JSON::Object::Ptr Course::toJson() const
{
	Poco::JSON::Object::Ptr returnObj = new Poco::JSON::Object;

	returnObj->set("courseKey", this->m_courseKey);
	returnObj->set("title", this->m_title);
	returnObj->set("major", this->m_majorById.at(this->m_major));
	returnObj->set("semester", getSemester());
	returnObj->set("creditPoints", this->m_creditPoints);

	return returnObj;
}

std::string Course::timetoString(const Poco::Data::Time time)
{
	int hours = time.hour();
	int minutes = time.minute();

	ostringstream oss;

	oss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes;

	return oss.str();
}

std::string Course::datetoString(const Poco::Data::Date date)
{
	int year = date.year();
	int month = date.month();
	int day = date.day();

	ostringstream oss;

	oss << setw(2) << setfill('0') << day << "." << setw(2) << setfill('0')
			<< month << "." << year;

	return oss.str();
}

Poco::Data::Time Course::timeFromString(const std::string time)
{
	regex timePattern(R"((\d{1,2})\:(\d{1,2}))");

	Poco::DateTime pocoTime;

	int i = 0;

	if(regex_match(time, timePattern))
	{
		pocoTime = Poco::DateTimeParser::parse("%H:%M", time, i);
	}

	int hour = pocoTime.hour();
	int minutes = pocoTime.minute();
	int seconds = pocoTime.second();

	return Poco::Data::Time(hour, minutes, seconds);
}

Poco::Data::Date Course::dateFromString(const std::string date)
{
	regex datePattern(R"((\d{1,2})\.(\d{1,2})\.(\d{4}))");

	smatch match;

	Poco::DateTime dateTime;

	if(regex_match(date, match, datePattern))
	{
		int year = stoi(match[3].str());
		int month = stoi(match[2].str());
		int day = stoi(match[1].str());

		dateTime.assign(year, month, day);
	}

	return Poco::Data::Date(dateTime.year(), dateTime.month(), dateTime.day());
}
