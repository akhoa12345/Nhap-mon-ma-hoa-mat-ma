﻿
#include <fstream>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

class BigInt {
private:
    bool _negative;
    std::string _num;

    int _charIntToInt(char c) const;
    char _intToChar(int num) const;
    std::string _reverse(const std::string& str) const;
    std::string _removeLeadingZeros(const std::string& num) const;
    void _addLeadingZeros(std::string& num, int totalZeros) const;
    void _addTrailingZeros(std::string& num, int totalZeros) const;
    bool _validate(const std::string& num);
    bool _isNegative(const std::string& num);
    std::string _absolute(const std::string& num);

public:
    BigInt();
    BigInt(const std::string& num);
    BigInt(const std::string& num, bool negative);
    BigInt(const BigInt& num);

    void setNegative(bool negativity);

    void operator=(const BigInt& num);

    ~BigInt();

    bool isNegative() const;

    char& operator[](const int index);

    bool operator<(const BigInt& num) const;
    bool operator<(const std::string& num) const;

    bool operator>(const BigInt& num) const;
    bool operator>(const std::string& num) const;

    bool operator==(const BigInt& num) const;
    bool operator==(const std::string& num) const;

    bool operator!=(const BigInt& num) const;
    bool operator!=(const std::string& num) const;

    bool operator<=(const BigInt& num) const;
    bool operator<=(const std::string& num) const;

    bool operator>=(const BigInt& num) const;
    bool operator>=(const std::string& num) const;

    BigInt operator+(const BigInt& num) const;
    BigInt operator+(const std::string& num) const;

    void operator+=(const BigInt& num);
    void operator+=(const std::string& num);

    BigInt operator-(const BigInt& num) const;
    BigInt operator-(const std::string& num) const;

    void operator-=(const BigInt& num);
    void operator-=(const std::string& num);

    BigInt operator*(const BigInt& num) const;
    BigInt operator*(const std::string& num) const;

    void operator*=(const BigInt& num);
    void operator*=(const std::string& num);

    std::tuple<BigInt, BigInt> operator/(const BigInt& num) const;
    std::tuple<BigInt, BigInt> operator/(const std::string& num) const;

    void operator/=(const BigInt& num);
    void operator/=(const std::string& num);

    BigInt operator%(const BigInt& base) const;
    BigInt operator%(const std::string& base) const;

    //void operator/=(const BigInt& num);

    void operator%=(const BigInt& num);

    static BigInt max(const BigInt& a, const BigInt& b);
    static BigInt modularAddition(const BigInt& a, const BigInt& b, const BigInt& m);
    static BigInt modularMultiplication(const BigInt& a, const BigInt& b, const BigInt& m);
    static BigInt GCD(BigInt a, BigInt b);
    static std::tuple<BigInt, BigInt, BigInt> Bezout(const BigInt& a, const BigInt& b);
    static BigInt inverseModulo(const BigInt& a, const BigInt& m);
    // Computes (base ^ exponent) % modulus using modular exponentiation
    static BigInt modularPower(const BigInt& base, const BigInt& exponent, const BigInt& modulus);


    friend std::istream& operator>>(std::istream& in, BigInt& num);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
    friend std::ostream& operator<<(std::ostream& out, const std::tuple<BigInt, BigInt, BigInt>& numVector);
};


class ElGamal {
public:
    ElGamal(const BigInt& p, const BigInt& g, const BigInt& a);
    std::tuple<BigInt, BigInt> encrypt(const BigInt& plaintext, const BigInt& b);
    BigInt decrypt(const std::tuple<BigInt, BigInt>& ciphertext) const;

private:
    BigInt _p; // Prime modulus
    BigInt _g; // Generator
    BigInt _a; // Private key
};

/**
 * @brief Convert a char to int.
 *
 * @param c char
 * @return int
 */


int BigInt::_charIntToInt(char c) const {
    return c - '0';
}

/**
 * @brief Convert an int to char.
 *
 * @param num int
 * @return char
 */
char BigInt::_intToChar(int num) const {
    return num + '0';
}

/**
 * @brief Reverse a string.
 *
 * @param str const std::string&
 * @return std::string
 */
std::string BigInt::_reverse(const std::string& str) const {
    return std::string(str.rbegin(), str.rend());
}

/**
 * @brief Remove leading zeros (00123 => 123)
 *
 * @param  num const std::string&
 * @return std::string
 */
