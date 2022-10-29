#pragma once

#ifndef GTE_CONVERTOR_H
#define GTE_CONVERTOR_H

namespace gte {
	#define MM2UM(x) (static_cast<long>(x*1000.0))
	#define UM2MM(x) (static_cast<double>((x*0.001))

	/*template<typename InputIt, typename OutputIt>
	void convertorLong2Double(InputIt first, InputIt last, OutputIt d_first)
	{
		;
	}
	template<typename InputIt, typename OutputIt>
	void convertorDouble2Long(InputIt first, InputIt last, OutputIt d_first)
	{
		;
	}*/
}


#endif // !GTE_CONVERTOR_H

