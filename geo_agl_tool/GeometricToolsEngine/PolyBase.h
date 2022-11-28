#pragma once

#ifndef GTE_PolyBase_H
#define GTE_PolyBase_H

#include <list>
#include <vector>
#include <deque>
#include <typeinfo.h>

//! �����
//! �������ʱ������Ϣ
namespace gte {
	class PolyBase
	{
	public:
		PolyBase() = default;
		~PolyBase() = default;

		virtual const std::type_info& getType()=0;
	};
}



#endif // !GTE_PolyBase_H

