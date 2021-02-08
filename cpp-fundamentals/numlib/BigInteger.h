//
// Created by valeri on 1.02.21 г..
//
# pragma once

#include <string>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "PrependString.h"

class BigInteger {
private:
    std::string digits;
    unsigned int digitsCount;
    enum OP { ADD, SUB, MUL, DEL };
    std::string zero = "0";

    bool isValid(const std::string& digits) {
        if (digits.empty()) {
            return false;
        }

        int i = 0;

        if (digits.at(0) == '-') {
            i = 1;
        }

        for (int len = digits.size(); i < len; i++) {
            if (!std::isdigit(digits.at(i))) {
                return false;
            }
        }

        return true;
    }

    BigInteger eval(const BigInteger& a, const BigInteger& b, BigInteger::OP operation) const {
        bool AIsNegative = a.isNegative;
        bool BIsNegative = b.isNegative;

        // if x = 0 or y = 0 or (x = 0 and y = 0)
        if (a.isZero()) {
            return b.isZero() ? zero : b;
        } else if (b.isZero()) {
            return a.isZero() ? zero : a;
        }

        // when |a| = |b| and opposite signs
        if (((AIsNegative && !BIsNegative) || (!AIsNegative && BIsNegative)) &&
            a.abs() == b.abs() && operation == BigInteger::OP::ADD) {
            return BigInteger("0");
        }

        if (operation == BigInteger::OP::ADD) {
            // -x + (-y) = -x - y
            if (AIsNegative && BIsNegative) {
                return eval(a.abs(), b.abs(), BigInteger::OP::ADD).negate();
            }
            // x + (-y) = x - y
            else if (!AIsNegative && BIsNegative) {
                return eval(a, b.abs(), BigInteger::OP::SUB);
            }

            // -x + y = y - x
            else if (AIsNegative && !BIsNegative) {
                return _subtract(b.abs(), a.abs());
            }

            // x + y
            else if (!AIsNegative && !BIsNegative) {
                return _add(a, b);
            }
        } else if (operation == BigInteger::OP::SUB) {
            // -x - y
            if (AIsNegative && !BIsNegative) {
                return eval(a.abs(), b.abs(), BigInteger::OP::ADD).negate();
            }
            // x - y
            else if (!AIsNegative && !BIsNegative) {
                if (a == b) {
                    return BigInteger("0");
                }

                return _subtract(a, b);
            }

            // -x - (-y) = -x + y
            else if (AIsNegative && BIsNegative) {
                return eval(a, b.abs(), BigInteger::OP::ADD);
            }

            // x - (-y) = x + y
            else if (!AIsNegative && BIsNegative) {
                return eval(a, b.abs(), BigInteger::OP::ADD);
            }
        }
    }

    std::string _negate(const BigInteger& a) const {
        return a.isNegative ? a.digits : "-" + a.digits;
    }

    std::string _abs(const BigInteger& a) const {
        return a.isNegative ? a.digits.substr(1) : a.digits;
    }

    bool _isNeg(const std::string& a) const {
        return a.at(0) == '-';
    }

    int _compare(const BigInteger& a, const BigInteger& b) const {
        bool AIsNegative = a.isNegative;
        bool BIsNegative = b.isNegative;

        if (AIsNegative && !BIsNegative) {
            return -1;
        } else if (!AIsNegative && BIsNegative) {
            return 1;
        }

        if (AIsNegative && BIsNegative) {
            if (a.digitsCount > b.digitsCount) {
                return -1;
            } else if (a.digitsCount < b.digitsCount) {
                return 1;
            }

            return b.digits.compare(a.digits);
        }

        if (a.digitsCount > b.digitsCount) {
            return 1;
        } else if (b.digitsCount > a.digitsCount) {
            return -1;
        }

        return a.digits.compare(b.digits);
    }

    BigInteger _max(const BigInteger& a,const BigInteger& b) const {
        return _compare(a, b) < 0 ? b : a;
    }

