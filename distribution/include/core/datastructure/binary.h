#ifndef TRILLBPP_BINARY_H_
#define TRILLBPP_BINARY_H_


#include <core/datastructure/vecWrapper.h>

class bin
{
public:
  //! Default constructor
  bin(): b(0) {}

  //! Set the binary object equal to \c value. Either "0" or "1".
  bin(const int &value): b(static_cast<char>(value)) {
    it_assert_debug((value == 0) || (value == 1),
                    "bin::bin(): value must be 0 or 1");
  }

  //! Copy constructor
  bin(const bin &inbin): b(inbin.b) {}

  //! Assign a value
  void operator=(const int &value) {
    it_assert_debug((value == 0) || (value == 1),
                    "bin::operator=(): value must be 0 or 1");
    b = static_cast<char>(value);
  }

  //! Assign a value
  void operator=(const bin &inbin) { b = inbin.b; }

  //! OR
  void operator/=(const bin &inbin) { b |= inbin.b; }

  //! OR
  void operator|=(const bin &inbin) { b |= inbin.b; }
  //! OR
  bin operator/(const bin &inbin) const { return bin(b | inbin.b); }
  //! OR
  bin operator|(const bin &inbin) const { return bin(b | inbin.b); }

  //! XOR
  void operator+=(const bin &inbin) { b ^= inbin.b; }
  //! XOR
  void operator^=(const bin &inbin) { b ^= inbin.b; }
  //! XOR
  bin operator+(const bin &inbin) const { return bin(b ^ inbin.b); }
  //! XOR
  bin operator^(const bin &inbin) const { return bin(b ^ inbin.b); }
  //! XOR
  void operator-=(const bin &inbin) { b ^= inbin.b; }
  //! XOR
  bin operator-(const bin &inbin) const { return bin(b ^ inbin.b); }
  //! Dummy definition to be able to use vec<bin>
  bin operator-() const { return bin(b); }

  //! AND
  void operator*=(const bin &inbin) { b &= inbin.b; }
  //! AND
  void operator&=(const bin &inbin) { b &= inbin.b; }
  //! AND
  bin operator*(const bin &inbin) const { return bin(b & inbin.b); }
  //! AND
  bin operator&(const bin &inbin) const { return bin(b & inbin.b); }

  //! NOT
  bin operator!(void) const { return bin(b ^ 1); }
  //! NOT
  bin operator~(void) const { return bin(b ^ 1); }

  //! Check if equal
  bool operator==(const bin &inbin) const { return b == inbin.b; }
  //! Check if equal
  bool operator==(const int &i) const { return b == i; }

  //! Check if not equal
  bool operator!=(const bin &inbin) const { return b != inbin.b; }
  //! Check if not equal
  bool operator!=(const int &i) const { return b != i; }

  //! Less than (interpret the binary values {0,1} as integers)
  bool operator<(const bin &inbin) const  { return b < inbin.b; }
  //! Less than equal (interpret the binary values {0,1} as integers)
  bool operator<=(const bin &inbin) const { return b <= inbin.b; }

  //! Greater than (interpret the binary values {0,1} as integers)
  bool operator>(const bin &inbin) const  { return b > inbin.b; }
  //! Greater than equal (interpret the binary values {0,1} as integers)
  bool operator>=(const bin &inbin) const { return b >= inbin.b; }

  //! Convert \c bin to \c short
  operator short() const  { return static_cast<short>(b); }
  //! Convert \c bin to \c int
  operator int() const    { return static_cast<int>(b); }
  //! Convert \c bin to \c bool
  operator bool() const   { return b != 0; }
  //! Convert \c bin to \c float
  operator float() const  { return static_cast<float>(b); }
  //! Convert \c bin to \c double
  operator double() const { return static_cast<double>(b); }

  //! Output the binary value of the object
  char value() const { return b; }

private:
  char b;
};

/*!
  \relatesalso bin
  \brief Output stream of bin
*/
ITPP_EXPORT std::ostream &operator<<(std::ostream &output, const bin &inbin);

/*!
  \relatesalso bin
  \brief Input stream of bin
*/
ITPP_EXPORT std::istream &operator>>(std::istream &input, bin &outbin);

/*!
  \relatesalso bin
  \brief absolute value of bin
*/
inline bin abs(const bin &inbin) { return inbin; }

/*!
  \relatesalso itpp::bin
  \brief absolute value of bin
*/
// inline int abs(const bin &inbin) { return inbin; }


#endif // #ifndef BINARY_H
