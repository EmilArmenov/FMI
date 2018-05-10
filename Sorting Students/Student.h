#pragma once
#include <fstream>
#include <iostream>

class Student
{
	friend std::ostream& operator<<(std::ostream& out, const Student& s);

public:
	Student(const char* studentName="Unknown", unsigned short newAge = 0, const char* subject = "Unknown", unsigned short grade = 2, const char* date = "Unknown");
	Student(const Student& rhs);
	Student&operator=(const Student& rhs);
	~Student();

public:
	char* getName()const;
	char* getSubject()const;
	char* getDate()const;
	unsigned short getAge()const;
	unsigned short getGrade()const;
	char* getData(const char* data)const;

private:
	char* m_studentName;
	unsigned short m_age;
	char* m_subject;
	unsigned short m_grade;
	char* m_date;

private:
	void initDynData(const char* name, const char* subject, const char* date);
	void copyFrom(const Student& rhs);
	void clear();
};