    BigInteger _add(const BigInteger& a, const BigInteger& b) const {
        int lenA = a.digitsCount;
        int lenB = b.digitsCount;
        int idxA = lenA - 1;
        int idxB = lenB - 1;
        PrependString sumStr(std::max(lenA, lenB) + 1);
//        std::string sumStr;
//        sumStr.reserve(std::max(lenA, lenB) + 1);
        short carry = 0;

        while (idxA >= 0 || idxB >= 0) {
            short ac = idxA < 0 ? 0 : a.digits.at(idxA) - '0';
            short bc = idxB < 0 ? 0 : b.digits.at(idxB) - '0';

            short digitSum = ac + bc + carry;

            if (digitSum > 9) {
                carry = 1;
                digitSum = digitSum % (short)10;
            } else {
                carry = 0;
            }

            sumStr.prepend((char)digitSum + 48);
//            sumStr = std::to_string(digitSum) + sumStr;

            idxA -= 1;
            idxB -= 1;
        }

        if (carry > 0) {
            sumStr.prepend('1');
//            sumStr = "1" + sumStr;
        }

        return BigInteger(std::string(sumStr.get_buffer()));
//        return BigInteger(sumStr);
    }

    BigInteger _subtract(const BigInteger& a, const BigInteger& b) const {
        // make so that a > b
        BigInteger subtractee = a.max(b);
        BigInteger subtractor = a == subtractee ? b : a;

        int lenA = subtractee.digitsCount;
        int lenB = subtractor.digitsCount;
        int idxA = lenA - 1;
        int idxB = lenB - 1;
        PrependString subResult(std::max(lenA, lenB));
        short carry = 0;

        while (idxA >= 0 || idxB >= 0) {
            short ac = idxA < 0 ? 0 : subtractee.digits.at(idxA) - '0';
            short bc = idxB < 0 ? 0 : subtractor.digits.at(idxB) - '0';

            short digitSub = ac - bc - carry;

            if (digitSub < 0) {
                carry = 1;
                digitSub += 10;
            } else {
                carry = 0;
            }

            if (!(idxA <= 0 && idxB <= 0 && digitSub == 0)) {
                subResult.prepend((char)digitSub + 48);
            }

            idxA -= 1;
            idxB -= 1;
        }

        return a < b ? _negate(std::string(subResult.get_buffer())) : std::string(subResult.get_buffer());
    }

    BigInteger _mult(const BigInteger& a, const BigInteger& b) const {
        bool isANegative = a.isNegative;
        bool isBNegative = b.isNegative;

        BigInteger _a(a.abs());
        BigInteger _b(b.abs());

        BigInteger r(_b.digits);
        _a = _a - BigInteger("1");
        BigInteger z("0");

        while (_a > z) {
            r = r + _b;
            _a = _a - BigInteger("1");
        }

        if ((!isANegative && isBNegative) ||
        (isANegative && !isBNegative)) {
            return r.negate();
        }

        return r;
    }
public:
    bool isNegative;

    BigInteger(const std::string& digits): digits(digits) {
        if (!isValid(digits)) {
            throw std::invalid_argument("parameter cannot be empty or negative and must be a valid integer");
        }
        digitsCount = digits.size();
        isNegative = _isNeg(digits);
    }

    std::string toString() const {
        return digits;
    }

    bool isZero() const {
        return digits == zero;
    }

    BigInteger negate() const {
        return BigInteger(_negate(digits));
    }

    BigInteger abs() const {
        return BigInteger(_abs(*this));
    }

    BigInteger max(const BigInteger& b) const {
        return BigInteger(_max(*this, b));
    }

    int compare(const BigInteger& other) const {
        return _compare(*this, other);
    }

    BigInteger operator*(const BigInteger& other) const {
        return _mult(*this, other);
    }

    BigInteger operator+(const BigInteger& other) const {
        return BigInteger(eval(digits, other.digits, BigInteger::OP::ADD));
    }

    BigInteger operator-(const BigInteger& other) const {
        return BigInteger(eval(digits, other.digits, BigInteger::OP::SUB));
    }

    bool operator<(const BigInteger& other) const {
        return this->compare(other) < 0;
    }

    bool operator>(const BigInteger& other) const {
        return this->compare(other) > 0;
    }

    bool operator==(const BigInteger& other) const {
        return digits == other.digits;
    }

    bool operator==(const std::string& s) const {
        return digits == s;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bsi) {
        os << bsi.toString();
        return os;
    }
};