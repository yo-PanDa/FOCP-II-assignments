#include <iostream>
using namespace std;

int main()
{
    int num;
    int flag = 0;
    cout << "Enter the number";
    cin >> num;
    for (int i = 2; i <= num; i++)
    {
        if (num % i == 0)
        {
            flag++;
        }
    }
    if (flag > 2)
    {
        cout << "The number is not prime ";
        goto allfactors;
    }
    else
    {
        cout << "The number is prime ";
    }
allfactors:
cout<<endl<<"the factors are";
    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            cout <<"\n"<< i;
            }
            }
    return 0;        
}