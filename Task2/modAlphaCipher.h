/** @file
 * @author Окороков А.С.
 * @version 1.0
 * @date 17.12.23
 * @copyright ИБСТ ПГУ
 * @warning Лабораторная работа №4
 * @brief Заголовочный файл для модуля шифра табличной перестановки
 */
#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cctype>
#include <locale>
#include <codecvt>
using namespace std;

/** @brief Шифрование методом Табличной перестановки
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt
 * @warning Реализация только для английского языка
 */
class Cipher
{
private:
    int key;
public:
    Cipher() = delete; //запретим конструктор без параметров
    Cipher(int k); //конструктор для установки ключа
    /**
     * @brief Метод для проверки текста для зашифрования или расшифрования \n
     * Все символы не принадлежащие английскому алфавиту удаляются \n
     * @param [in] text строка с сообщением типа string
     * @return строка типа string
     * @throw cipher_error, если строка пустая
   	 */
    string getValidText(const string & text); //делаем метод публичным
    /**
     * @brief Зашифрование
     * @param [in] text Строка для зашифрования
     * @return Зашифрованная строка
     */
    string encrypt(const string& text); //зашифрование
    /**
     * @brief Расшифровывание
     * @param [in] cioher_text Строка для зашифрования
     * @return Расшифрованная строка
     */
    string decrypt(const string& cipher_text); //расшифрование
};

/** @brief класс-исключение cipher_error 
 * @details производный от класса std::invalid_argument \n
 * В данном классе перегружены конструкторы с параметрами. \n
 * При перегрузке явно указан вызов конструктора базового класса с параметром
 */
class cipher_error: public invalid_argument
{
public:
    explicit cipher_error (const string& what_arg):
        invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        invalid_argument(what_arg) {}
};
