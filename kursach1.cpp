#include "zagolovky.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

// ==================== Employee ====================

Employee::Employee()
    : id(0), fullName(""), position(Position::JUNIOR),
    department(Department::DEVELOPMENT), salary(0.0), phoneNumber("") {
}

Employee::Employee(int id, const std::string& name, Position pos,
    Department dept, double salary, const std::string& phone)
    : id(id), fullName(name), position(pos), department(dept),
    salary(salary), phoneNumber(phone) {
}

int Employee::getId() const { return id; }
std::string Employee::getFullName() const { return fullName; }
Position Employee::getPosition() const { return position; }
Department Employee::getDepartment() const { return department; }
double Employee::getSalary() const { return salary; }
std::string Employee::getPhoneNumber() const { return phoneNumber; }

void Employee::setFullName(const std::string& name) { fullName = name; }
void Employee::setPosition(Position pos) { position = pos; }
void Employee::setDepartment(Department dept) { department = dept; }
void Employee::setSalary(double s) { salary = s; }
void Employee::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }

std::string Employee::positionToString(Position pos) {
    switch (pos) {
    case Position::JUNIOR:
        return "Junior";
    case Position::MIDDLE:
        return "Middle";
    case Position::SENIOR:
        return "Senior";
    case Position::TEAM_LEAD:
        return "Team Lead";
    case Position::MANAGER:
        return "Manager";
    default:
        return "Unknown";
    }
}

std::string Employee::departmentToString(Department dept) {
    switch (dept) {
    case Department::DEVELOPMENT:
        return "Development";
    case Department::TESTING:
        return "Testing";
    case Department::HR:
        return "HR";
    case Department::SALES:
        return "Sales";
    case Department::ADMIN:
        return "Administration";
    default:
        return "Unknown";
    }
}

Position Employee::stringToPosition(const std::string& str) {
    if (str == "Junior")
        return Position::JUNIOR;
    if (str == "Middle")    
        return Position::MIDDLE;
    if (str == "Senior")
        return Position::SENIOR;
    if (str == "Team Lead" || str == "TeamLead")
        return Position::TEAM_LEAD;
    if (str == "Manager")   
        return Position::MANAGER;
    return Position::JUNIOR;
}

Department Employee::stringToDepartment(const std::string& str) {
    if (str == "Development")
        return Department::DEVELOPMENT;
    if (str == "Testing")
        return Department::TESTING;
    if (str == "HR")
        return Department::HR;
    if (str == "Sales")
        return Department::SALES;
    if (str == "Administration" || str == "Admin")
        return Department::ADMIN;
    return Department::DEVELOPMENT;
}

void Employee::display() const {
    std::cout << std::left
        << "ID: " << std::setw(5) << id << " | "
        << std::setw(50) << fullName << " | "
        << std::setw(12) << positionToString(position) << " | "
        << std::setw(14) << departmentToString(department) << " | "
        << "Зарплата: " << std::setw(10) << salary << " | "
        << "Тел: " << phoneNumber
        << std::endl;
}

std::string Employee::toFileString() const {
    std::ostringstream oss;
    oss << id << "|"
        << fullName << "|"
        << positionToString(position) << "|"
        << departmentToString(department) << "|"
        << salary << "|"
        << phoneNumber;
    return oss.str();
}

Employee Employee::fromFileString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> fields;

    while (std::getline(iss, token, '|')) {
        fields.push_back(token);
    }

    if (fields.size() < 6) {
        return Employee();
    }

    try {
        int id = std::stoi(fields[0]);
        std::string name = fields[1];
        Position pos = stringToPosition(fields[2]);
        Department dept = stringToDepartment(fields[3]);
        double salary = std::stod(fields[4]);
        std::string phone = fields[5];
        return Employee(id, name, pos, dept, salary, phone);
    }
    catch (const std::exception&) {
        // Строка испорчена — возвращаем пустого сотрудника
        return Employee();
    }
}

// ==================== Database ====================

Database::Database(const std::string& filename) : filename(filename) {}

void Database::addEmployee(const Employee& emp) {
    for (const auto& e : employees) {
        if (e.getId() == emp.getId()) {
            std::cout << "Ошибка: сотрудник с ID " << emp.getId()
                << " уже существует.\n";
            return;
        }
    }
    employees.push_back(emp);
    std::cout << "Сотрудник добавлен!\n";
}

void Database::removeEmployee(int id) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [id](const Employee& e) { return e.getId() == id; });

    if (it != employees.end()) {
        employees.erase(it);
        std::cout << "Сотрудник с ID " << id << " удалён.\n";
    }
    else {
        std::cout << "Сотрудник с ID " << id << " не найден.\n";
    }
}

