/*
Title: Employee Records
File Name : debugPointerArrayProject
Programmer : Brion Blais
Date : 11 / 2024
Requirements :
Write a program that will ask the user to enter an employee ID and Gross Wages.  Calculate the taxes and deductions to include take home pay and display the results.
The program should store the information in a two dimenional array.
The program should read previous records from a file and save the new records added.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Constants
int const COLUMNS = 6;
int const ARRAY_SIZE = 100;
double const STATE_TAX = .04;
double const FED_TAX = .05;
double const FICA = .05;
string const empInfoType[COLUMNS] = {"ID","Gross Pay","State Tax","Federal Tax","FICA","Net Pay" };

//arrays
double employeeInfo[ARRAY_SIZE][COLUMNS]; //2D array to hold up to 100 employee records

//function prototypes
void getSavedEmployeeRecords(double [][COLUMNS], int &);
void getEmployeeInfo(double [][COLUMNS], int &);
int getID();
double computePay(double [][COLUMNS], int);
double GetGrossPay();
void displayEmployeeTable(double [][COLUMNS], int);
void saveEmployeeInfo(double [][COLUMNS], int);
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

void getEmployeeInfo(double employee[][COLUMNS], int &records) {
    getSavedEmployeeRecords(employeeInfo, records);
    cout << records << " records recovered from the saved file." << endl;
    int rowIndex = records;
    do {
        employee[rowIndex][0] = getID();
        if (employee[rowIndex][0] > 0) {
            double grossPay = GetGrossPay();
            employee[rowIndex][1] = grossPay;
            employee[rowIndex][2] = grossPay * STATE_TAX;
            employee[rowIndex][3] = grossPay * FED_TAX;
            employee[rowIndex][4] = grossPay * FICA;
            employee[rowIndex][5] = computePay(employeeInfo, rowIndex);
            rowIndex++;
        }
        else {
            cout << "Done entering new records.\n\n";
            records += (rowIndex - records);
            break;
        }
    } while (rowIndex < ARRAY_SIZE);
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

void getSavedEmployeeRecords(double employee[][COLUMNS], int &records) {
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
    for (int i = 0; i < savedRecordCount; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            employeeSavedRecords >> employee[i][j];
        }
        records++;
    }
    employeeSavedRecords.close();
}

void saveEmployeeInfo(double[][COLUMNS], int records) {
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