std::string BigInt::_removeLeadingZeros(const std::string& num) const {
    std::stringstream ss;
    bool valid = false;

    for (int i = 0; i < (int)num.length(); ++i) {
        if (num[i] == '0' && !valid) {
            continue;
        }
        else {
            valid = true;
            ss << num[i];
        }
    }

    if (ss.str().length() == 0) {
        ss << 0;
    }

    return ss.str();
}

/**
 * @brief Add leading zeros (123, zeros = 4 => 0000123)
 *
 * @param num std::string&
 * @param totalZeros int
 */
void BigInt::_addLeadingZeros(std::string& num, int totalZeros) const {
    std::stringstream ss;

    for (int i = 1; i <= totalZeros; ++i) {
        ss << 0;
    }
    ss << num;

    num = ss.str();
}

/**
 * @brief Add trailing zeros (123, zeros = 4 => 1230000)
 *
 * @param num std::string&
 * @param totalZeros int
 */
void BigInt::_addTrailingZeros(std::string& num, int totalZeros) const {
    std::stringstream ss;

    ss << num;
    for (int i = 1; i <= totalZeros; ++i) {
        ss << 0;
    }

    num = ss.str();
}

/**
 * @brief Check if a number is valid (i.e only digits and minus mark)
 *
 * @param num const std::string&
 * @return true if valid
 * @return false otherwise
 */
bool BigInt::_validate(const std::string& num) {
    for (int i = 0; i < (int)num.length(); ++i) {
        if (i == 0 && num[i] == '-') continue;
        else if (num[i] >= '0' && num[i] <= '9') continue;
        else return false;
    }
    return true;
}

/**
 * @brief Check if a number is negative (aka num[0] == '-')
 *
 * @param num const std::string&
 * @return true if that number is a negative number
 * @return false otherwise
 */
bool BigInt::_isNegative(const std::string& num) {
    return num[0] == '-';
}

/**
 * @brief Absolute value of a negative number (aka str.substr(1, str.length() - 1))
 *
 * @param num const std::string&
 * @return std::string
 */
std::string BigInt::_absolute(const std::string& num) {
    return num.substr(1, num.length() - 1);
}

BigInt::BigInt() {
    // Do nothing
    _negative = false;
    _num = "0";
}

BigInt::BigInt(const std::string& num) {
    if (!_validate(num)) {
        throw std::runtime_error("Invalid integer format");
    }

    _negative = _isNegative(num);

    _num = (_negative) ? _removeLeadingZeros(_absolute(num)) : _removeLeadingZeros(num);
}

BigInt::BigInt(const std::string& num, bool negative) {
    _num = _removeLeadingZeros(num);
    _negative = negative;
}

BigInt::BigInt(const BigInt& num) {
    _num = num._num;
    _negative = num._negative;
}

/**
 * @brief Set the number's sign (negative or not)
 *
 * @param negativity bool | true = negative, false = positive.
 */
void BigInt::setNegative(bool negativity) {
    _negative = negativity;
}

void BigInt::operator=(const BigInt& num) {
    _num = num._num;
    _negative = num._negative;
}

BigInt::~BigInt() {
    // Do nothing
}

bool BigInt::isNegative() const {
    return _negative;
}

char& BigInt::operator[](const int index) {
    if (index < 0 || index >(int)_num.length()) {
        throw std::runtime_error("Index out of bound");
    }
    return _num[index];
}

bool BigInt::operator<(const BigInt& num) const {
    // 2 số khác dấu => số nhỏ hơn chắc chắn là số âm
    if (num.isNegative() != isNegative()) {
        return isNegative();
    }

    // 2 số có độ dài khác nhau => tùy vào dấu mà đưa ra số nhỏ hơn.
    if (_num.length() != num._num.length()) {
        return (isNegative()) ? (_num.length() > num._num.length())
            : (_num.length() < num._num.length());
    }

    return isNegative() ? (_num > num._num) : (_num < num._num);
}

bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}

bool BigInt::operator>(const BigInt& num) const {
    return !(*this <= num);
}

bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}

bool BigInt::operator==(const BigInt& num) const {
    return (_num == num._num) && (_negative == num._negative);
}

bool BigInt::operator==(const std::string& num) const {
    return *this == BigInt(num);
}

bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}

bool BigInt::operator!=(const std::string& num) const {
    return *this != BigInt(num);
}

bool BigInt::operator<=(const BigInt& num) const {
    return (*this == num || *this < num);
}

bool BigInt::operator<=(const std::string& num) const {
    return *this <= BigInt(num);
}

bool BigInt::operator>=(const BigInt& num) const {
    return (*this == num || *this > num);
}

bool BigInt::operator>=(const std::string& num) const {
    return *this >= num;
}

