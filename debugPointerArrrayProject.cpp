#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Constants
int const COLUMNS = 6;
double const STATE_TAX = .04;
double const FED_TAX = .05;
double const FICA = .05;
string const empInfoType[COLUMNS] = {"ID","Gross Pay","State Tax","Federal Tax","FICA","Net Pay" };

//arrays
vector<vector<double>> employeeInfo; //2D vector

//function prototypes
void getSavedEmployeeRecords(vector<vector<double>> &, int &);
void getEmployeeInfo(vector<vector<double>> &, int &);
int getID();
double GetGrossPay();
void displayEmployeeTable(vector<vector<double>>&, int);
void saveEmployeeInfo(vector<vector<double>>&, int);
void SetFormat(int precision, int width);
int countLines();

//global
fstream employeeSavedRecords;

int main() {
    int records = 0;
    getEmployeeInfo(employeeInfo, records);
    displayEmployeeTable(employeeInfo, records);
    saveEmployeeInfo(employeeInfo, records);
}

void displayEmployeeTable(vector<vector<double>>& employeeInfo, int records) {
    SetFormat(2, 3);
    for (int i = 0; i < records; i++) {
        cout << left << "ID " << left << static_cast<int>(employeeInfo[i][0]) << "\n";
        for (int j = 1; j < COLUMNS; j++) {
            SetFormat(2, 10);
            cout << left << empInfoType[j] << ":\t$" << left << employeeInfo[i][j] << "\n";
        }
        cout << endl;
    }
}

void SetFormat(int precision, int width) {
    cout.precision(precision);
    cout << setw(width);
    cout << fixed;
}

void getEmployeeInfo(vector<vector<double>> &employeeInfo, int &records) {
    getSavedEmployeeRecords(employeeInfo, records);
    cout << (employeeInfo.size()) << " records recovered from the saved file." << endl;
    vector<double> row;
    do {
        row.push_back(getID());
        if (row[0] == 0) {
            break;
        }
        double grossPay = GetGrossPay();
        row.push_back(grossPay);
        row.push_back(grossPay * STATE_TAX);
        row.push_back(grossPay * FED_TAX);
        row.push_back(grossPay * FICA);
        row.push_back(row[1] - (row[2] + row[3] + row[4]));
        employeeInfo.push_back(row);
        row.clear();
    } while (row.empty());
    records = static_cast<int>(employeeInfo.size());
    cout << "Done entering new records.\n\n";
}

int getID() {
    int id;
    cout << "Please Enter the Employee ID; enter 0 if there are no more records: ";
    cin >> id;
    return id;
}

double GetGrossPay() {
    double gp;
    cout << "Please Enter the Employee's Gross Pay: ";
    cin >> gp;
    return gp;
}

void getSavedEmployeeRecords(vector<vector<double>>& employeeInfo, int &records) {
    employeeSavedRecords.open("employeeSavedRecords.txt");
    if (employeeSavedRecords) {
        cout << "employeeSavedRecords is open.\n";
    }
    else {
        cout << "The file was not found or could not be opened. \n";
        cout << "Please check to see if the file is in the correct folder and rerun the program. Exiting ...\n";
        exit(0);
    }
    if (employeeSavedRecords) {
        cout << "Reading records ... ";
    }
    int savedRecordCount = countLines();
    vector<double> row;
    double tempInput;
    for (int i = 0; i < savedRecordCount; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            employeeSavedRecords >> tempInput;
            row.push_back(tempInput);
        }
        employeeInfo.push_back(row);
        row.clear();
        records++;
    }
    employeeSavedRecords.close();
}

void saveEmployeeInfo(vector<vector<double>>& employeeInfo, int records) {
    employeeSavedRecords.open("employeeSavedRecords.txt");
    for (int i = 0; i < records; i++) {
        employeeSavedRecords << employeeInfo[i][0] << "\t";
        for (int j = 1; j < COLUMNS; j++) {
            employeeSavedRecords << employeeInfo[i][j] << "\t";
        }
        employeeSavedRecords << endl;
    }
    employeeSavedRecords.close();
    cout << "Employee information saved.\n";
}

int countLines() {
    int lineCount = 0;
    string fileContents;
    while (getline(employeeSavedRecords, fileContents)) {
        if (fileContents == "") {
            cout << "This is an empty file or it is unreadable.\n";
            return 0;
        }
        lineCount += 1;
    }
    cout << "There are " << lineCount << " lines in this file.\n";
    employeeSavedRecords.clear();
    employeeSavedRecords.seekg(0, ios::beg);
    return lineCount;
 }