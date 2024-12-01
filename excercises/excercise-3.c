/*
Tác giả: X
Ngày tạo: 24/11/2024

Bài tập 3: Xử lý ma trận
Chức năng:

    1.	Nhập ma trận số nguyên: Dùng con trỏ để cấp phát và nhập dữ liệu.
    2.	Hiển thị ma trận: Duyệt qua mảng 2 chiều và in ra màn hình.
    3.	Tìm phần tử lớn nhất và nhỏ nhất trong ma trận: Duyệt qua các phần tử bằng con trỏ.
    4.	Tính tổng các phần tử trên đường chéo chính (nếu là ma trận vuông): Dùng đệ quy để tính tổng.
    5.	Liệt kê các số nguyên tố trong ma trận: Kiểm tra từng phần tử bằng hàm kiểm tra số nguyên tố.
    6.	Sắp xếp các phần tử trong ma trận theo thứ tự tăng dần: Sử dụng thuật toán sắp xếp (Bubble Sort hoặc Merge Sort) qua con trỏ.
    7.	Lưu ma trận vào tập tin: Ghi ma trận vào file văn bản.
    8.	Đọc ma trận từ tập tin: Đọc dữ liệu từ file và hiển thị.

 */

// Khai báo thư viện
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Khai báo cấu trúc ma trận
typedef struct
{
    int **matrix;
    int rows;
    int cols;
} Matrix;

// Khai báo các nguyên mẫu hàm
void input(Matrix *matrix);
void display(Matrix matrix);

// Tìm phần tử lớn nhất và nhỏ nhất trong ma trận
void findMinMax(Matrix matrix);

// Tính tổng các phần tử trên đường chéo chính
int sumMainDiagonal(Matrix matrix);
// C2: Dùng đệ quy
int sumMainDiagonalRecursion(int **matrix, int rows, int cols, int i);

// Kiểm tra số nguyên tố
int isPrime(int n);

// Liệt kê các số nguyên tố trong ma trận
void listPrimes(Matrix matrix);

// Sắp xếp các phần tử trong ma trận theo thứ tự tăng dần
void sortMatrix(Matrix matrix);

// Lưu ma trận vào tập tin
void saveToFile(Matrix matrix, char *filename);

// Đọc ma trận từ tập tin
void readFromFile(Matrix *matrix, char *filename);

// Hàm main
int main()
{
    Matrix matrix;
    matrix.matrix = NULL;
    matrix.rows = 0;
    matrix.cols = 0;

    int choice;
    do
    {
        printf("Chuong trinh xu ly ma tran\n");
        printf("1. Nhap ma tran\n");
        printf("2. Hien thi ma tran\n");
        printf("3. Tim phan tu lon nhat va nho nhat\n");
        printf("4. Tinh tong cac phan tu tren duong cheo chinh\n");
        printf("5. Liet ke cac so nguyen to trong ma tran\n");
        printf("6. Sap xep cac phan tu trong ma tran theo thu tu tang dan\n");
        printf("7. Luu ma tran vao tap tin\n");
        printf("8. Doc ma tran tu tap tin\n");
        printf("9. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            input(&matrix);
            break;
        case 2:
            display(matrix);
            break;
        case 3:
            findMinMax(matrix);
            break;
        case 4:
            printf("Tong cac phan tu tren duong cheo chinh: %d\n", sumMainDiagonal(matrix));
            break;
        case 5:
            listPrimes(matrix);
            break;
        case 6:
            sortMatrix(matrix);
            printf("Ma tran sau khi sap xep:\n");
            display(matrix);
            break;
        case 7:
        {
            char filename[50];
            printf("Nhap ten tap tin de luu: ");
            scanf("%s", filename);
            saveToFile(matrix, filename);
        }
        break;
        case 8:
        {
            char filename[50];
            printf("Nhap ten tap tin de doc: ");
            scanf("%s", filename);
            readFromFile(&matrix, filename);
            // Hiển thị ma trận sau khi đọc từ file
            display(matrix);
        }
        break;
        case 9:
            free(matrix.matrix);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            break;
        }
    } while (choice != 9);

    return 0;
}

// Viết các hàm xử lý ở đây...