BigInt BigInt::operator+(const BigInt& num) const {
    // Xét dấu phép cộng. Đơn giản là khác dấu => chuyển sang phép trừ, cùng dấu => mang dấu chung.
    if (isNegative() != num.isNegative()) {
        return isNegative() ? num - BigInt(_num, !isNegative()) : *this - BigInt(num._num, !num.isNegative());
    }

    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    // Thêm số 0 vào trước để 2 string bằng nhau => tránh index out of bound.
    if ((int)_num.length() > (int)secondNum.length()) {
        _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
    }
    else if ((int)_num.length() < (int)secondNum.length()) {
        _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
    }

    // Cộng như hồi tiểu học (từ phải sang trái)
    int carry = 0;
    for (int i = (int)firstNum.length() - 1; i >= 0; --i) {
        int currentSum = _charIntToInt(firstNum[i]) + _charIntToInt(secondNum[i]) + carry;

        ss << currentSum % 10;
        carry = currentSum / 10;
    }

    if (carry > 0) {
        while (carry > 0) {
            ss << carry % 10;
            carry /= 10;
        }
    }

    return BigInt(_reverse(ss.str()), isNegative());
}

BigInt BigInt::operator+(const std::string& num) const {
    return *this + BigInt(num);
}

void BigInt::operator+=(const BigInt& num) {
    // Goes brrr
    *this = *this + num;
}

void BigInt::operator+=(const std::string& num) {
    *this += BigInt(num);
}

BigInt BigInt::operator-(const BigInt& num) const {
    // Xét dấu phép trừ:
    // a > 0, b < 0 aka a - (-b): trả về a + b
    // a < 0, b > 0 aka -a - b: trả về -(a + b)
    if (isNegative() != num.isNegative()) {
        BigInt result = BigInt(_num) + BigInt(num._num);
        result.setNegative(isNegative());
        return result;
    }

    // Nếu cả 2 số đều âm thì lấy num - *this. Hay là, (-a) - (-b) = b - a.
    if (isNegative() && num.isNegative()) {
        return BigInt(num._num) - BigInt(_num);
    }

    // Các trường hợp trừ 0 và 0 trừ.
    if (num == "0") {
        return *this;
    }

    if (_num == "0" && num != "0") {
        BigInt result = num;
        result.setNegative(!num.isNegative());
        return result;
    }

    // Trường hợp còn lại - 2 số nguyên dương trừ nhau.
    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    // Thêm số 0 vào trước để 2 string bằng nhau => tránh index out of bound.
    if ((int)_num.length() > (int)secondNum.length()) {
        _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
    }
    else if ((int)_num.length() < (int)secondNum.length()) {
        _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
    }

    // Swap order if firstNum < secondNum
    if (*this < num) {
        std::swap(firstNum, secondNum);
    }

    // Reverse both of strings
    firstNum = _reverse(firstNum);
    secondNum = _reverse(secondNum);

    int carry = 0;

    for (int i = 0; i < (int)firstNum.length(); i++) {
        int sub = _charIntToInt(firstNum[i]) - _charIntToInt(secondNum[i]) - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        ss << sub;
    }

    return BigInt(_reverse(ss.str()), (*this < num));
}

BigInt BigInt::operator-(const std::string& num) const {
    return *this - BigInt(num);
}

void BigInt::operator-=(const BigInt& num) {
    *this = *this - num;
}

void BigInt::operator-=(const std::string& num) {
    *this -= BigInt(num);
}

BigInt BigInt::operator*(const BigInt& num) const {
    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    if (firstNum == "0" || secondNum == "0") {
        return BigInt("0");
    }

    BigInt result;

    int carry = 0;
    for (int i = (int)secondNum.length() - 1; i >= 0; --i) {
        if (secondNum[i] == '0') continue;
        for (int j = (int)firstNum.length() - 1; j >= 0; --j) {
            int current_prod = _charIntToInt(firstNum[j]) * _charIntToInt(secondNum[i]) + carry;

            ss << current_prod % 10;
            carry = current_prod / 10;
        }

        while (carry > 0) {
            ss << carry % 10;
            carry /= 10;
        }

        std::string lineResult = _reverse(ss.str());
        _addTrailingZeros(lineResult, secondNum.length() - i - 1);

        result += BigInt(lineResult); ss.str("");
    }

    // Result sign
    result.setNegative(isNegative() != num.isNegative());

    return result;
}

BigInt BigInt::operator*(const std::string& num) const {
    return *this * BigInt(num);
}

void BigInt::operator*=(const BigInt& num) {
    // Goes brrr
    *this = *this * num;
}

