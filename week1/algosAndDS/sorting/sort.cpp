#include<iostream>
using namespace std;

/*
BUBBLE SORT
*/
void bubbleSort(int *arr, int n){
    bool isSwapped;
    for(int i = 0; i < n; ++i){
        isSwapped = false;
        for(int j = 0; j < n - 1; ++j){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }

        if(isSwapped == false){
            break;
        }
    }
}

/*
SELECTION SORT
*/
void selectionSort(int arr[], int n){
    int minIndex;
    for(int i = 0; i < n; ++i){
        minIndex = i;
        for(int j = i + 1; j < n; ++j){
            if(arr[minIndex] > arr[j]){
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

/*
INSERTION SORT
*/
void insertionSort(int arr[], int n){
    int min, j;
    for(int i = 0; i < n; ++i){
        min = arr[i];
        j = i - 1;
        while(j >= 0 & arr[j] > min){
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = min;
    }
}

/*
MERGE SORT
*/

// Gộp hai mảng con arr[left...mid] và arr[mid+1..right]
void merge(int arr[], int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Tạo các mảng tạm */
    int L[n1], R[n2];

    /* Copy dữ liệu sang các mảng tạm */
    for(i = 0; i < n1; ++i){
        L[i] = arr[left + i];
    }

    for(j = 0; j < n2; ++j){
        R[j] = arr[mid + 1 + j];
    }

    /* Gộp hai mảng tạm vừa rồi vào mảng arr*/
    i = 0; // Khởi tạo chỉ số bắt đầu của mảng con đầu tiên
    j = 0; // Khởi tạo chỉ số bắt đầu của mảng con thứ hai
    k = left; // IKhởi tạo chỉ số bắt đầu của mảng lưu kết quả

    while(i < n1 & j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            ++i;
        }

        else{
            arr[k] = R[j];
            ++j;
        }

        ++k;
    }

    /* Copy các phần tử còn lại của mảng L vào arr nếu có */
    while(i < n1){
        arr[k] = L[i];
        ++i;
        ++k;
    }

    /* Copy các phần tử còn lại của mảng R vào arr nếu có */
    while(j < n2){
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(int arr[], int left, int right){
    if(left >= right){
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}



/*
QUICK SORT
*/
int partition(int arr[],int left, int right){
    int pivot = arr[right];
    int i = left - 1;
    for(int j = left; j < right; ++j){
        if(arr[j] < pivot){
            i += 1;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]);

    return i + 1;
}


void quickSort(int arr[], int left, int right){
    if(left > right){
        return;
    }
    int index_pivot = partition(arr, left, right);
    quickSort(arr, left, index_pivot - 1);
    quickSort(arr, index_pivot + 1, right);
}


/*
HEAP SORT
*/

void heapify(int arr[], int n, int i)
{
	int largest = i; // Khởi tạo largest như là root
	int l = 2 * i + 1; // left = 2*i + 1 (con trái)
	int r = 2 * i + 2; // right = 2*i + 2 (con phải)

	// Nếu nút con trái lớn hơn root
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// Nếu nút con phải lớn hơn root
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// Nếu root không phải là lớn nhất
	if (largest != i)
	{
        // Đổi chỗ cho phần tử lớn nhất làm cha
		swap(arr[i], arr[largest]);

		// Đệ quy lại hàm heapify để vun các node phía dưới node vừa swap
		heapify(arr, n, largest);
	}
}

// Hàm heap sort
void heapSort(int arr[], int n)
{
	// Tạo một heap (Sắp xếp lại mảng từ dưới lên) từ nút cha cuối cùng (last parent) có index = (n / 2 - 1)
	for (int i = n / 2 - 1; i >= 0; --i){
		heapify(arr, n, i);
    }
	// Trích xuất từng phần tử một từ heap
	for (int i = n - 1; i >= 0; --i)
	{
		// Di chuyển root về cuối cùng
		swap(arr[0], arr[i]);

		// Gọi hàm heapify
		heapify(arr, i, 0);
	}
}




int main(){
    int arr[] = {7,5,6,4,3,2,1,9,8};
    int n = sizeof(arr) / sizeof(arr[0]);
    // mergeSort(arr, 0, n-1);
    heapSort(arr,n);

    for (auto item: arr)
	{
		cout << item << " ";
	}
	cout << endl;

    return 0;
}