#include <stdio.h>
#include <string.h>

#define SIZE 5

// Tạo bảng Playfair từ khóa
void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    char used[26] = {0};  // Đánh dấu chữ cái đã dùng
    int k = 0, c = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            while (key[k] && used[key[k] - 'A']) k++;  // Bỏ qua chữ cái trùng
            if (key[k]) {
                matrix[i][j] = key[k];
                used[key[k] - 'A'] = 1;
                k++;
            } else {
                while (used[c] || c == ('J' - 'A')) c++;  // Bỏ qua j và các chữ đã dùng
                matrix[i][j] = 'A' + c;
                used[c] = 1;
                c++;
            }
        }
    }
}

// Tìm vị trí của ký tự trong bảng
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';  // Gộp J vào I
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Mã hóa cặp ký tự
void encryptPair(char matrix[SIZE][SIZE], char *a, char *b) {
    int r1, c1, r2, c2;
    findPosition(matrix, *a, &r1, &c1);
    findPosition(matrix, *b, &r2, &c2);

    if (r1 == r2) {  // Cùng hàng
        *a = matrix[r1][(c1 + 1) % SIZE];
        *b = matrix[r2][(c2 + 1) % SIZE];
    } else if (c1 == c2) {  // Cùng cột
        *a = matrix[(r1 + 1) % SIZE][c1];
        *b = matrix[(r2 + 1) % SIZE][c2];
    } else {  // Hình chữ nhật
        *a = matrix[r1][c2];
        *b = matrix[r2][c1];
    }
}

// Mã hóa Playfair
void encrypt(char text[], char key[]) {
    char matrix[SIZE][SIZE];
    generateMatrix(key, matrix);

    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        if (text[i] == text[i + 1]) text[i + 1] = 'X';  // Chống lặp ký tự
        encryptPair(matrix, &text[i], &text[i + 1]);
    }
}

int main() {
    char text[] = "HELLO";
    char key[] = "WORLD";

    encrypt(text, key);
    printf("MA HOA: %s\n", text);

    return 0;
}
