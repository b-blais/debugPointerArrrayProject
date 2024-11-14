#include <iostream>

#include <iomanip>
#include <vector>

using namespace std;

//Constants
int const columns = 6;
int const ARRAY_SIZE = 7;
double const STATE_TAX = .04;
double const FED_TAX = .05;
double const FICA = .05;
string const empInfoType[7] = { "", "ID","Gross Pay","State Tax","Federal Tax","FICA","Net Pay" };

//arrays
double employeeInfo[10][6]; //2D array to hold up to 10 employee records

//function prototypes
void getEmployeeInfo(double [][columns], int);
int getID();
void computePay(double [], int);

void DisplayEmployeeTable(double employees[], int ARRAY_SIZE);







double GetGrossPay();


void SetFormat(int precision, int width);

void PopulateEmployeeTable(double employees[], double empInfo[], int  ARRAY_SIZE);

int main()

{
    //vector <double*> Employees;
    //double empInfo[7];
    //double* ptr;

    //ptr = GetEmployeeInfo();
    while (ptr[1] != 0)
    {
        Employees.push_back(ptr);
        DisplayEmployeeTable(ptr, 7);
        ptr = getEmployeeInfo(employeeInfo, 6);
    }

    // for (auto Employee : Employees)
   //  {
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << endl;
            cout << empInfoType[j] << "\t" << Employees[i][j];
        }
    }
    //  }

}
void DisplayEmployeeTable(double employees[], int ARRAY_SIZE) {

    double  empInfo = employees[0];
    cout << left << empInfoType[1] << ": " << employees[1] << endl;
    SetFormat(2, 15);
    double grossPay = employees[1];
    for (int i = 2; i < 7; i++)
    {
        cout << empInfoType[i] << ":\t$" << right << employees[i] << "\n";
    }

}

void SetFormat(int precision, int width) {
    cout.precision(precision);
    cout << setw(width);
    cout << fixed;
}

// To do: allow for multiple employees.

//         save in file and read in file

void getEmployeeInfo(double employee[][columns], int rows) {
    int count = 0;
    while (count < rows) {
        employee[count][0] = getID();
        if (employee[count][0] > 0) {
            employee[count][1] = GetGrossPay();
            employee[count][2] = STATE_TAX;
            employee[count][3] = FED_TAX;
            employee[count][4] = FICA;
            computePay(employeeInfo, count);
            //double* ptr2 = EmployeeInfo;

        }
    }

    
    
}

int getID() {
    int id;
    cout << "Please Enter the Employee ID:";
    cin >> id;
    return id;
}


void computePay(double info[][columns], int row)

{
    double grossPay = info[row][1];
    double netPay = grossPay;
    for (int i = 2; i < size; i++)
    {
        info[row][i] = info[row][i] * grossPay;
        netPay = netPay - info[row][i];
    }
    info[row][size - 1] = netPay;
}

double GetGrossPay() {
    double gp;
    cout << "Please Enter the Employee's Gross Pay:";
    cin >> gp;
    return gp;
}



void PopulateEmployeeTable(double employees[], double empInfo[], int  ARRAY_SIZE) {
    static int EmployeeCount = 0;
    employees[EmployeeCount] = *empInfo;
    EmployeeCount += 1;
}



/*double GetStateTax() {

    double st;

    cout << "Please Enter the State tax percentage:";

    cin >> st;

    return st;



}

double GetFedTax() {

    double ft;

    cout << "Please Enter the Federal tax percentage:";

    cin >> ft;

    return ft;



}





double GetFICA() {

    double FICA;

    cout << "Please Enter the Employee's FICA withholding:";

    cin >> FICA;

    return FICA;



}

*/