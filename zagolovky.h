#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

enum class Position {
    JUNIOR,
    MIDDLE,
    SENIOR,
    TEAM_LEAD,
    MANAGER
};
enum class Department {
    DEVELOPMENT,
    TESTING,
    HR,
    SALES,
    ADMIN
};
class Employee {
private:
    int id;
    std::string fullName;
    Position position;
    Department department;
    double salary;
    std::string phoneNumber;

public:
    Employee();
    Employee(int id, const std::string& name, Position pos, Department dept, double salary, const std::string& phone);

    int getId() const;
    std::string getFullName() const;
    Position getPosition() const;
    Department getDepartment() const;
    double getSalary() const;
    std::string getPhoneNumber() const;

    void setFullName(const std::string& name);
    void setPosition(Position pos);
    void setDepartment(Department dept);
    void setSalary(double salary);
    void setPhoneNumber(const std::string& phone);

    static std::string positionToString(Position pos);
    static std::string departmentToString(Department dept);
    static Position stringToPosition(const std::string& str);
    static Department stringToDepartment(const std::string& str);

    void display() const;

    std::string toFileString() const;
    static Employee fromFileString(const std::string& line);
};

class Database {
private:
    std::vector<Employee> employees;
    std::string filename;

public:
    Database(const std::string& filename = "employees.mydb");

    void addEmployee(const Employee& emp);
    void removeEmployee(int id);
    void editEmployee(int id);
    Employee* findEmployeeById(int id);

    void displayAll() const;
    void searchByName(const std::string& name) const;
    void searchByDepartment(Department dept) const;

    void saveToFile();
    void loadFromFile();
    void exportToCSV(const std::string& csvFilename) const;
};

#endif
