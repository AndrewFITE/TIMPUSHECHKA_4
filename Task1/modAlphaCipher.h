/** @file
 * @author Окороков А.С.
 * @version 1.0
 * @date 17.12.23
 * @copyright ИБСТ ПГУ
 * @warning Лабораторная работа №4
 * @brief Заголовочный файл для модуля Gronsfeld
 */
#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <locale>
using namespace std;

/** @brief Шифрование методом Гронсфельда
 * @details Ключ устанавливается в конструкторе
 * Для зашифрования и расшифрования предназначены методы encrypt и decrypt
 * @warning Реализация только для русского языка!
 */
class modAlphaCipher
{
private:
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";  //алфавит по порядку
	map <wchar_t,int> alphaNum;   //ассоциативный массив "номер по символу"
	vector <int> key;          //ключ
	/**
     * @brief Преобразование строка-вектор
     * @param [in] s Строка
     * @return Вектор типа int
     */
	vector<int> convert(const wstring& ws);//преобразование строка-вектор
	/**
     * @brief Преобразование вектор-строка
     * @param [in] v Вектор типа int
     * @return string
     */
	wstring convert(const vector<int>& v);//преобразование вектор-строка
	/**
     * @brief Проверка на хороший ключ
     * @param [in] s Строка wstring
     * @return Строка wstring
     * @throw cipher_error, если ключ пустой или в ключе находится символ, не принадлежащий алфавиту 
     */
	wstring getValidKey(const wstring & ws);
	/**
     * @brief Метод для валидации открытого текста \n
     * Все символы не принадлежащие алфавиту игнорируются \n
     * Все строчные символы преобразуются к прописным
     * @param [in] s Строка wstring
     * @return Строка wstring
     * @throw cipher_error, если текст пустой 
     */
	wstring getValidOpenText(const wstring & ws);
	/**
     * @brief Метод для валидации текста зашифрования \n
     * @param [in] s Строка wstring
     * @return Строка wstring
     * @throw cipher_error, если текст пустой и в тексте содержатся строчные буквы 
     */
	wstring getValidCipherText(const wstring & ws);
public:
	modAlphaCipher() = delete;//запретим конструктор без параметров
	modAlphaCipher(const wstring& wskey);  //конструктор для установки ключа
	/**
     * @brief Зашифровывание
     * @param [in] open_text Открытый текст. Не должен быть пустой строкой
     * Строчные символы автоматически преобразуются к прописным
     * Все "не" буквы удаляются
     * @return Зашифрованная строка
     * @throw cipher_error, если текст пустой
     */
	wstring encrypt(const wstring& open_text);  //зашифрование
	/**
     * @brief Расшифровывание
     * @param [in] cipher_text Строка для зашифрования
     * @return Расшифрованная строка
     * @throw cipher_error, если текст пустой
     */
	wstring decrypt(const wstring& cipher_text);//расшифрование
};

/** @brief класс-исключение cipher_error 
 * @details производный от класса invalid_argument
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
