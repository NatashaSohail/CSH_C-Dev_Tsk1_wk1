#include <iostream>   
#include <fstream>   
#include <string>   
#include <sstream>   
using namespace std;

// Structure to group student data
struct Student {
    int rollNo;        
    string name;       
    int marks[5];      
    int total;        
    float average;     
    char grade;       
};

int main() {
    Student s;   // One student at a time
    int choice;
    fstream file;  // File object for read and write

    do {
        cout << "\n===== Student Result Management System =====\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            // Input student details
            cout << "Enter Roll No: ";
            cin >> s.rollNo;
            cin.ignore(); 
            cout << "Enter Name: ";
            getline(cin, s.name);
            s.total = 0;
            cout << "Enter marks of 5 subjects:\n";
            for(int i=0; i<5; i++) {
                cout << "Subject " << i+1 << ": ";
                cin >> s.marks[i];
                s.total += s.marks[i];
            }
            s.average = s.total / 5.0;
            if(s.average >= 80) s.grade = 'A';
            else if(s.average >= 60) s.grade = 'B';
            else if(s.average >= 40) s.grade = 'C';
            else s.grade = 'F';

             
            file.open("students.txt", ios::app);
            file << s.rollNo << "|" << s.name << "|" 
                 << s.total << "|" << s.average << "|" << s.grade << "\n";
            file.close();

            cout << "Student record saved!\n";
        }

        else if(choice == 2) {
            // View all records
            file.open("students.txt", ios::in);
            string line;
            cout << "\n--- All Student Records ---\n";
             cout << "RollNo | Name | Total | Average | Grade\n";
            while(getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }

        else if(choice == 3) {
            // Search student by Roll No
            int r; bool found = false;
            cout << "Enter Roll No to search: ";
            cin >> r;

            file.open("students.txt", ios::in);
            string line;
            while(getline(file, line)) {
                stringstream ss(line);
                string part;
                int rollFromFile;

                // Read roll no first
                getline(ss, part, '|');
                rollFromFile = stoi(part);

                if(rollFromFile == r) {
                    // Found the record
                    string name, total, average, grade;
                    getline(ss, name, '|');
                    getline(ss, total, '|');
                    getline(ss, average, '|');
                    getline(ss, grade, '|');

                    cout << "\n--- Record Found ---\n";
                    cout << "Roll No : " << rollFromFile << endl;
                    cout << "Name    : " << name << endl;
                    cout << "Total   : " << total << endl;
                    cout << "Average : " << average << endl;
                    cout << "Grade   : " << grade << endl;

                    found = true;
                    break;
                }
            }
            file.close();
            if(!found) cout << "No record found!\n";
        }


        else if(choice == 4) {
            cout << "Exiting...\n";
        }

        else {
            cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    return 0;
}
