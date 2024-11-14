#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

//Constants
int const COLUMNS = 6;
int const ARRAY_SIZE = 10;
double const STATE_TAX = .04;
double const FED_TAX = .05;
double const FICA = .05;
string const empInfoType[COLUMNS] = {"ID","Gross Pay","State Tax","Federal Tax","FICA","Net Pay" };

//arrays
double employeeInfo[ARRAY_SIZE][COLUMNS]; //2D array to hold up to 10 employee records

//function prototypes
void openFile();
void getSaveEmployeeRecords(double [][COLUMNS], int &);
void getEmployeeInfo(double [][COLUMNS], int &);
int getID();
double computePay(double [][COLUMNS], int);
double GetGrossPay();
void displayEmployeeTable(double [][COLUMNS], int);
void saveEmployeeInfo(double [][COLUMNS], int);
void SetFormat(int precision, int width);
void closeFile();

//global
fstream employeeSavedRecords;

int main() {
    
    
    openFile();
    int records = 0;
    getEmployeeInfo(employeeInfo, records);
    displayEmployeeTable(employeeInfo, records);
    saveEmployeeInfo(employeeInfo, records);
    closeFile();
}

void displayEmployeeTable(double employeeInfo[][COLUMNS], int records) {
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

// To do: allow for multiple employees.

//         save in file and read in file

void getEmployeeInfo(double employee[][COLUMNS], int &records) {
    getSaveEmployeeRecords();
    int rowIndex = 0;
    do {
        employee[rowIndex][0] = getID();
        if (employee[rowIndex][0] > 0) {
            double grossPay = GetGrossPay();
            employee[rowIndex][1] = grossPay;
            employee[rowIndex][2] = grossPay * STATE_TAX;
            employee[rowIndex][3] = grossPay * FED_TAX;
            employee[rowIndex][4] = grossPay * FICA;
            employee[rowIndex][5] = computePay(employeeInfo, rowIndex);
            records++;
            rowIndex++;
        }
        else {
            cout << "Done entering new records.\n\n";
            break;
        }
    } while (rowIndex < ARRAY_SIZE);
}

int getID() {
    int id;
    cout << "Please Enter the Employee ID: ";
    cin >> id;
    return id;
}

double GetGrossPay() {
    double gp;
    cout << "Please Enter the Employee's Gross Pay: ";
    cin >> gp;
    return gp;
}

double computePay(double info[][COLUMNS], int row)

{
    double grossPay = info[row][1];
    double deductions = 0.0;
    for (int i = 2; i < 5; i++)
    {
        deductions += info[row][i];
    }
    return grossPay - deductions;
}

void getSaveEmployeeRecords(double employee[][COLUMNS], int &records) {
    while (employeeSavedRecords >> )
    
    for (int i = 0; i < records; i++) {
        employeeSavedRecords << employeeInfo[i][0] << "\t";
        for (int j = 1; j < COLUMNS; j++) {
            employeeSavedRecords << employeeInfo[i][j] << "\t";
        }
        employeeSavedRecords << endl;
    }
}

void saveEmployeeInfo(double[][COLUMNS], int records) {
    for (int i = 0; i < records; i++) {
        employeeSavedRecords << employeeInfo[i][0] << "\t";
        for (int j = 1; j < COLUMNS; j++) {
            employeeSavedRecords << employeeInfo[i][j] << "\t";
        }
        employeeSavedRecords << endl;
    }
}

void openFile() {
    employeeSavedRecords.open("employeeSavedRecords.txt", ios::app);
        if (employeeSavedRecords) {
            cout << "file open.\n";
        }
        else {
            cout << "The file was not found or could not be opened. \n";
            cout << "Please check to see if the file is in the correct folder and rerun the program. Exiting ...\n";
            exit(0);
        }
}

void closeFile() {
    cout << "Closing file ...";
    employeeSavedRecords.close();
    cout << "File closed.";
}