#include <iostream>
#include <random>
#include <ctime>

using namespace std;

void enhanced_selection_sort(int arr[], int size) {
    if (size > 1) {
        int max_val = arr[size - 1];
        int index = size - 1;

        for (int a = 0; a < size - 1; a++) {
            if (arr[a] >= max_val) {
                max_val = arr[a];
                index = a;
            }
        }

        if (index != size - 1) {
            int temp = arr[size - 1];
            arr[size - 1] = max_val;
            arr[index] = temp;
        }

        enhanced_selection_sort(arr, size - 1);
    }
}

void generate_random_input(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

int main() {
    int size = 100000;
    static int arr[100000];
    generate_random_input(arr, size);

    clock_t start = clock();
    enhanced_selection_sort(arr, size);
    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC * 1000;

    cout << "Execution Time: " << elapsed_time << " ms." << endl;

    // Printing first 10 sorted elements for demonstration
   
    cout << endl;

    return 0;
}
