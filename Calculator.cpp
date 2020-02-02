#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

char infix[55], pseudoinfix[55], postfix[55];
double integers[26];
double result = 0;

struct Result // To calculate result
{
  double x;
  Result *next;
} *Topr = NULL;

struct Stack // to convert infix to pseudoinfix
{
  char Operator;
  Stack *next;
} *Top = NULL;

void pushr(double ch)// to push in result
{
  Result *newresult = new Result;
  if (Topr == NULL)
  {
    newresult->next = NULL;
    Topr = newresult;
    newresult->x = ch;
  }
  else
  {
    newresult->next = Topr;
    Topr = newresult;
    newresult->x = ch;
  }
}

double popr()// to pop from result
{
  double ret;
  Result *temp = new Result;
  if (Topr != NULL)
  {
    temp = Topr;
    ret = temp->x;
    Topr = temp->next;
  }
  delete temp;
  return ret;
}

void push(char ch)// to push in stack
{
  Stack *newStack = new Stack;
  if (Top == NULL)
  {
    newStack->next = NULL;
    Top = newStack;
    newStack->Operator = ch;
  }
  else
  {
    newStack->next = Top;
    Top = newStack;
    newStack->Operator = ch;
  }
}

char pop()// to pop from stack
{
  char ret;
  Stack *temp = new Stack;
  if (Top != NULL)
  {
    temp = Top;
    ret = temp->Operator;
    Top = temp->next;
    return ret;
  }
  else
  {
    return '#';
  }
  delete temp;
}

char Topelement()// top element of stack
{
  char ch;
  if (Top != NULL)
    ch = Top->Operator;
  else
    ch = '#';
  return ch;
}

int braces(char *pseudoinfix)// to count no of braces 
{
  int leftbr, rightbr;
  leftbr = rightbr = 0;
  for (int i = 0; pseudoinfix[i] != '\0'; i++)
  {
    if (pseudoinfix[i] == '(')
      leftbr++;
    else if (pseudoinfix[i] == ')')
      rightbr++;
  }
  if (leftbr == rightbr)
    return 0;
  else if (leftbr < rightbr)
    return 1;
  else
    return -1;
}

int precendence(char ch)// returns precendence of operator to apply bodmas
{
  switch (ch)
  {
    case '^':
        return 5;
  case '/':
    return 4;
  case '*':
    return 4;
  case '+':
    return 3;
  case '-':
    return 3;
  default:
    return 0;
  }
}

void To_postfix() // to convert pseudoinfix to postfix
{
  char topelement, infixelement, poped_element;
  int precendence_of_infix, precendence_of_topelement, j = 0;
  strcpy(postfix, " ");
  for (int i = 0; pseudoinfix[i] != '\0'; i++)
  {
    if (pseudoinfix[i] != '(' && pseudoinfix[i] != ')' && pseudoinfix[i] != '*' && pseudoinfix[i] != '/' && pseudoinfix[i] != '+' && pseudoinfix[i] != '-' && pseudoinfix[i] != '^')
      postfix[j++] = pseudoinfix[i];
    else if (pseudoinfix[i] == '(')
    {
      infixelement = pseudoinfix[i];
      push(infixelement);
    }
    else if (pseudoinfix[i] == ')')
    {
      while ((poped_element = pop()) != '(')
      {
        postfix[j++] = poped_element;
      }
    }
    else
    {
      infixelement = pseudoinfix[i];
      precendence_of_infix = precendence(infixelement);
      topelement = Topelement();
      precendence_of_topelement = precendence(topelement);
      if (precendence_of_infix > precendence_of_topelement)
      {
        push(infixelement);
      }
      else
      {
        while (precendence_of_topelement >= precendence_of_infix)
        {
          if (topelement == '#')
            break;
          poped_element = pop();
          topelement = Topelement();
          postfix[j++] = poped_element;
          precendence_of_topelement = precendence(topelement);
        }
        push(infixelement);
      }
    }
  }
  while ((poped_element = pop()) != '#')
    postfix[j++] = poped_element;
  postfix[j] = '\0';
}

double numeric_value(char ch)// to get numerical value
{
  switch (ch)
  {
  case '0':
    return 0.0;
  case '1':
    return 1.0;
  case '2':
    return 2.0;
  case '3':
    return 3.0;
  case '4':
    return 4.0;
  case '5':
    return 5.0;
  case '6':
    return 6.0;
  case '7':
    return 7.0;
  case '8':
    return 8.0;
  case '9':
    return 9.0;
  }
  return -1;
}

int check_operator(char a)
{
  if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '^')
  {
    if (a == '(')
    {
      return 1;
    }
    else
    {
      return 2;
    }
  }
  return 0;
}

