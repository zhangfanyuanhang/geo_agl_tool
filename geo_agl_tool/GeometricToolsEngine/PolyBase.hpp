#pragma once

#ifndef GTE_POLYBASE_HPP
#define GTE_POLYBASE_HPP

#include <list>
#include <vector>
#include <deque>
#include <typeinfo.h>

///! 虚基类
///! 获得运行时类型信息
namespace gte {
	class PolyBase
	{
	public:
		PolyBase() = default;
		~PolyBase() = default;

		virtual const std::type_info& getType()=0;
	};
}



#endif // !GTE_POLYBASE_HPP

