#pragma once

#ifndef GTE_SEQUENCER_H
#define GTE_SEQUENCER_H


#include "Base.h"

//! 序列容器类 deque
//! 随机访问
//! 插入和删除
namespace gte {
	template <typename T>
	class Sequencer: public Base
	{
	public:
		typedef T data_type;
		typedef typename std::deque<data_type>::const_iterator const_iterator;
		typedef typename std::deque<data_type>::iterator iterator;
	
		~Sequencer() = default;
	//! 不支持单独构造
	protected:
		Sequencer() = default;
		Sequencer(const std::list<data_type>& pts) :Base(), mData(pts.begin(), pts.end()) {}
		Sequencer(const std::vector<data_type>& pts) :Base(),mData(pts.begin(), pts.end()){}
		Sequencer(std::initializer_list<data_type>& pts) :Base(), mData(pts) {}
		template <typename Iter>
		Sequencer(const Iter begin, const Iter end) : Base(), mData(begin, end) {}
		Sequencer(const Sequencer&) = default;
	//! 重载实现
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	
	//! 
	public:
		//virtual inline ORDER order();
		//virtual inline bool closure();
	//! 基本操作
	public:
		
		inline void push_front(data_type pt) { mData.push_front(pt); }
		inline void push_back(data_type pt) { mData.push_back(pt); }
		inline size_t size()const { return mData.size(); }
		inline void resize(size_t size) { mData.resize(size); };

		inline const data_type& operator[](size_t i)const { return mData[i]; }
		inline data_type& operator[](size_t i) { return mData[i]; }

		inline const_iterator begin() const { return mData.begin(); }
		inline const_iterator end() const { return mData.end(); }
		inline iterator begin() { return mData.begin(); }
		inline iterator end() { return mData.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mData.insert(pos, first, last); }

		inline void clear() { mData.clear(); }


	
	protected:
		std::deque<data_type> mData; 
	};

}

#endif // !GTE_POLYGON2_HPP

