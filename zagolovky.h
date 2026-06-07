#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

// Перечисление должностей
enum class Position {
    JUNIOR,
    MIDDLE,
    SENIOR,
    TEAM_LEAD,
    MANAGER
};

// Перечисление отделов
enum class Department {
    DEVELOPMENT,
    TESTING,
    HR,
    SALES,
    ADMIN
};

// Класс, моделирующий одного сотрудника
class Employee {
private:
    int id;                    // Табельный номер (первичный ключ)
    std::string fullName;      // Фамилия, имя, отчество
    Position position;         // Должность (enum)
    Department department;     // Отдел (enum)
    double salary;             // Заработная плата
    std::string phoneNumber;   // Контактный телефон

public:
    // Конструкторы
    Employee();
    Employee(int id, const std::string& name, Position pos,
        Department dept, double salary, const std::string& phone);

    // Геттеры
    int getId() const;
    std::string getFullName() const;
    Position getPosition() const;
    Department getDepartment() const;
    double getSalary() const;
    std::string getPhoneNumber() const;

    // Сеттеры
    void setFullName(const std::string& name);
    void setPosition(Position pos);
    void setDepartment(Department dept);
    void setSalary(double salary);
    void setPhoneNumber(const std::string& phone);

    // Вспомогательные статические методы
    static std::string positionToString(Position pos);
    static std::string departmentToString(Department dept);
    static Position stringToPosition(const std::string& str);
    static Department stringToDepartment(const std::string& str);

    // Вывод на экран
    void display() const;

    // Сериализация в строку и обратно (для сохранения/загрузки)
    std::string toFileString() const;
    static Employee fromFileString(const std::string& line);
};

// Класс — хранилище сотрудников и операций над ними
class Database {
private:
    std::vector<Employee> employees;
    std::string filename;

public:
    Database(const std::string& filename = "employees.mydb");

    // Основные операции CRUD
    void addEmployee(const Employee& emp);
    void removeEmployee(int id);
    void editEmployee(int id);
    Employee* findEmployeeById(int id);

    // Отображение и поиск
    void displayAll() const;
    void searchByName(const std::string& name) const;
    void searchByDepartment(Department dept) const;

    // Работа с файлами
    void saveToFile();
    void loadFromFile();
    void exportToCSV(const std::string& csvFilename) const;
};

#endif
