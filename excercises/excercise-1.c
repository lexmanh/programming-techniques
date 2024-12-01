/*
Tác giả: X
Ngày tạo: 24/11/2024

Bài tập 1: Quản lý thư viện sách
Thông tin sách:

•	Mã sách (string).
•	Tên sách (string).
•	Tác giả (string).
•	Năm xuất bản (int).
•	Giá tiền (float).

Chức năng:

1.	Nhập danh sách sách: Dùng struct, lưu trữ vào mảng động qua con trỏ.
2.	Hiển thị danh sách sách: Dùng đệ quy để duyệt và in thông tin từng sách.
3.	Tìm sách theo mã: Dùng tìm kiếm tuyến tính qua con trỏ.
4.	Liệt kê sách xuất bản sau năm 2000: Dùng con trỏ để lọc và hiển thị.
5.	Sắp xếp sách theo giá tăng dần: Dùng thuật toán sắp xếp nổi bọt (Bubble Sort) qua con trỏ.
6.	Lưu danh sách sách vào tập tin: Ghi dữ liệu vào file văn bản.
7.	Đọc danh sách sách từ tập tin: Đọc và hiển thị dữ liệu từ file.

 */

// Khai báo thư viện
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo cấu trúc sách
typedef struct
{
    char code[20];
    char name[50];
    char author[50];
    int year;
    float price;
} Book;

// Khai báo cấu trúc danh sách sách
typedef struct
{
    Book *books; // Con trỏ lưu trữ mảng sách => chỉ đến địa chỉ đầu tiên của mảng.
    int size;
} BookList;

// Khai báo các nguyên mẫu hàm

// Hàm nhập danh sách sách
void input(BookList *list);

// Hàm hiển thị danh sách sách
void display(BookList list);

// Hàm tìm sách theo mã
void searchByCode(BookList list, char *code);

// Hàm liệt kê sách xuất bản sau năm 2000
void listBooksAfter2000(BookList list);

// Hàm sắp xếp sách theo giá tăng dần
void sortBooksByPrice(BookList list);

// Hàm lưu danh sách sách vào tập tin
void saveToFile(BookList list, char *filename);

// Hàm đọc danh sách sách từ tập tin
void readFromFile(BookList *list, char *filename);

// Hàm tìm kiếm nhị phân
int binarySearch(BookList list, char *code, int left, int right);
void bubbleSort(BookList list);
void insertionSort(BookList list);
void selectionSort(BookList list);
void quickSort(BookList list, int left, int right);
void merge(BookList list, int left, int mid, int right);
void mergeSort(BookList list, int left, int right);

// Hàm main
int main()
{
    BookList list;
    list.size = 0;
    list.books = NULL;  // danh sách sách rỗng

    int choice;
    do
    {
        printf("Chương trình quản lý thư viện sách");
        printf("\n1. Input book list\n");
        printf("2. Display book list\n");
        printf("3. Search book by code\n");
        printf("4. List books after 2000\n");
        printf("5. Sort books by price\n");
        printf("6. Save to file\n");
        printf("7. Read from file\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                input(&list);
            break;
            case 2:
                display(list);
            break;
            case 3:
            {
                char code[20];
                printf("Enter code to search: ");
                scanf("%s", code);
                searchByCode(list, code);
            }
            break;
            case 4:
                listBooksAfter2000(list);
            break;
            case 5:
                sortBooksByPrice(list);
            break;
            case 6:
            {
                char saveFilename[50];
                printf("Enter filename to save: ");
                scanf("%s", saveFilename);
                saveToFile(list, saveFilename);
            }
            break;
            case 7:
            {
                char readFilename[50];
                printf("Enter filename to read: ");
                scanf("%s", readFilename);
                readFromFile(&list, readFilename);
            }
            break;
            case 8:
                free(list.books);
            break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 8.\n");
            break;
        }
    } while (choice != 8);

    free(list.books);
    return 0;
}

