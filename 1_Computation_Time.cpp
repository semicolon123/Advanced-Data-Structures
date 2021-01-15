#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

/*************** INSERTION SORT **********************/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
/********************* SELECTION SORT ***********************/
void selectionSort(int arr[], int n){
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++) 
        if (arr[j] < arr[min_idx])
        min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
/******************** QUICK SORT **************************/
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[],int low, int high){
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
/******************** MERGE SORT ****************************/
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;      // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {        // Copy the remaining elements of L[], if there are any
            arr[k] = L[i];
            i++;
            k++;
    }
   
    while (j < n2) {         // Copy the remaining elements of R[], if there are any
            arr[k] = R[j];
            j++;
            k++;
    }
}

void mergeSort(int arr[],int l,int r){      // l is for left index and r is right index of the sub-array of arr to be sorted
        if(l>=r){
            return;//returns recursively
        }
        int m = (l+r-1)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
 }

int main()
{
    struct timeval begin, end;
    int arr[10000]; //Given in the problem

    
    for(int i = 0;i<10000;i++){
        arr[i]=rand();
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    /*The function gettimeofday() returns the time elapsed since 00:00:00 UTC on January 1st, 1970
    (often called Epoch time). The tricky thing is that the function returns both the number of seconds
    and microseconds in separate long int variables, so that to obtain the total time including
    microseconds you need to sum both together accordingly.*/

    /***** Calculating Computation time for INSERTION sort *****/
    gettimeofday(&begin, 0);
    insertionSort(arr, n);
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    cout<<"Computation time measured for:\n\n";
    cout<<"1. Insertion sort:"<<elapsed<<" seconds"<<"\n\n";

    /***** Calculating Computation time for SELECTION sort *****/
    gettimeofday(&begin, 0);
    selectionSort(arr,n);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    cout<<"2. Selection sort:"<<elapsed<<" seconds"<<"\n\n";

    /***** Calculating Computation time for MERGE sort *****/
    gettimeofday(&begin, 0);
    mergeSort(arr,0, (10000-1));
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    cout<<"3. Merge sort:"<<elapsed<<" seconds"<<"\n\n";

    /***** Calculating Computation time for QUICK sort *****/
    gettimeofday(&begin, 0);
    quickSort(arr,0, (10000-1));
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    cout<<"4. Quick sort:"<<elapsed<<" seconds";

    return 0;
}