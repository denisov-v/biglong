#include <bitset>
#include <algorithm>
#include "biglong.h"

namespace blong
{
	// performs right bit shift and returns offcast tail as fraction
	double biglong::bit_rshift_frac_part(UNSIGINT shift) const
	{
		std::string bin_str;
		UNSIGINT b = 0;
		for (size_t i = 0; b < shift; ++i, b += BASE_POWER)
			if (i < value.size())
			{
				bin_str = std::bitset<BASE_POWER>(static_cast<unsigned long long>(value[i]))
					.to_string() + bin_str;
			}
			else
			{
				bin_str = std::bitset<BASE_POWER>(0ULL).to_string() + bin_str;
			}
		bin_str = bin_str.substr(b - shift);

		double frac_part = 0;
		unsigned int d = 2;
		for (size_t i = 0; i < std::min(bin_str.length(), sizeof(unsigned int) * 8 - 1); ++i, d <<= 1)
			if (bin_str[i] == '1')
				frac_part += 1 / static_cast<double>(d);		
		
		return frac_part;
	}
}