#include "Student.h"

Student::Student(const char * studentName, unsigned short age, const char * subject, unsigned short grade, const char * date)
{
	initDynData(studentName, subject, date);
	m_age = age;
	m_grade = grade;
}

Student::Student(const Student & rhs)
{
	copyFrom(rhs);
}

Student & Student::operator=(const Student & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Student& s) 
{
	out << s.m_studentName << ' ' << s.m_age << ' ' << s.m_subject << ' ' << s.m_grade << ' ' << s.m_date << '\n';
	return out;
}

Student::~Student()
{
	clear();
}

char * Student::getName() const
{
	return m_studentName;
}

char * Student::getSubject() const
{
	return m_subject;
}

char * Student::getDate() const
{
	return m_date;
}

unsigned short Student::getAge() const
{
	return m_age;
}

unsigned short Student::getGrade() const
{
	return m_grade;
}

char * Student::getData(const char * data) const
{
	if (strcmp(data,"name")==0)
		return m_studentName;
	
	else if (strcmp(data, "subject") == 0)
		return m_subject;
	
	else if (strcmp(data, "date") == 0)
		return m_date;
	
	else
		return nullptr;
}

void Student::initDynData(const char* name, const char* subject, const char* date)
{
	try
	{
		m_studentName = new char[strlen(name) + 1];
		strcpy(m_studentName, name);

		m_subject = new char[strlen(subject) + 1];
		strcpy(m_subject, subject);

		m_date = new char[strlen(date) + 1];
		strcpy(m_date, date);
	}
	catch (const std::bad_alloc& ba)
	{
		ba.what();
		clear();
		throw;
	}
}

void Student::copyFrom(const Student & rhs)
{
	initDynData(rhs.m_studentName, rhs.m_subject, rhs.m_date);
	m_age = rhs.m_age;
	m_grade = rhs.m_grade;
}

void Student::clear()
{
	delete[] m_studentName;
	delete[] m_subject;
	delete[] m_date;
}
