#include<iostream>
using namespace std;

/*
BUBBLE SORT
*/
void bubbleSort(int *arr, int n){

    // Biến flag để đánh dâu xem sau 1 lần duyệt thì mảng có cần swap lần nào không.
    bool isSwapped;

    for(int i = 0; i < n; ++i){
        // Khởi tạo flag khi bắt đầu duyệt
        isSwapped = false;

        for(int j = 0; j < n - 1; ++j){
            // So sánh 2 phần tử liền kề nhau, nếu không đúng order thì swap
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                isSwapped = true; // Đánh dấu 1 lần swap
            }
        }

        // Nếu sau 1 lần duyệt mà mảng ko có lần swap nào thì không cần duyệt nữa, mảng đã đc sort.
        if(isSwapped == false){
            break;
        }
    }
}

/*
SELECTION SORT
*/
void selectionSort(int arr[], int n){
    // Đánh dấu phần từ có giá trị nhỏ nhất trong 1 lần duyệt
    int minIndex;

    for(int i = 0; i < n; ++i){
        // Gán phần tử đang xét là nhỏ nhất
        minIndex = i;

        for(int j = i + 1; j < n; ++j){
            // So sánh phần tử đang xét với các phần tử sau nó, nếu có số khác nhỏ hơn thì sửa giá trị minIndex
            if(arr[minIndex] > arr[j]){
                minIndex = j;
            }
        }
        // Kết thúc 1 lần duyệt, đổi chỗ số đang xét với số nhỏ nhất vừa tìm được.
        swap(arr[minIndex], arr[i]);
    }
}

/*
INSERTION SORT
*/
void insertionSort(int arr[], int n){
    // Đánh dấu giá trị nhỏ nhất
    int min;

    // Dùng để dịch chuyển vị trí các thành phần trong mảng đã được sort
    int j;

    for(int i = 0; i < n; ++i){
        // Gán giá trị đang xet là min
        min = arr[i];

        j = i - 1;

        // Di chuyển các thành phần mà lớn hơn min ở trong mảng arr[0...i-1] lên một vị trí
        while(j >= 0 & arr[j] > min){
            arr[j + 1] = arr[j];
            j -= 1;
        }

        // Đưa giá trị đang xét về đúng vị trí trong phần được sort của mảng
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

    // Ghép hai mảng theo thứ tự
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

    // Lấy phần tử nằm giữa
    int mid = left + (right - left) / 2;

    // Sort nửa trái
    mergeSort(arr, left, mid);

    // Sort nửa phải
    mergeSort(arr, mid + 1, right);
    
    // Ghép 2 nửa lại theo order
    merge(arr, left, mid, right);
}



/*
QUICK SORT
*/
int partition(int arr[],int left, int right){
    // Đặt pivot(trục) là phần tử cuối trong đoạn cần sort
    int pivot = arr[right];

    // con trỏ để track đoạn gồm toàn các giá trị nhỏ hơn pivot
    int i = left - 1;

    for(int j = left; j < right; ++j){
        // So sánh giá trị đang xét với pivot, nếu nhỏ hơn, nên đưa nó về đoạn được track bởi con trỏ i
        if(arr[j] < pivot){
            i += 1;
            swap(arr[i], arr[j]);
        }
    }
    // Đưa pivot về giữa của 2 đoạn gồm toàn các giá trị nhỏ hơn pivot và gồm toàn các giá trị lớn hơn pivot
    swap(arr[i+1], arr[right]);

    // Return lại index của pivot lúc này
    return i + 1;
}


void quickSort(int arr[], int left, int right){
    // Nếu đoạn cần xét không có phần tử nào, dừng sort
    if(left >= right){
        return;
    }
    // lấy giá trị của pivot sau khi phân chia xong
    int index_pivot = partition(arr, left, right);
    // Đệ quy tiếp với 2 đoạn chia bởi pivot
    quickSort(arr, left, index_pivot - 1);
    quickSort(arr, index_pivot + 1, right);
}


/*
HEAP SORT
*/

void heapify(int arr[], int n, int i){
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
void heapSort(int arr[], int n){
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
    quickSort(arr, 0, n-1);
    // heapSort(arr,n);

    for (auto item: arr)
	{
		cout << item << " ";
	}
	cout << endl;

    return 0;
}