void BigInt::operator*=(const std::string& num) {
    *this *= BigInt(num);
}

/**
 * @note Thuật tham khảo từ Tài liệu giáo khoa chuyên tin, quyển 1
 *
 * (c) thầy Hồ Sĩ Đàm, Đỗ Đức Đông, Lê Minh Hoàng, Nguyễn Thanh Hùng.
 *
 * @param  num const BigInt&
 * @return std::tuple<quotient, remainder>
 */
std::tuple<BigInt, BigInt> BigInt::operator/(const BigInt& num) const {
    BigInt zero("0");

    if (num == zero) {
        throw std::runtime_error("Zero divison");
    }

    std::vector<BigInt> kb(11, zero);

    for (int i = 1; i <= 10; ++i) {
        kb[i] = kb[i - 1] + num;
    }

    BigInt c(zero);
    std::string hold = "";

    for (int i = 0; i < (int)_num.length(); ++i) {
        hold = hold + _num[i];

        int k = 0;
        for (; kb[k] <= hold; ++k);

        c._num += _intToChar(k - 1);

        hold = (BigInt(hold) - kb[k - 1])._num;
    }

    c._num = _removeLeadingZeros(c._num);

    return std::make_tuple(BigInt(c), BigInt(hold));
}

std::tuple<BigInt, BigInt> BigInt::operator/(const std::string& num) const {
    return *this / BigInt(num);
}

void BigInt::operator/=(const BigInt& num) {
    *this = std::get<0>(*this / num);
}

void BigInt::operator/=(const std::string& num) {
    *this /= BigInt(num);
}

/**
 * @note Thuật tham khảo từ Tài liệu giáo khoa chuyên tin, quyển 1
 *
 * (c) thầy Hồ Sĩ Đàm, Đỗ Đức Đông, Lê Minh Hoàng, Nguyễn Thanh Hùng.
 */
BigInt BigInt::operator%(const BigInt& base) const {
    auto result = *this / base;

    if (*this < "0") {
        return base - std::get<1>(result);
    }

    return std::get<1>(*this / base);
}

BigInt BigInt::operator%(const std::string& base) const {
    return *this % BigInt(base);
}

void BigInt::operator%=(const BigInt& num) {
    // Goes brrr
    *this = *this % num;
}

/**
 * @brief Max value of the pair <a, b>
 *
 * @param a const BigInt&
 * @param b const BigInt&
 * @return BigInt
 */
BigInt BigInt::max(const BigInt& a, const BigInt& b) {
    return (a > b) ? a : b;
}

/**
 * @brief Modular addition (aka (a + b) % m)
 *
 * @param a const BigInt&
 * @param b const BigInt&
 * @param m const BigInt&
 * @return BigInt
 */
BigInt BigInt::modularAddition(const BigInt& a, const BigInt& b, const BigInt& m) {
    BigInt zero("0");

    if (m <= zero) {
        throw std::runtime_error("Invalid modular base");
    }

    BigInt first = (a >= zero) ? a : (m - a);
    BigInt second = (b >= zero) ? b : (m - b);
    return ((first % m) + (second % m)) % m;
}

/**
 * @brief Modular multiplication (aka (a * b) % m)
 *
 * @param a const BigInt&
 * @param b const BigInt&
 * @param m const BigInt&
 * @return BigInt
 */
BigInt BigInt::modularMultiplication(const BigInt& a, const BigInt& b, const BigInt& m) {
    BigInt zero("0");

    if (m <= zero) {
        throw std::runtime_error("Invalid modular base");
    }

    BigInt first = (a >= zero) ? a : m - a;
    BigInt second = (b >= zero) ? b : m - b;
    return ((first % m) * (second % m)) % m;
}

/**
 * @brief Find Greatest Common Divisor of (a, b)
 *
 * @param a BigInt
 * @param b BigInt
 * @return BigInt
 */
BigInt BigInt::GCD(BigInt a, BigInt b) {
    BigInt c = a % b;
    while (c > "0") {
        a = b; b = c; c = a % b;
    }
    return b;
}

BigInt BigInt::inverseModulo(const BigInt& a, const BigInt& m) {
    auto res = Bezout(a, m);

    if (std::get<0>(res) != "1") {
        throw std::runtime_error("Inverse modulo doesn't exist");
    }

    return std::get<1>(res) % m;
}

//BigInt BigInt::modularPower(const BigInt& base, const BigInt& exponent, const BigInt& modulus) {
//    BigInt result("1");
//    BigInt baseCopy(base % modulus);
//
//    while (exponent > "0") {
//        if (exponent % "2" == "1") {
//            result = (result * baseCopy) % modulus;
//        }
//        baseCopy = (baseCopy * baseCopy) % modulus;
//        exponent /= "2";
//    }
//
//    return result;
//}


