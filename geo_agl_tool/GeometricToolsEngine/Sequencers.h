#pragma once

#ifndef GTE_SEQUENCERSS_H
#define GTE_SEQUENCERSS_H


#include "Base.h"

namespace gte {

	template <typename SequencerType>
	class Sequencers: public Base
	{
	public:
		typedef typename SequencerType::point_type point_type;
		typedef SequencerType sequencer_type;
		typedef typename std::vector<sequencer_type>::const_iterator const_iterator;
		typedef typename std::vector<sequencer_type>::iterator iterator;
	protected:
		Sequencers() = default;
		Sequencers(const std::vector<sequencer_type>& pts) :Base(),mSequencers(pts) {}
		Sequencers(std::initializer_list<sequencer_type>& pts) :Base() {
			if (size_t size = pts.size())
			{
				std::copy(pts, pts + size, mSequencers.begin());
			}
		}
	public:
		
		~Sequencers() = default;
	
		inline void add(sequencer_type ply) { mSequencers.push_back(ply); }
		inline size_t size()const { return mSequencers.size(); }
		inline void resize(size_t size) { mSequencers.resize(size); }

		inline const sequencer_type& operator[](size_t i)const { return mSequencers[i]; }
		inline sequencer_type& operator[](size_t i) { return mSequencers[i]; }

		inline const_iterator begin() const { return mSequencers.begin(); }
		inline const_iterator end() const { return mSequencers.end(); }

		inline iterator begin() { return mSequencers.begin(); }
		inline iterator end() { return mSequencers.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mSequencers.insert(pos, first, last); }

		inline void clear() { mSequencers.clear(); }

		
	protected:
		std::vector<sequencer_type> mSequencers;
	};
}

#endif // !GTE_POLYGON2_HPP

