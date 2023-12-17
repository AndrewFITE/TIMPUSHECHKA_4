#include "modAlphaCipher.h"
using namespace std;

Cipher::Cipher(int k) {
    if (k < 2)
        throw invalid_argument("Неверный ключ!");
    key = k;
}

// Функция для шифрования текста
string Cipher::encrypt(const string& text) {
	string valid_text = getValidText(text);
    int row = key, col = valid_text.length();
    vector<vector<char>> matrix(row, vector<char>(col, ' '));

    int direction = 0;
    int row_index = 0, col_index = 0;

    // Заполнение матрицы символами текста по диагонали
    for (int i = 0; i < col; i++) {
        if (row_index == 0 || row_index == row - 1)
            direction = 1 - direction;
        matrix[row_index][col_index++] = text[i];
        if (direction)
            row_index++;
        else
            row_index--;
    }

    string cipher_text;
    // Считывание элементы матрицы построчно для создания зашифрованного текста
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (matrix[i][j] != ' ')
                cipher_text += matrix[i][j];

    return cipher_text;
}

// Функция для дешифрования текста
string Cipher::decrypt(const string& cipher_text) {
    int row = key, col = cipher_text.length();
    vector<vector<char>> matrix(row, vector<char>(col, ' '));

    int direction;
    int row_index = 0, col_index = 0;

    // Заполнение матрицы символами '*' по диагонали
    for (int i = 0; i < col; i++) {
        if (row_index == 0)
            direction = 1;
        if (row_index == row - 1)
            direction = 0;
        matrix[row_index][col_index++] = '*';
        if (direction)
            row_index++;
        else
            row_index--;
    }

    int index = 0;
    // Замена символов '*' на символы зашифрованного текста построчно
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (matrix[i][j] == '*' && index < col)
                matrix[i][j] = cipher_text[index++];

    string text;
    row_index = 0, col_index = 0;
    // Считывание матрицы по диагонали для восстановления исходного текста
    for (int i = 0; i < col; i++) {
        if (row_index == 0)
            direction = 1;
        if (row_index == row - 1)
            direction = 0;
        if (matrix[row_index][col_index] != '*')
            text += matrix[row_index][col_index++];
        if (direction)
            row_index++;
        else
            row_index--;
    }

    return text;
}
string Cipher::getValidText(const string & text) {
    if (text.empty()) {
        throw cipher_error("Пустая строка!");
    }
    if (key >= text.length()) {
        throw cipher_error("Длина ключа не может быть больше длины текста!");
    }
    for (char c : text) {
        if (!isalpha(c)) {
            throw cipher_error("Текст содержит недопустимые символы!");
        }
    }
    return text; // Возвращаем длину строки, если все проверки пройдены
}
