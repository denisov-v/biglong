#ifndef BIGLONG
#define BIGLONG

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace blong
{
#if _M_X64
	typedef unsigned long long UNSIGINT;
	typedef long long SIGINT;
	typedef unsigned int SHORT_UNSIGINT;
	const UNSIGINT BASE = 4294967296ULL; // 2^32
	const UNSIGINT REM_MASK = 4294967295ULL;
	const UNSIGINT BASE_POWER = 32;
	const UNSIGINT HEX_DIGITS = 8;
#elif _M_IX86
	typedef unsigned int UNSIGINT;
	typedef int SIGINT;
	typedef unsigned short SHORT_UNSIGINT;
	const UNSIGINT BASE = 65536; // 2^16
	const UNSIGINT REM_MASK = 65535;
	const UNSIGINT BASE_POWER = 16;
	const UNSIGINT HEX_DIGITS = 4;
#endif

	class biglong
	{
		friend std::ostream& operator<<(std::ostream &stream, const biglong &n);
		friend std::istream& operator>>(std::istream &stream, biglong &n);

	public:
		static const biglong zero;
		static const biglong one;
		static const biglong two;

		biglong();
		explicit biglong(const std::string& hex_string);
		explicit biglong(UNSIGINT num);
		biglong(biglong&& source);
		biglong(const unsigned char* raw_bytes, const size_t length);

		biglong& operator=(const std::string& hex_string);
		biglong& operator=(UNSIGINT num);
		biglong& operator=(biglong&& source);

		bool operator==(const biglong& rhs) const;
		bool operator!=(const biglong& rhs) const;
		bool operator<(const biglong& rhs) const;
		bool operator<=(const biglong& rhs) const;
		bool operator>(const biglong& rhs) const;
		bool operator>=(const biglong& rhs) const;

		biglong& operator++();
		biglong& operator+=(const biglong& rhs);

		biglong operator+(const biglong& rhs) const;
		biglong operator+(UNSIGINT rhs) const;		
		biglong operator*(const biglong& rhs) const;
		biglong operator*(SHORT_UNSIGINT rhs) const;
		biglong operator*(UNSIGINT rhs) const;

		biglong div(const biglong& rhs, biglong& quot) const;
		biglong trunc_sub(const biglong& rhs) const;
		biglong power_mod(const biglong& power, const biglong& modulo) const;

		double bit_rshift_frac_part(UNSIGINT shift) const;

		static biglong get_random(const biglong& max);
		static biglong gcd(const biglong& a, const biglong& b);

		std::string to_string() const;
		size_t get_raw_bytes(unsigned char*& raw_bytes) const;
		size_t get_raw_bytes(unsigned char*& raw_bytes, const size_t min_length) const;
		bool isOdd() const;

	private:
		biglong(size_t reserved_size, SHORT_UNSIGINT default_value);

		void normalize();
		void remove_leading_zeros();
		void from_string(const std::string& hex_string);		
	
		std::vector<UNSIGINT> value;
	};
}
#endif