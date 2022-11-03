#pragma once

#ifndef MAT_MEDIAL_AXIS_TRANSFORM_H
#define MAT_MEDIAL_AXIS_TRANSFORM_H

#include "Point.h"
#include "Polygons2.h"
#include "Segment2.h"
#include "boost_polygon.h"
#include "boost/polygon/voronoi.hpp"

//using boost::polygon::voronoi_builder;
//using boost::polygon::voronoi_diagram;
namespace boost {
	namespace polygon {
		namespace detail {
			template <typename T>
			struct my_voronoi_ctype_traits;

			template <>
			struct my_voronoi_ctype_traits<int64_t> {
				typedef int64_t int_type;
				typedef int64_t int_x2_type;
				typedef uint64_t uint_x2_type;
				typedef extended_int<128> big_int_type;
				typedef double_t fpt_type;
				typedef extended_exponent_fpt<fpt_type> efpt_type;
				typedef ulp_comparison<fpt_type> ulp_cmp_type;
				typedef type_converter_fpt to_fpt_converter_type;
				typedef type_converter_efpt to_efpt_converter_type;
			};
		}
	}
}
class MedialAxisTransform
{
	using voronoi_diagram = boost::polygon::voronoi_diagram<double_t>;
public:
	MedialAxisTransform(const gte::Polygons2i& plys);
	~MedialAxisTransform();

	void ConstructVoronoi(std::vector<gte::Point2i>& pts);
private:
	voronoi_diagram mVoronoiDiagram;
private:
	gte::Polygons2i mPolygons;
	std::vector<gte::Point2i> mMATPoints;
};


#endif // !MAT_MEDIAL_AXIS_TRANSFORM_H

