#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the size of the array (at least 2 elements): ";
    cin >> n;

    if (n < 2) {
        cout << "The array must have at least 2 elements to find second largest and second smallest.\n";
        return 0;
    }

    int arr[n]; 
    cout << "Enter the " << n << " elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; 
    }

    int largest = INT_MIN, secondLargest = INT_MIN;
    int smallest = INT_MAX, secondSmallest = INT_MAX;

    for (int i = 0; i < n; i++) {

        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }

        if (arr[i] < smallest) {
            secondSmallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] < secondSmallest && arr[i] != smallest) {
            secondSmallest = arr[i];
        }
    }


    if (secondLargest == INT_MIN) {
        cout << "No second largest element.\n"; 
    } else {
        cout << "Second Largest: " << secondLargest << endl;
    }


    if (secondSmallest == INT_MAX) {
        cout << "No second smallest element.\n"; 
    } else {
        cout << "Second Smallest: " << secondSmallest << endl;
    }

    cout << "Array in reverse order: ";
    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
