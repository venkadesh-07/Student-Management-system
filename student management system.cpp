#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
    }

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
    }
};

const string FILE_NAME = "students.txt";

void saveToFile(const vector<Student>& students) {
    ofstream file(FILE_NAME);
    for (const auto& s : students) {
        file << s.id << endl << s.name << endl << s.age << endl;
    }
    file.close();
}

vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream file(FILE_NAME);

    Student s;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        students.push_back(s);
    }

    file.close();
    return students;
}

void addStudent() {
    vector<Student> students = loadFromFile();
    Student s;
    s.input();
    students.push_back(s);
    saveToFile(students);
    cout << "Student added successfully!\n";
}

void displayStudents() {
    vector<Student> students = loadFromFile();
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }

    for (const auto& s : students) {
        s.display();
    }
}

void searchStudent() {
    vector<Student> students = loadFromFile();
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    for (const auto& s : students) {
        if (s.id == id) {
            cout << "Student Found:\n";
            s.display();
            return;
        }
    }
    cout << "Student not found.\n";
}

void updateStudent() {
    vector<Student> students = loadFromFile();
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    for (auto& s : students) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();
            saveToFile(students);
            cout << "Updated successfully!\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent() {
    vector<Student> students = loadFromFile();
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            saveToFile(students);
            cout << "Deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}