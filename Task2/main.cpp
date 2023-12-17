#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;

void check(wstring text, wstring key,  bool destructCipherText = false)
{
	try {
		wstring cipherText;
		wstring decryptedText;
		Cipher cipher(key);
		cipherText = cipher.encrypt(text);
		if (destructCipherText)
			cipherText.front() = towlower(cipherText.front());
		decryptedText = cipher.decrypt(cipherText);
		wcout << L"key = " << key << endl;
		wcout << L"Text = " << text << endl;
		wcout << L"Encrypted text: " << cipherText << endl;
		wcout << L"Decrypted text: " << decryptedText << endl;
	} catch (const cipher_error & e) {
		wcerr << "Error: " << e.what() << endl;
	}
}

void interface_program()
{
	wstring key;
	wstring text;
	unsigned op;
	wcout << L"Введите ключ (количество столбцов): ";
	wcin >> key;
	Cipher cipher(key);
	do {
		wcout << L"Выберите операцию (0 - выход, 1 - шифрование, 2 - расшифрование, 3 - ввод нового ключа): ";
		wcin >> op;
		if (op > 3) {
			wcout << L"Данной операции не существует! Выберите существующую операцию!";
		} else if (op > 0 && op < 3) {
			wcout << L"Введите текст: ";
			wcin >> text;
			if (op == 1) {
				wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
			} else {
				wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
			}
		} else if (op == 3) {
			wcout << L"Введите новый ключ: ";
			wcin >> key;
			cipher.set_key(key);
		}
	} while (op != 0);
}

int main()
{
	locale loc("ru_RU.UTF-8");
	locale::global(loc);
	wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
	unsigned mode_program;
	do {
		wcout << L"Выберите операцию (0 - завершение работы, 1 - интерфейс, 2 - тест программы): ";
		wcin >> mode_program;
		if (mode_program == 1) {
			interface_program();
		} else if (mode_program == 2) {
			wstring line = L"----------------------------------------";
			wcout << line << endl;
			check(L"ТИМП", L"0");
			wcout << line << endl;
			check(L"ТИМП", L"");
			wcout << line << endl;
			check(L"ТИМП", L"@#$%&*");
			wcout << line << endl;
			check(L"ТИМП", L"3", true);
			wcout << line << endl;
			check(L"ТИМП", L"2");
			wcout << line << endl;
			check(L"ГР500АНТ058А", L"3");
			wcout << line << endl;
			check(L"ТИМП", L"3");
			wcout << line << endl;
			check(L"", L"3");
			wcout << line << endl;
			check(L"ТИМП", L"4");
			wcout << line << endl;
		}
	} while (mode_program != 0);
	return 0;
}