void Topseudoinfix()// to convert a expression in pseudoinfix eg: (23+ 4) as (a+b)
{
  bool decimal_encountered = false;
  double temp = 0;
  int j = 0, k = 0, decimal_count = 0;
  char ch = 'a';
  for (int i = 0; infix[i] != '\0'; i++)
  {
    if (check_operator(infix[i]) == 0)
    {
      if (infix[i] == '.')
      {
        decimal_encountered = true;
      }
      else
      {
        temp = (temp * 10) + numeric_value(infix[i]);
      }
      if (decimal_encountered)// to measure decimal point numbers
      {
        decimal_count = decimal_count + 1;
      }
    }
    else if (check_operator(infix[i]) == 2)
    {
      pseudoinfix[k++] = ch++;
      pseudoinfix[k++] = infix[i];
      while (infix[i] == ')')
      {
        i++;
        pseudoinfix[k++] = infix[i];
      }
      if (decimal_count > 0)
      {
        temp = temp / pow(10, decimal_count - 1);
      }
      decimal_encountered = false;
      decimal_count = 0;
      integers[j++] = temp;
      temp = 0;
    }
    else if (check_operator(infix[i]) == 1)
    {
      decimal_encountered = false;
      decimal_count = 0;
      pseudoinfix[k++] = infix[i];
    }
  }
  if (decimal_count > 0)
  {
    temp = temp / pow(10, decimal_count - 1);
  }
  integers[j++] = temp;
  pseudoinfix[k++] = ch;
}

double corresponding_value(char ch)
{
  switch (ch)
  {
  case 'a':
    return integers[0];
  case 'b':
    return integers[1];
  case 'c':
    return integers[2];
  case 'd':
    return integers[3];
  case 'e':
    return integers[4];
  case 'f':
    return integers[5];
  case 'g':
    return integers[6];
  case 'h':
    return integers[7];
  case 'i':
    return integers[8];
  case 'j':
    return integers[9];
  case 'k':
    return integers[10];
  case 'l':
    return integers[11];
  case 'm':
    return integers[12];
  case 'n':
    return integers[13];
  case 'o':
    return integers[14];
  case 'p':
    return integers[15];
  case 'q':
    return integers[16];
  case 'r':
    return integers[17];
  case 's':
    return integers[18];
  case 't':
    return integers[19];
  case 'u':
    return integers[20];
  case 'v':
    return integers[21];
  case 'w':
    return integers[22];
  case 'x':
    return integers[23];
  case 'y':
    return integers[24];
  case 'z':
    return integers[25];
  case 'R':
    return result;
  }
  return 0;
}

void calculate() // to calculate
{
  double num1 = 0, num2 = 0;
  for (int i = 0; postfix[i] != '\0'; i++)
  {
    if (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/'
            && postfix[i] != '^')
    {
      pushr(corresponding_value(postfix[i]));
    }
    else if (postfix[i] == '+')
    {
      num1 = popr();
      num2 = popr();

      result = num1 + num2;
      pushr(result);
    }
    else if (postfix[i] == '-')
    {
      num1 = popr();
      num2 = popr();

      result = num2 - num1;
      pushr(result);
    }
    else if (postfix[i] == '*')
    {
      num1 = popr();
      num2 = popr();

      result = num1 * num2;
      pushr(result);
    }
    else if (postfix[i] == '/')
    {
      num1 = popr();
      num2 = popr();

      result = (num2 / num1);
      if(num1 == 0){
        cout << "Error: Denominator Can't be Zero\n";
        system("pause");
        exit(1);
      }
      pushr(result);
    }
        else if (postfix[i] == '^')
    {
      num1 = popr();
      num2 = popr();

      result = pow(num2,num1);
      pushr(result);
    }
  }
  cout << endl
     << "Result: " << result << endl;
}

int main()
{
  char choice = 'y';
  int chk;
  system("cls");
  while (tolower(choice) != 'n')
  {
    if (tolower(choice) == 'y')
    {
      system("cls");
      cout << "\t\t\tCalculator by Himanshu Sharma \n";
      cout << "Enter expression: "
         << "\n";
      cin >> infix;
      chk = braces(infix);
      if (chk != 0)
      {
        cout << "Unbalanced No of Braces\n";
        if (chk == 1)
        {
          cout << "Extra Right Braces\n";
        }
        else
        {
          cout << "Extra Left Braces\n";
        }
      }
      Topseudoinfix();
      To_postfix();
      calculate();
      cout << "enter Y to continue, N to exit\n";
      cin >> choice;
    }
  }
  return 0;
}
