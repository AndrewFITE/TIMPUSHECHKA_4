#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <UnitTest++/TestReporterStdout.h>
#include "modAlphaCipher.h"
using namespace std;

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

string t;
SUITE(encrypt){
    TEST(upcase){
        t = "TANKI"; 
        CHECK_EQUAL(Cipher(3).encrypt(t), "TIAKN");
    }
    TEST(spaces){
        t = "T A N K I"; 
        CHECK_THROW(Cipher(3).encrypt(Cipher(3).getValidText(t)), cipher_error);
    }
    TEST(symbols){
        t = "!@TANKI@!"; 
        CHECK_THROW(Cipher(3).encrypt(Cipher(3).getValidText(t)), cipher_error);
    }
    TEST(lowcase){
        t = "tanki"; 
        CHECK_EQUAL(Cipher(3).encrypt(t), "tiakn");
    }
    TEST(NoText){
        t = ""; 
        CHECK_THROW(Cipher(3).encrypt(Cipher(3).getValidText(t)), cipher_error);
    }    
}
SUITE(decrypt){
    TEST(upcase){
        t = "TIAKN"; 
        CHECK_EQUAL(Cipher(3).decrypt(t), "TANKI");
    }
    TEST(spaces){
        t = "T I A K N"; 
        CHECK_THROW(Cipher(3).decrypt(Cipher(3).getValidText(t)), cipher_error);
    }
    TEST(symbols){
        t = "!@TIAKN@!"; 
        CHECK_THROW(Cipher(3).decrypt(Cipher(3).getValidText(t)), cipher_error);
    }
    TEST(NoText){
        t = "";
        CHECK_THROW(Cipher(3).decrypt(Cipher(3).getValidText(t)), cipher_error);
    }
    TEST(lowcase){
        t = "2+2=5"; 
        CHECK_THROW(Cipher(3).decrypt(Cipher(3).getValidText(t)), cipher_error);
    }    
}
SUITE(KeyTest) {
    TEST(InvalidKey) {
    CHECK_THROW(Cipher(0), invalid_argument);
    }
    TEST(MinusKey) {
    CHECK_THROW(Cipher(-22), invalid_argument);
    
}
}

SUITE(KeyLengthTest) {
    TEST(KeyGreaterThanTextLength) {
        CHECK_THROW(Cipher(22).getValidText("timp"), cipher_error);
    }
}
int main() {
    return UnitTest::RunAllTests();
}
