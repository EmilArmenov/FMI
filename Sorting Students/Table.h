#pragma once
#include "DArray.h"
#include "Student.h"

const int MAX_DATA_LENGTH = 50;
const int MAX_LINE_LENGTH = 1024;

//table header: name, age, subject, grade, date
class Table 
{
public:
	//opens a file by the given @path and loads
	//its content into the studen array
	Table(const char* path);

	~Table();

	//@what - by which column the table should be sorted
	//@order - ascending or descending print screen order
	void sort(const char* what, const char* order);

	void printDesc()const;
	void printAsc()const;

private:
	//uses merge sort
	void sortByName(int left, int right);
	//uses heap sort
	void sortByAge();
	//uses merge sort
	void sortBySubject(int left, int right);
	//uses counting sort
	void sortByGrade();
	//uses merge sort
	void sortByDate(int left, int right);

private:
	void buildMaxHeap(int parent, int length);
	void mergeSorted(int left, int mid, int right, const char* data);

private:
	void loadFile(const char* path);

private:
	DynamicArray<Student> student;

private:
	Table(const Table&) = delete;
	Table& operator=(const Table&) = delete;
};
