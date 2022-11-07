#pragma once

#ifndef GTE_BASE_H
#define GTE_BASE_H

#include <list>
#include <vector>
#include <deque>
#include <typeinfo.h>

//! 虚基类
//! 获得运行时类型信息
namespace gte {
	class Base
	{
	public:
		Base() = default;
		~Base() = default;

		virtual const std::type_info& getType()=0;
	};
}



#endif // !GTE_BASE_H

