#include<bits/stdc++.h>
using namespace std;

int partition(int a[], int low, int high) {
	int pivot = a[low];
	int i = low, j = high;
	while(i < j) {
		while(pivot >= a[i] && i <= high - 1) i++;
		while(pivot < a[j] && j >= low + 1) j--;
		if(i < j) swap(a[i], a[j]);
	}
	swap(a[low], a[j]);
	return j;
}

void quickSort(int a[], int low, int high) {
	if(low < high) {
		int partitionIndex = partition(a, low, high);
		quickSort(a, low, partitionIndex - 1);
		quickSort(a, partitionIndex + 1, high);
	}
}

int main() {
	int n; cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	quickSort(a, 0, n - 1);
	for(int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
	return 0;
}