/**
 * @brief Tìm Bezout Identity (aka tìm x, y sao cho ax + by = (a, b))
 *
 * @param a const BigInt&
 * @param b const BigInt&
 * @return std::tuple<BigInt, BigInt, BigInt>
 */
std::tuple<BigInt, BigInt, BigInt> BigInt::Bezout(const BigInt& a, const BigInt& b) {
    if (a == "0") {
        return std::tuple<BigInt, BigInt, BigInt>{b, BigInt("0"), BigInt("1")};
    }

    auto recursiveResult = Bezout(b % a, a);

    std::tuple<BigInt, BigInt, BigInt> result{
        std::get<0>(recursiveResult),
        std::get<2>(recursiveResult) - std::get<0>(b / a) * std::get<1>(recursiveResult),
        std::get<1>(recursiveResult)
    };

    return result;
}

/**
 * @brief Tìm modulo nghịch đảo của a (aka ax \equiv 1 (mod m))
 *
 * @param a const BigInt& a
 * @param m const BigInt& m
 * @return BigInt
 *
 * @throw std::runtime_error
 */


std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string s; in >> s;
    num = BigInt(s);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.isNegative()) {
        out << '-';
    }
    out << num._num;
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::tuple<BigInt, BigInt, BigInt>& numVector) {
    out << std::get<0>(numVector);
    out << ' ';
    out << std::get<1>(numVector);
    out << ' ';
    out << std::get<2>(numVector);
    out << ' ';
    return out;
}

// ElGamal constructor
ElGamal::ElGamal(const BigInt& p, const BigInt& g, const BigInt& a)
    : _p(p), _g(g), _a(a) {}

// ElGamal encryption method
std::tuple<BigInt, BigInt> ElGamal::encrypt(const BigInt& plaintext, const BigInt& b) {
    // Generate a random value for the ephemeral key
    // (In practice, this should be a secure random number, not just 'b')
    // BigInt b = /* generate_random_number() */;

    // Compute the ciphertext pair (c1, c2)
    BigInt c1 = BigInt::modularMultiplication(BigInt::modularMultiplication(_g, b, _p), _a, _p);
    BigInt c2 = BigInt::modularMultiplication(BigInt::modularPower(_g, b, _p), plaintext, _p);

    return std::make_tuple(c1, c2);
}

// ElGamal decryption method
BigInt ElGamal::decrypt(const std::tuple<BigInt, BigInt>& ciphertext) const {
    // Extract the components of the ciphertext
    BigInt c1 = std::get<0>(ciphertext);
    BigInt c2 = std::get<1>(ciphertext);

    // Compute the shared secret
    BigInt s = BigInt::modularPower(c1, _a, _p);

    // Compute the modular inverse of s
    BigInt sInverse = BigInt::inverseModulo(s, _p);

    // Compute the decrypted plaintext
    BigInt plaintext = BigInt::modularMultiplication(c2, sInverse, _p);

    return plaintext;
}


class ElGamalVerifier {
public:
    ElGamalVerifier(const BigInt& p, const BigInt& g, const BigInt& y);

    bool verify(const BigInt& m, const BigInt& r, const BigInt& h);

private:
    BigInt _p; // Prime modulus
    BigInt _g; // Generator
    BigInt _y; // Public key
};

ElGamalVerifier::ElGamalVerifier(const BigInt& p, const BigInt& g, const BigInt& y)
    : _p(p), _g(g), _y(y) {}

bool ElGamalVerifier::verify(const BigInt& m, const BigInt& r, const BigInt& h) {
    // Calculate v1 = g^h mod p
    BigInt v1 = BigInt::modularPower(_g, h, _p);

    // Calculate v2 = (y^r * r^h) mod p
    BigInt v2 = (BigInt::modularPower(_y, r, _p) * BigInt::modularPower(r, h, _p)) % _p;

    // Check if v1 is equal to v2
    return v1 == v2;
}



int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    // Read input data from file
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    BigInt p, g, x, c1, c2;
    input_file >> p >> g >> x >> c1 >> c2;
    input_file.close();

    // Perform ElGamal decryption
    ElGamal elgamal(p, g, x);
    BigInt h = elgamal.decrypt({ c1, c2 });
    BigInt m = (c1 * BigInt::inverseModulo(h, p)) % p;

    // Write output data to file
    std::ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    output_file << h << '\n' << m << '\n';
    output_file.close();

    return 0;
}
