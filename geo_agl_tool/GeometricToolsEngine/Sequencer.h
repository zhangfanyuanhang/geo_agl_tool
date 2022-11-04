#pragma once

#ifndef GTE_SEQUENCER_H
#define GTE_SEQUENCER_H


#include "Base.h"

namespace gte {
	template <typename PointType>
	class Sequencer: public Base
	{
	public:
		typedef PointType point_type;
		typedef typename std::vector<point_type>::const_iterator const_iterator;
		typedef typename std::vector<point_type>::iterator iterator;

	protected:
		
		Sequencer() = default;
		Sequencer(const std::vector<point_type>& pts) :Base(),mSequencer(pts) {}
		Sequencer(std::initializer_list<point_type>& pts) :Base() {
			if (size_t size = pts.size())
			{
				std::copy(pts, pts + size, mSequencer.begin());
			}
		}

	public:
		~Sequencer() = default;
		inline void add(point_type pt) { mSequencer.push_back(pt); }
		inline size_t size()const { return mSequencer.size(); }
		inline void resize(size_t size) { mSequencer.resize(size); };

		inline const point_type& operator[](size_t i)const { return mSequencer[i]; }
		inline point_type& operator[](size_t i) { return mSequencer[i]; }

		inline const_iterator begin() const { return mSequencer.begin(); }
		inline const_iterator end() const { return mSequencer.end(); }

		inline iterator begin() { return mSequencer.begin(); }
		inline iterator end() { return mSequencer.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mSequencer.insert(pos, first, last); }

		inline void clear() { mSequencer.clear(); }



	protected:
		std::vector<point_type>mSequencer;
	};

}

#endif // !GTE_POLYGON2_HPP

