#include "Table.h"

Table::Table(const char* path)
{
	loadFile(path);
}

Table::~Table()
{}

void Table::sort(const char* what, const char* order)
{
	if (strcmp(what, "name") == 0)
		sortByName(0, student.getSize() - 1);

	else if (strcmp(what, "age") == 0)
		sortByAge();

	else if (strcmp(what, "subject") == 0)
		sortBySubject(0, student.getSize() - 1);
	
	else if (strcmp(what, "grade") == 0)
		sortByGrade();

	else if (strcmp(what, "date") == 0)
		sortByDate(0, student.getSize() - 1);

	else
		return;

	if (strcmp(order, "asc") == 0)
		printAsc();
	
	else
		printDesc();
}

void Table::sortByName(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		sortByName(left, mid);
		sortByName(mid + 1, right);

		mergeSorted(left, mid, right, "name");
	}
}

void Table::sortByAge()
{
	for (int i = student.getSize() / 2 - 1; i >= 0; i--)
		buildMaxHeap(i, student.getSize());

	for (int i = student.getSize() - 1; i >= 0; i--)
	{
		student.swap(student[i], student[0]);
		buildMaxHeap(0, i);
	}
}

void Table::sortBySubject(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		sortBySubject(left, mid);
		sortBySubject(mid + 1, right);

		mergeSorted(left, mid, right, "subject");
	}
}

//in this function we extract by 2 because
//we want to align the grades with the indexes of container array
void Table::sortByGrade()
{
	const int gradesContainerLength = 5;   //number of grades { 2 3 4 5 6 }

	unsigned short container[gradesContainerLength] = {};

	for (int i = 0; i < student.getSize(); i++)
		container[student[i].getGrade() - 2]++;

	for (int i = 1; i < gradesContainerLength; i++)
		container[i] += container[i - 1];
	
	DynamicArray<Student> temp(student.getSize());

	for (int i = 0; i < student.getSize(); i++)
	{
		temp.insertAt(container[student[i].getGrade() - 2] - 1, student[i]);
		container[student[i].getGrade() - 2]--;
	}

	student = temp;
}

void Table::sortByDate(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		sortByDate(left, mid);
		sortByDate(mid + 1, right);

		mergeSorted(left, mid, right, "date");
	}
}

void Table::printDesc() const
{
	for (int i = student.getSize()-1; i >= 0; i--)
		std::cout << student[i];
}

void Table::printAsc()const
{
	for (int i = 0; i < student.getSize(); i++)
		std::cout << student[i];
}

void Table::buildMaxHeap(int parent, int length)
{
	int largest = parent;
	int left = 2 * parent + 1;
	int right = 2 * parent + 2;

	if (left<length && student[left].getAge()>student[largest].getAge())
		largest = left;
	
	if (right<length && student[right].getAge()>student[largest].getAge())
		largest = right;

	if (largest != parent)
	{
		student.swap(student[parent], student[largest]);
		parent = largest;
		buildMaxHeap(parent, length);
	}
}

void Table::mergeSorted(int left, int mid, int right, const char* data)
{
	int lenA = mid - left + 1;
	int lenB = right - mid;
	DynamicArray<Student> A, B;

	for (int i = 0; i < lenA; i++)
		A.add(student[left + i]);

	for (int i = 0; i < lenB; i++)
		B.add(student[mid + 1 + i]);

	int i, j, k;
	for (i = 0, j = 0, k = left; i < lenA && j < lenB; k++)
	{
		if (strcmp(A[i].getData(data), B[j].getData(data)) <= 0)
		{
			student[k] = A[i];
			i++;
		}
		else
		{
			student[k] = B[j];
			j++;
		}
	}

	while (i < lenA)
	{
		student[k] = A[i];
		i++;
		k++;
	}

	while (j < lenB)
	{
		student[k] = B[j];
		j++;
		k++;
	}
}

void Table::loadFile(const char * path)
{
	std::ifstream file(path);
	file.ignore(MAX_LINE_LENGTH, '\n');  // skips the header of the file

	char name[MAX_DATA_LENGTH];
	unsigned short age;
	char subject[MAX_DATA_LENGTH];
	unsigned short grade;
	char date[MAX_DATA_LENGTH];

	while (true)
	{
		if (file.eof())
			break;

		file.getline(name, MAX_DATA_LENGTH, ',');
		file >> age;
		file.ignore();
		file.getline(subject, MAX_DATA_LENGTH, ',');
		file >> grade;
		file.ignore();
		file.getline(date, MAX_DATA_LENGTH, '\n');
		if (file.bad())
		{
			file.clear();
			continue;
		}

		student.add(Student(name, age, subject, grade, date));
	}

	file.clear();
	file.close();
}
