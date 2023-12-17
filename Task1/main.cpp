#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <typeinfo>
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"\nkey = " << key << endl;
        wcout << L"Text = " << Text << endl;
        wcout << L"Encrypted text: " << cipherText << endl;
        wcout << L"Decrypted text: " << decryptedText << "\n" << endl;
    } catch (const cipher_error & e) {
        wcerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    check(L"ГРАНТА", L"ЛАДА");
    check(L"КВ-2", L"");
    check(L"СИЛА", L"ОТЭЦ666");
    check(L"ПРИОРА", L"Лада");
    check(L"1234", L"ЛАДА");
    check(L"С и л а", L"ОТЭЦ");
    check(L"@#$", L"ТАНК");
}
