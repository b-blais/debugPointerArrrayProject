/*
Title: Employee Records
File Name : debugPointerArrayProject
Programmer : Brion Blais
Date : 11 / 2024
Requirements :
Write a program that will ask the user to enter an employee ID and Gross Wages.  Calculate the taxes and deductions to include take home pay and display the results.
The program should store the information in a two dimensional array.
The program should read previous records from a file and save the new records added.

This branch changes the two dimensional array to a dynamically created two dimensional array.  This means that the size of the array is determined at runtime by the user entry
and the number of records saved in the text file.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Constants
int const COLUMNS = 6;
double const STATE_TAX = .04;
double const FED_TAX = .05;
double const FICA = .05;
string const empInfoType[COLUMNS] = {"ID","Gross Pay","State Tax","Federal Tax","FICA","Net Pay" };

//Pointers
double** ptrArray = nullptr;

//function prototypes
void createDynamicArray(int, int);
void getSavedEmployeeRecords(int, int &);
void getEmployeeInfo(int, int &);
int getID();
double computePay(int);
double GetGrossPay();
void displayEmployeeTable(int);
void saveEmployeeInfo(int);
void SetFormat(int precision, int width);
int countLines();
void deleteDynamicMemoryAllocations(int &);

//global
fstream employeeSavedRecords;

int main() {
        
    int records = 0;
    int newRecords;
    cout << "How many records are you adding today?\t";
    cin >> newRecords;
    if (newRecords > 0) {
        getEmployeeInfo(newRecords, records);
    }
    else {
        getSavedEmployeeRecords(newRecords, records);
        cout << records << " records recovered from the saved file." << endl;
    }
    displayEmployeeTable(records);
    saveEmployeeInfo(records);
    deleteDynamicMemoryAllocations(records);
}

void createDynamicArray(int newEmployees, int recordsToRecover) {
    // array of pointers to what will be records for "employeeNumber" employees
    ptrArray = new double* [(newEmployees + recordsToRecover)];
    // connect the array of pointers to the fixed array of columns.
    for (int i = 0; i < (newEmployees + recordsToRecover); i++) {
        ptrArray[i] = new double[COLUMNS];
    }
}

void deleteDynamicMemoryAllocations(int &records) {
    for (int i = 0; i < records; i++) {
        delete[] ptrArray[i];
     }
    delete[] ptrArray;
}

void displayEmployeeTable(int records) {
    SetFormat(2, 3);
    for (int i = 0; i < records; i++) {
        cout << left << "ID " << left << static_cast<int>(ptrArray[i][0]) << "\n";
        for (int j = 1; j < COLUMNS; j++) {
            SetFormat(2, 10);
            cout << left << empInfoType[j] << ":\t$" << left << ptrArray[i][j] << "\n";
        }
        cout << endl;
    }
}

void SetFormat(int precision, int width) {
    cout.precision(precision);
    cout << setw(width);
    cout << fixed;
}

void getEmployeeInfo(int newRecords, int &records) {
    getSavedEmployeeRecords(newRecords, records);
    cout << records << " records recovered from the saved file." << endl;
    int rowIndex = records;
    do {
        ptrArray[rowIndex][0] = getID();
        double grossPay = GetGrossPay();
        ptrArray[rowIndex][1] = grossPay;
        ptrArray[rowIndex][2] = grossPay * STATE_TAX;
        ptrArray[rowIndex][3] = grossPay * FED_TAX;
        ptrArray[rowIndex][4] = grossPay * FICA;
        ptrArray[rowIndex][5] = computePay(rowIndex);
        rowIndex++;
    } while (rowIndex < (records+newRecords));
        cout << "Done entering new records ... " << newRecords << " records added.\n\n";
        records += newRecords;
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

double computePay(int row)

{
    double grossPay = ptrArray[row][1];
    double deductions = 0.0;
    for (int i = 2; i < 5; i++)
    {
        deductions += ptrArray[row][i];
    }
    return grossPay - deductions;
}

void getSavedEmployeeRecords(int newRecords, int &records) {
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
    int recordsToRecover = countLines();
    createDynamicArray(newRecords, recordsToRecover);
    for (int i = 0; i < recordsToRecover; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            employeeSavedRecords >> ptrArray[i][j];
        }
        records++;
    }
    employeeSavedRecords.close();
}

void saveEmployeeInfo(int records) {
    employeeSavedRecords.open("employeeSavedRecords.txt");
    for (int i = 0; i < records; i++) {
        employeeSavedRecords << ptrArray[i][0] << "\t";
        for (int j = 1; j < COLUMNS; j++) {
            employeeSavedRecords << ptrArray[i][j] << "\t";
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