// Hàm nhập danh sách sách
void input(BookList *list)
{
    printf("Enter the number of books: ");
    scanf("%d", &list->size);

    // cấp phát bộ nhớ động cho mảng sách
    list->books = (Book *)realloc(list->books, list->size * sizeof(Book));
    if (!list->books) // => if (list->books == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);  // Dừng chương trình nếu không cấp phát được bộ nhớ
    }

    for (int i = 0; i < list->size; i++)
    {
        printf("Enter information of book %d:\n", i + 1);
        printf("Code: ");
        scanf("%s", list->books[i].code); // %s không cần '&' vì code là một mảng ký tự, bản chất là con trỏ.
        printf("Name: ");
        scanf("%s", list->books[i].name); // %s không cần '&' vì name là một mảng ký tự, bản chất là con trỏ.
        printf("Author: ");
        scanf("%s", list->books[i].author); // %s không cần '&' vì author là một mảng ký tự, bản chất là con trỏ.
        printf("Year: ");
        scanf("%d", &list->books[i].year); // %d cần '&' vì year là một biến kiểu int.
        printf("Price: ");
        scanf("%f", &list->books[i].price); // %f cần '&' vì price là một biến kiểu float.
    }
}

// Hàm hiển thị danh sách sách
void display(BookList list)
{
    if (list.size == 0)
    {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < list.size; i++)
    {
        printf("Book %d:\n", i + 1);
        printf("Code: %s\n", list.books[i].code);
        printf("Name: %s\n", list.books[i].name);
        printf("Author: %s\n", list.books[i].author);
        printf("Year: %d\n", list.books[i].year);
        printf("Price: %.2f\n", list.books[i].price);
    }
}

// Hàm tìm sách theo mã
// *code: con trỏ trỏ đến mảng ký tự chứa mã sách cần tìm
void searchByCode(BookList list, char *code)
{
    for (int i = 0; i < list.size; i++)
    {
        // so sánh chuỗi mã sách với mã sách của sách thứ i
        // dùng hàm strcmp trong thư viện string.h
        if (strcmp(list.books[i].code, code) == 0)
        {
            printf("Book found:\n");
            printf("Code: %s\n", list.books[i].code);
            printf("Name: %s\n", list.books[i].name);
            printf("Author: %s\n", list.books[i].author);
            printf("Year: %d\n", list.books[i].year);
            printf("Price: %.2f\n", list.books[i].price);
            return;
        }
    }
    printf("Book with code %s not found!\n", code);
}

