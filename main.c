#include <stdio.h>
#include <stdlib.h>

char buffer;

struct Employee {
  char name[100];  // 1
  char id[10];     // 2
  float salary;    // 3
  float bonus;     // 4
  int workingdays; // 5
  int paidleaves;  // 6
  int sickleaves;  // 7
};

void initEmployee(struct Employee *E) {//function to read employee's details
  char ch = ' ';
  printf("Enter Name : ");//employee name
  int pos = 0;
  while (ch != '\n') {
    scanf("%c", &ch);
    E->name[pos] = ch;
    pos++;
  }
ID:
  printf("Enter ID : ");//employee id
  ch = ' ';
  pos = 0;
  while (ch != '\n' && pos < 10) {
    scanf("%c", &ch);
    E->id[pos] = ch;
    pos++;
  }
  if (pos >= 10 && E->id[0] == 'S' && E->id[1] == 'T' && E->id[2] == 'R') {//invalid id check
    printf("Please Enter a ValidID!\n");
    goto ID;
  }
  if (E->id[3] == '0' && E->id[4] == '0') {//25 paid leaves if id is STR00XXXXX
    E->paidleaves = 4;
    E->salary = 100000;
  } else if (E->id[3] == '0' && E->id[4] == '1') {//20 paid leaves if id is STR01XXXXX
    E->paidleaves = 3;
    E->salary = 10000;
  } else if (E->id[3] == '0' && E->id[4] == '2') {//12 paid leaves if id is STR02XXXXX
    E->paidleaves = 2;
    E->salary = 1000;
  } else {
    goto ID;//asks to enter new id if none of the cases match
  }
  E->sickleaves = 3;//sick leaves same for all
  E->workingdays = 0;
}

void printvar(char *str) {//function to print string one character at a time and a new line for each word
  int pos = 0;
  char ch = str[0];
  while (ch != '\n') {//loop for printing string
    pos++;
    printf("%c", ch);
    ch = str[pos];
  }
  printf("\n");//new line
}

void salaryDay(struct Employee *E) {//function to calculate salary based on number of leaves and bonuses
  int totalWorkingdays;
  printf("Enter No.of Total Working Days : ");
  scanf("%d", &totalWorkingdays);
  printf("Enter No.of Working Days : ");
  scanf("%d", &E->workingdays);
  if(totalWorkingdays<=0){
    printf("Total working days must be greater than zero\n");
    return;
  }
  float finalSalary = ((float)E->workingdays /                 //formula for final salary based on working days
                       (totalWorkingdays - E->paidleaves - E->sickleaves)) *
                      E->salary;
  E->bonus = (finalSalary <= E->salary)//if final salary less than base salary, bonus is (finalSalary - E->salary) / E->salary * 100
                 ? ((finalSalary - E->salary) / E->salary) * 100//if final salary is more than base salary, bonus is 20% if (finalSalary - E->salary) / E->salary * 100 > 30
                 : (((finalSalary - E->salary) / E->salary * 100 > 30)
                        ? 20
                        : ((finalSalary - E->salary) / E->salary * 100) + 10);//else the bonus is finalSalary - E->salary) / E->salary * 100) + 10 percent
  printf("Bonus : %.2f\n", (E->bonus > 0) ? E->bonus : 0.0f);
  finalSalary = E->salary * (1 + E->bonus / 100);//final salary 
  printf("Final salary : %.2f\n", finalSalary);
  scanf("%c",&buffer);
}

int main() {//TUI
  system("clear");
  // Deduction Logic
  struct Employee E[100];
  int Running = 1;
  int totalemp = 0;
  char option;
  printf("==========================================================\n");
  printf("                Employee Payroll Management               \n");
  printf("==========================================================\n");
  while (Running) {//runs forever until user changes value of running to 0
    printf("==========================================================\n");
    printf("                           Menu                           \n");
    printf("==========================================================\n");
    printf("  1. n -> New Employee\n  2. l -> List "
           "Employee\n  3. s -> Enter Salaries\n  4. c -> Clear whole screen"    //options
           "\n  5. q -> quit application\nEnter an Option : ");
    scanf("%c%c", &option, &buffer);
    if (option == 'q') {//running=0, breaks the while loop
      Running = 0;
    } else if (option == 'n') {//new employee
      printf("==========================================================\n");
      printf("                      New Employee                        \n");
      printf("==========================================================\n");
    ReEnter:
      initEmployee(&E[totalemp]);//employee details function call
      for (int i = 0; i < totalemp; i++) {//checks for duplicate id stored
        if (E[i].id[6] == E[totalemp].id[6] &&
            E[i].id[7] == E[totalemp].id[7] &&
            E[i].id[8] == E[totalemp].id[8]) {
          printf("Employee Already Exists! Please Recheck and Reenter the "
                 "name!\n");
          goto ReEnter;//starts ReEnter process again, calling employee details function again
        }
      }
      totalemp++;//increases number of total employees
    } else if (option == 'l') {//list of employees
      printf("==========================================================\n");
      printf("                      Employee List                       \n");
      printf("==========================================================\n");
      for (int i = 0; i < totalemp; i++) {//for loop to retrieve all the names of the employees stored
        printf("Name : ");
        printvar(E[i].name);
        printf("Id : ");
        printvar(E[i].id);
        printf("Salary : %.2f\n", E[i].salary);
      }
    } else if (option == 's') {//to enter salaries
      printf("==========================================================\n");
      printf("                    Employee Salaries                     \n");
      printf("==========================================================\n");
      for (int i = 0; i < totalemp; i++) {
        printf("For ID : %s", E[i].id);//displays the id for which their salary is being modified
        salaryDay(&E[i]);
      }
    } else if (option == 'c') {//clears the screen
      system("clear");
      printf("==========================================================\n");
      printf("                Employee Payroll Management               \n");
      printf("==========================================================\n");
    } else {
      printf("Enter a Valid Option!\n");
    }
  }
}
