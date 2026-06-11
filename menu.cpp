#include "zagolovky.h"
#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n~~~~~~~~~~ БАЗА ДАННЫХ СОТРУДНИКОВ ~~~~~~~~~~\n";
    cout << "[1] Добавить сотрудника\n";
    cout << "[2] Показать всех сотрудников\n";
    cout << "[3] Найти сотрудника по имени\n";
    cout << "[4] Найти сотрудников по отделу\n";
    cout << "[5] Редактировать запись\n";
    cout << "[6] Удалить запись\n";
    cout << "[7] Сохранить базу в файл\n";
    cout << "[8] Загрузить базу из файла\n";
    cout << "[9] Экспорт в CSV (для сторонних организаций)\n";
    cout << "[0] Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Database db("employees.mydb");
    db.loadFromFile();
    int choice;
    do {
        showMenu();
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. \n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            int id;
            string name, phone;
            double salary;
            int posChoice, deptChoice;

            cout << "Введите ID: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }
            cin.ignore();

            cout << "Введите ФИО: ";
            getline(cin, name);

            cout << "Должность (0-Junior, 1-Middle, 2-Senior, "
                << "3-TeamLead, 4-Manager): ";
            cin >> posChoice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }

            cout << "Отдел (0-Development, 1-Testing, 2-HR, "
                << "3-Sales, 4-Admin): ";
            cin >> deptChoice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }

            cout << "Зарплата: ";
            cin >> salary;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }
            cin.ignore();

            cout << "Телефон: ";
            getline(cin, phone);

            Employee emp(id, name,
                static_cast<Position>(posChoice),
                static_cast<Department>(deptChoice),
                salary, phone);
            db.addEmployee(emp);
            break;
        }
        case 2:
            db.displayAll();
            break;
        case 3: {
            string name;
            cout << "Введите имя или часть имени для поиска: ";
            getline(cin, name);
            db.searchByName(name);
            break;
        }
        case 4: {
            int deptChoice;
            cout << "Отдел (0-Development, 1-Testing, 2-HR, "
                << "3-Sales, 4-Admin): ";
            cin >> deptChoice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }
            cin.ignore();
            db.searchByDepartment(
                static_cast<Department>(deptChoice));
            break;
        }
        case 5: {
            int id;
            cout << "Введите ID сотрудника для редактирования: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }
            db.editEmployee(id);
            break;
        }
        case 6: {
            int id;
            cout << "Введите ID сотрудника для удаления: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Возврат в меню \n";
                break;
            }
            db.removeEmployee(id);
            break;
        }
        case 7:
            db.saveToFile();
            break;
        case 8:
            db.loadFromFile();
            break;
        case 9:
            db.exportToCSV("export.csv");
            break;
        case 0:
            cout << "На этом всё.\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}