// Hàm liệt kê sách xuất bản sau năm 2000
void listBooksAfter2000(BookList list)
{
    int found = 0;
    for (int i = 0; i < list.size; i++)
    {
        if (list.books[i].year > 2000)
        {
            printf("Book %d:\n", i + 1);
            printf("Code: %s\n", list.books[i].code);
            printf("Name: %s\n", list.books[i].name);
            printf("Author: %s\n", list.books[i].author);
            printf("Year: %d\n", list.books[i].year);
            printf("Price: %.2f\n", list.books[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("No books found after 2000.\n");
    }
}

// Hàm sắp xếp sách theo giá tăng dần
void sortBooksByPrice(BookList list)
{
    if (list.size <= 1) return;  // Không cần sắp xếp nếu chỉ có 1 cuốn sách hoặc không có sách
    bubbleSort(list);  // Hoặc có thể chọn bất kỳ thuật toán sắp xếp nào ở đây
}

// Hàm lưu danh sách sách vào tập tin
void saveToFile(BookList list, char *filename)
{
    FILE *file = fopen(filename, "w"); // mode: write
    // Kiểm tra xem file có tồn tại không?
    // Nếu không thì tạo file mới
    if (file == NULL)
    {
        printf("Cannot open file %s!\n", filename);
        return;
    }

    // Ghi số lượng sách vào file ở dòng đầu tiên
    fprintf(file, "%d\n", list.size);

    // Ghi thông tin của từng cuốn sách vào file
    for (int i = 0; i < list.size; i++)
    {
        fprintf(file, "%s\n", list.books[i].code);
        fprintf(file, "%s\n", list.books[i].name);
        fprintf(file, "%s\n", list.books[i].author);
        fprintf(file, "%d\n", list.books[i].year);
        fprintf(file, "%.2f\n", list.books[i].price);
    }

    // Đóng file sau khi ghi xong
    fclose(file);
}

// Hàm đọc danh sách sách từ tập tin
// *list: con trỏ trỏ đến danh sách sách cần đọc
// *filename: con trỏ trỏ đến mảng ký tự chứa tên file cần đọc
void readFromFile(BookList *list, char *filename)
{
    FILE *file = fopen(filename, "r"); // mode: read
    if (file == NULL)
    {
        printf("Cannot open file %s!\n", filename);
        return;
    }

    // Đọc số lượng sách từ file
    fscanf(file, "%d\n", &list->size);

    // Cấp phát bộ nhớ động cho mảng sách
    list->books = (Book *)realloc(list->books, list->size * sizeof(Book));

    // Đọc thông tin của từng cuốn sách từ file
    for (int i = 0; i < list->size; i++)
    {
        fscanf(file, "%s\n", list->books[i].code);
        fscanf(file, "%s\n", list->books[i].name);
        fscanf(file, "%s\n", list->books[i].author);
        fscanf(file, "%d\n", &list->books[i].year);
        fscanf(file, "%f\n", &list->books[i].price);
    }

    // Đóng file sau khi đọc xong
    fclose(file);
}

// Hàm tìm kiếm nhị phân
int binarySearch(BookList list, char *code, int left, int right)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;
    if (strcmp(list.books[mid].code, code) == 0)
    {
        return mid;
    }
    else if (strcmp(list.books[mid].code, code) > 0)
    {
        return binarySearch(list, code, left, mid - 1);
    }
    else
    {
        return binarySearch(list, code, mid + 1, right);
    }
}

// Hàm sắp xếp nổi bọt
void bubbleSort(BookList list)
{
    for (int i = 0; i < list.size - 1; i++)
    {
        for (int j = list.size - 1; j > i; j--)
        {
            if (list.books[j].price < list.books[j - 1].price)
            {
                Book temp = list.books[j];
                list.books[j] = list.books[j - 1];
                list.books[j - 1] = temp;
            }
        }
    }
}

// Hàm sắp xếp chèn
void insertionSort(BookList list)
{
    for (int i = 1; i < list.size; i++)
    {
        Book key = list.books[i];
        int j = i - 1;
        while (j >= 0 && list.books[j].price > key.price)
        {
            list.books[j + 1] = list.books[j];
            j--;
        }
        list.books[j + 1] = key;
    }
}

// Hàm sắp xếp chọn
void selectionSort(BookList list)
{
    for (int i = 0; i < list.size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < list.size; j++)
        {
            if (list.books[j].price < list.books[minIndex].price)
            {
                minIndex = j;
            }
        }
        Book temp = list.books[i];
        list.books[i] = list.books[minIndex];
        list.books[minIndex] = temp;
    }
}

// Hàm sắp xếp nhanh dùng đệ quy
void quickSort(BookList list, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int i = left;
    int j = right;
    float pivot = list.books[(left + right) / 2].price;
    while (i <= j)
    {
        while (list.books[i].price < pivot)
        {
            i++;
        }
        while (list.books[j].price > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            Book temp = list.books[i];
            list.books[i] = list.books[j];
            list.books[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(list, left, j);
    quickSort(list, i, right);
}

// Hàm sắp xếp trộn
void merge(BookList list, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book *L = (Book *)malloc(n1 * sizeof(Book));
    Book *R = (Book *)malloc(n2 * sizeof(Book));

    for (int i = 0; i < n1; i++)
    {
        L[i] = list.books[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = list.books[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].price <= R[j].price)
        {
            list.books[k] = L[i];
            i++;
        }
        else
        {
            list.books[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        list.books[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list.books[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(BookList list, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}


