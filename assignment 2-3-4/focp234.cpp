#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) 
return false;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) 
return false;
    }
    return true;
}

int nextPrime(int n) {
    while (!isPrime(++n));
    return n;
}

int printFactors(int n) {
    cout << "Factors of " << n << ":";
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) 
cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (isPrime(n)) {
        cout << n << " is prime no. next prime: " << nextPrime(n) << endl;
    } else {
        cout << n << " is not prime no." << endl;
        printFactors(n);
    }

    return 0;
}
#include <iostream>
using namespace std;
int main() {
    int m,n;
    int arr[m][n];

     cin>>m;
     cin>>n;
cout<<"matrix is of size:"<<m<<"X"<< n ;
    return 0;
}
#include <iostream>
using namespace std;
int main() {
    int arr[20];
 for(int i=0;i<=9;i++){       
     cin>>arr[i];
   }
 for(int i=9;i>=0;i--){  

cout<<arr[i]<<endl;
}
    return 0;
}
#include <iostream>
using namespace std;

int main()
{
  int size=0;
    int a[10];

    for(int i=0; i<10;i++) {
    cin>>a[i];
    size++;
    }
      
    for(int i=0; i<10; i++)
    {
        for(int j=i+1; j<10; j++) { 
        if(a[i]>a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
   
 
      cout<<" 2nd largest "<<a[size-2]<<endl;
       cout<<" 2nd smallest "<<a[1]<<" ";
   return 0;
}
#include <iostream>
using namespace std;

int main() {
    string str;
    
    cout << "Enter sentence: "<<endl;
  
    getline(cin, str);
    
    cout << "You entered: " << str << endl;
    
    return 0;
}

int main() {
    string str;
    cout << "Enter string: ";
    getline(cin, str);

    string nwstr = "";
    for (char c : str) {
        if (c != ' ') {
   
            if (c >= 'A' && c <= 'Z') {
            c += 32;
            nwstr += c;
            }
        }
    }

    int n = nwstr.length();
    bool palindrome = true;
    for (int i = 0; i < n / 2; i++) {
        if (nwstr[i] != nwstr[n - i - 1]) {
            palindrome = false;
            break;
        }
    }

    if (palindrome) {
        cout << "The string is palindrome" << endl;
    } else {
        cout << "The string is not palindrome";
    }

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    string str;
    cout << "Enter string ";
    getline(cin, str);

    int freq[256] = {0}; 

  
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') 
        freq[str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            cout << char(i) << ": " << freq[i] << endl;
}
}

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    string str;
    cout << "Enter string ";
    getline(cin, str);

    for (int i = 0; i < str.length(); i++) {
        char c = tolower(str[i]); 
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            str[i] = '*'; 
        }
    }

    cout << "new updated string: " << str;

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int n = 4; 
    int matrix[4][4]; 
    int no = 1; 
    int sR = 0, eR = n-1, sC = 0, eC = n-1; 
    while (sR <= eR && sC <= eC) {

        for (int i = sC; i <= eC; i++) 
        matrix[sR][i] = no++;
        sR++; 
        
        for (int i = sR; i <= eR; i++) 
        matrix[i][eC] = no++;
        eC--; 
        if (sR <= eR) {
            
            for (int i = eC; i >= sC; i--) 
            matrix[eR][i] = no++;
            eR--; 
        }
        
        if (sC <= eC) {
           
            for (int i = eR; i >= sR; i--) 
            matrix[i][sC] = no++;
            sC++;
        }
    }

   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
        cout << matrix[i][j] << " ";
       cout<<endl;
    }

    return 0;
}
#include<iostream>
using namespace std;
int main(){
    int n,m;
    cout<<"Enter number of rows :";
    cin>>n;
    cout<<"Enter number of columns : ";
    cin>>m;
    int arr[n][m];
    int transpose[m][n];
    cout<<endl<<"Enter the elements of "<<n<<"X"<<m<<" matrix\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            transpose[j][i]=arr[i][j];
        }
    }
    for(int i=0;i<m;i++){
        int j=0;
        int k=(n-1);
        while(j<k){
            int temp=transpose[i][k];
            transpose[i][k]=transpose[i][j];
            transpose[i][j]=temp;
            j++;
            k--;
        }
    }
    cout<<endl<<"THE 90 DEGREE CLOCKWISE ROTATION OF THE GIVEN MATRIX IS : "<<endl<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<transpose[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}