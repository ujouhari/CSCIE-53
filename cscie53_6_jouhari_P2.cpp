/*
PROBLEM 2:
Create a class called Employee to store: employee id, first name, last name, pay amount (as a floating
point number).
Create the following method functions for Employee:
 Constructor
 Display an Employee
 Increase pay by a percentage
Create an array of (5) Employees
Create a function called updatePay() that takes as input a pointer to the array of Employees, the number
of items in the array and a raise percentage (as an integer) and optional id. If id is provded, update the
salary value for that Employee by the amount of the raise. If it is not provided, update all employees.
Create code to test your class and function.
Ground Rules: You may create any additional methods for the class that you feel will be helpful. All
data members should be private.
*/

#include <iostream>
#include <ctype.h>
#include <string>
using namespace std;

const int SIZE = 5;

class Employee{
private:
	int m_employee_id;
	string m_first_name;
	string m_last_name;
	float m_salary;

public:
	//define default constructor
	Employee();
	//define constructor with employee parameters
	Employee(int employee_id, string first_name, string last_name, float salary);
	void display();
	void update_pay(Employee *parray_employees, int num_items, int raise, int id);

};
Employee::Employee()
{ }

Employee::Employee(int employee_id, string first_name, string last_name, float salary):
	m_employee_id(employee_id), m_first_name(first_name), m_last_name(last_name), m_salary(salary)
{ }

// Function to display values of Employee.
void Employee::display()
{
	cout << m_employee_id << " " << m_first_name << " " << m_last_name << ":" << m_salary << endl;
}

//Function to update pay of employee
void Employee::update_pay(Employee *parray_employees, int num_items, int raise, int id = 0)
{
	//in this case, max employee ID is the same as total num of items so return if id > num_items.
	if (id > num_items)
	{
		cout << "Employee ID not defined" << endl;
		return;
	}
	
	//Default condition: if id is zero, update all salaries
	if (id == 0)
	{
		for (int i = 0; i < num_items; i++)
		{
			parray_employees[i].m_salary = parray_employees[i].m_salary + (parray_employees[i].m_salary * raise/100);
		}
	}

	//Otherwise update salary only for employee with specified ID.
	else
	{
		for (int i = 0; i < num_items; i++)
		{
			if (id == parray_employees[i].m_employee_id)
			{
				parray_employees[i].m_salary = parray_employees[i].m_salary + (parray_employees[i].m_salary * raise / 100);
			}
		}
	}
}

int main()
{
	Employee e;
	//Create an array of 5 elements, each element is an Employee object.
	Employee array_employees[SIZE] = {
	Employee(1, "Merideth", "Gray", 7000),
	Employee(2, "Derek", "Sheperd", 8000),
	Employee(3, "Miranda", "Bailey", 10000),
	Employee(4, "Chisty", "Yang", 9000),
	Employee(5, "Denny", "Duquette", 10000),
	};

	cout << "Original array of employees" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		array_employees[i].display();
	}
	cout << endl; 

	int raise = 10;
	int id = 3;
	e.update_pay(array_employees, SIZE, raise, id);
	cout << "Array after 10% raise to employee 3:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		array_employees[i].display();
	}
	cout << endl;

	e.update_pay(array_employees, SIZE, raise);
	cout << "Array after 10% raise to all employees:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		array_employees[i].display();
	}
	cout << endl;

	int id2 = 7;
	e.update_pay(array_employees, SIZE, raise, id2);

	system("pause");
	return 0;
}
