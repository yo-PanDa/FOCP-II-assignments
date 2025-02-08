#include <iostream>
#include <algorithm> 
using namespace std;

void reverseArray(int arr[], int size) {
    reverse(arr, arr + size);
}

void findSecondLargestAndSmallest(int arr[], int size)
{
    if (size < 2)
    {
        cout << "Not enough elements to find second largest and second smallest!" << endl;
        return;
    }
    sort(arr, arr + size);
    cout << "Second smallest: " << arr[1] << endl;
    cout << "Second largest: " << arr[size - 2] << endl;
}

int main(){
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int arr[size];

    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    reverseArray(arr, size);
    cout << "Reversed array: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout<<findSecondLargestAndSmallest(arr, size);

    return 0;
}
