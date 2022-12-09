#pragma once

#ifndef GTE_MULTIPNTSGM_HPP
#define GTE_MULTIPNTSGM_HPP

#include "MathDefines.h"
#include "Sequencer.hpp"
#include "Point.hpp"
#include "Segment2.hpp"

///! ��ṹ���ݣ�ʹ�ô�������������������ݽṹ
///! ������������������һ�¡�
namespace gte {
	
	using MultiPoints2i = Sequencer<Point2i>;
	using MultiPoints2d = Sequencer<Point2d>;
	using MultiSegments2i = Sequencer<Segment2i>;
	using MultiSegments2d = Sequencer<Segment2d>;

}

#endif //GTE_MULTIPNTSGM_HPP
