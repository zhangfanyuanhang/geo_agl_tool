#pragma once

#ifndef GTE_SEQUENCER_HPP
#define GTE_SEQUENCER_HPP


#include "PolyBase.hpp"

//! ���������� deque
//! �������
//! �����ɾ��
namespace gte {
	template <typename T>
	class Sequencer: public PolyBase
	{
	public:
		typedef T data_type;
		typedef typename std::deque<data_type>::const_iterator const_iterator;
		typedef typename std::deque<data_type>::iterator iterator;
	
		~Sequencer() = default;

		Sequencer() = default;
		Sequencer(const std::list<data_type>& pts) :PolyBase(), mData(pts.begin(), pts.end()) {}
		Sequencer(const std::vector<data_type>& pts) :PolyBase(),mData(pts.begin(), pts.end()){}
		Sequencer(std::initializer_list<data_type>& pts) :PolyBase(), mData(pts) {}
		template <typename Iter>
		Sequencer(const Iter begin, const Iter end) : PolyBase(), mData(begin, end) {}
		Sequencer(const Sequencer&) = default;
	//! ����ʵ��
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	
	//! 
	public:
		//virtual inline ORDER order();
		//virtual inline bool closure();
	//! ��������
	public:
		
		inline void push_front(data_type pt) { mData.push_front(pt); }
		inline void push_back(data_type pt) { mData.push_back(pt); }
		inline size_t size()const { return mData.size(); }
		inline void resize(size_t size) { mData.resize(size); };
		inline data_type& back() { return mData.back(); }
		inline const data_type& back()const { return mData.back(); }
		inline data_type& front() { return mData.front(); }
		inline const data_type& front()const { return mData.front(); }
		inline bool empty() { return mData.empty(); }

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

