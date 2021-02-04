#include <iostream>
#include "BigInteger.cpp"
#include <assert.h>

int main() {
    BigInteger a("0");
    BigInteger b("0");

    assert((a + b) == "0");

    BigInteger a00("0");
    BigInteger b00("2");

    assert(a00 + b00 == "2");
    assert(b00 + a00 == "2");

    BigInteger a01("-2");
    BigInteger b01("0");

    assert(a01 + b01 == "-2");

    BigInteger a2("-9");
    BigInteger b2("9");

    assert((a2 + b2) == "0");
//
//
    BigInteger a3("9");
    BigInteger b3("-9");

    assert((a3 + b3) == "0");
//
    BigInteger a4("-10");
    BigInteger b4("-20");

    assert((a4 + b4) == "-30");
//
    BigInteger a5("399");
    BigInteger b5("101");

    assert((a5 + b5) == "500");
//
    BigInteger a6("30");
    BigInteger b6("-30");

    assert((a6 - b6) == "60");
//
    BigInteger a7("-30");
    BigInteger b7("30");

    assert((a7 - b7) == "-60");

    // Test 'max' method
    BigInteger x("-1");
    BigInteger y("-3");

    assert(x.max(y) == "-1");

    BigInteger x2("200");
    BigInteger y2("100");

    assert(x2.max(y2) == "200");

    BigInteger x3("1000");
    BigInteger y3("999");

    assert(x3.max(y3) == "1000");

    BigInteger x4("892");
    BigInteger y4("982");

    assert(x4.max(y4) == "982");

    BigInteger x5("-3");
    BigInteger y5("5");

    assert(x5.max(y5) == "5");

    BigInteger x6("5");
    BigInteger y6("-3");

    assert(x6.max(y6) == "5");

    BigInteger x7("0");
    BigInteger y7("1");

    assert(x7.max(y7) == "1");

    BigInteger x8("1");
    BigInteger y8("0");

    assert(x8.max(y8) == "1");

    BigInteger x9("0");
    BigInteger y9("-1");

    assert(x9.max(y9) == "0");

    BigInteger x10("0");
    BigInteger y10("100");
    BigInteger x11("100");
    BigInteger y11("0");

    assert(x10.max(y10) == y10.max(x10));

    BigInteger x12("2");
    BigInteger y12("1");
    BigInteger z12("3");

    assert(x12.max(y12).max(z12) == "3");

    // Subtract
    BigInteger as("30");
    BigInteger bs("10");

    assert((as - bs) == "20");

    BigInteger as1("1000");
    BigInteger bs1("1");

    assert(as1 - bs1 == "999");

    BigInteger as2("40");
    BigInteger bs2("11");

    assert(as2 - bs2 == "29");

    assert(bs2 - as2 == "-29");

    BigInteger as3("734723894792834789237489327489237489274892");
    BigInteger bs3("293829839289382938928392839289328938928398");

    assert(as3 - bs3 == "440894055503451850309096488199908550346494");

    return 0;
}