void Database::editEmployee(int id) {
    Employee* emp = findEmployeeById(id);
    if (emp == nullptr) {
        std::cout << "Сотрудник с ID " << id << " не найден.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name;
    std::cout << "Новое ФИО (оставьте пустым, чтобы не менять): ";
    std::getline(std::cin, name);
    if (!name.empty()) {
        emp->setFullName(name);
    }

    std::string posStr;
    std::cout << "Должность (Junior/Middle/Senior/Team Lead/Manager, "
        << "оставьте пустым, чтобы не менять): ";
    std::getline(std::cin, posStr);
    if (!posStr.empty()) {
        emp->setPosition(Employee::stringToPosition(posStr));
    }

    std::string deptStr;
    std::cout << "Отдел (Development/Testing/HR/Sales/Admin, "
        << "оставьте пустым, чтобы не менять): ";
    std::getline(std::cin, deptStr);
    if (!deptStr.empty()) {
        emp->setDepartment(Employee::stringToDepartment(deptStr));
    }

    std::string salaryStr;
    std::cout << "Зарплата (оставьте пустым, чтобы не менять): ";
    std::getline(std::cin, salaryStr);
    if (!salaryStr.empty()) {
        try {
            emp->setSalary(std::stod(salaryStr));
        }
        catch (const std::exception&) {
            std::cout << "Некорректное значение зарплаты. Поле не изменено.\n";
        }
    }

    std::string phone;
    std::cout << "Телефон (оставьте пустым, чтобы не менять): ";
    std::getline(std::cin, phone);
    if (!phone.empty()) {
        emp->setPhoneNumber(phone);
    }

    std::cout << "Запись обновлена.\n";
}

Employee* Database::findEmployeeById(int id) {
    for (auto& e : employees) {
        if (e.getId() == id) {
            return &e;
        }
    }
    return nullptr;
}

void Database::displayAll() const {
    if (employees.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    std::cout << "\nСПИСОК СОТРУДНИКОВ:\n";
    for (const auto& e : employees) {
        e.display();
    }
}

void Database::searchByName(const std::string& name) const {
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
        [](unsigned char c) { return std::tolower(c); });

    bool found = false;
    for (const auto& e : employees) {
        std::string full = e.getFullName();
        std::string lowerFull = full;
        std::transform(lowerFull.begin(), lowerFull.end(), lowerFull.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (lowerFull.find(lowerName) != std::string::npos) {
            e.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Сотрудников с именем, содержащим \"" << name
            << "\", не найдено.\n";
    }
}

void Database::searchByDepartment(Department dept) const {
    bool found = false;
    for (const auto& e : employees) {
        if (e.getDepartment() == dept) {
            e.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Сотрудников в отделе "
            << Employee::departmentToString(dept) << " не найдено.\n";
    }
}

void Database::saveToFile() {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename
            << " для записи.\n";
        return;
    }
    for (const auto& e : employees) {
        outFile << e.toFileString() << '\n';
    }
    outFile.close();
    std::cout << "База данных сохранена в " << filename << ".\n";
}

void Database::loadFromFile() {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "Файл " << filename
            << " не найден. Будет создана новая база.\n";
        return;
    }

    employees.clear();
    std::string line;
    int loadedCount = 0;
    int errorCount = 0;

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }
        Employee emp = Employee::fromFileString(line);
        if (emp.getId() == 0 && emp.getFullName().empty()) {
            // fromFileString вернула пустого сотрудника — строка испорчена
            ++errorCount;
        }
        else {
            employees.push_back(emp);
            ++loadedCount;
        }
    }

    inFile.close();
    std::cout << "Загружено " << loadedCount << " записей из "
        << filename << ".\n";
    if (errorCount > 0) {
        std::cout << "Пропущено " << errorCount
            << " испорченных строк.\n";
    }
}

void Database::exportToCSV(const std::string& csvFilename) const {
    std::ofstream outFile(csvFilename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << csvFilename
            << " для записи.\n";
        return;
    }
    outFile << "\xEF\xBB\xBF";
    outFile << "ID,ФИО,Должность,Отдел,Зарплата,Телефон\n";
    for (const auto& e : employees) {
        outFile << e.getId() << ","
            << "\"" << e.getFullName() << "\","
            << Employee::positionToString(e.getPosition()) << ","
            << Employee::departmentToString(e.getDepartment()) << ","
            << e.getSalary() << ","
            << e.getPhoneNumber() << "\n";
    }

    outFile.close();
    std::cout << "Данные экспортированы в " << csvFilename << ".\n";
}