#include<iostream>
using namespace std;
int main(){
int m1[3][3]={1,2,3,4,5,6,7,8,9};
int i,j;
cout<<"orignal mamtrix\n";
for(i=0;i<3;i++)
{
    for(j=0;j<3;j++)
    {
        cout<<m1[i][j]<<" ";

    }
} 
cout<<"matrix after 90 degree rotation\n";
for(i=0;i<3;i++)
{
    for(j=2;j>= 0;j--)
    {
        cout<<m1[j][i]<<" ";
    }
    cout<<endl;
}
return 0;
}