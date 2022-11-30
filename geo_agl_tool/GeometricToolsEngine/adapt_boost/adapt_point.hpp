#pragma once

#ifndef GTE_ADAPT_POINT_HPP
#define GTE_ADAPT_POINT_HPP

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Point.hpp"

/// --------------------------------------------------------
// Adapt gte::Point2i to Boost.Geometry
namespace boost
{
	namespace geometry
	{
		namespace traits
		{
			template<> struct tag<gte::Point2i>
			{
				typedef point_tag type;
			};

			template<> struct coordinate_type<gte::Point2i>
			{
				typedef gte::Point2i::coord_type type;
			};

			template<> struct coordinate_system<gte::Point2i>
			{
				typedef cs::cartesian type;
			};

			template<> struct dimension<gte::Point2i> : boost::mpl::int_<2> {};

			template<>
			struct access<gte::Point2i, 0>
			{
				static gte::Point2i::coord_type get(gte::Point2i const& p)
				{
					return p.x();
				}

				static void set(gte::Point2i& p, gte::Point2i::coord_type const& value)
				{
					p.x() = value;
				}
			};

			template<>
			struct access<gte::Point2i, 1>
			{
				static gte::Point2i::coord_type get(gte::Point2i const& p)
				{
					return p.y();
				}

				static void set(gte::Point2i& p, gte::Point2i::coord_type const& value)
				{
					p.y() = value;
				}
			};
			//
			template<> struct tag<gte::Point2d>
			{
				typedef point_tag type;
			};

			template<> struct coordinate_type<gte::Point2d>
			{
				typedef gte::Point2d::coord_type type;
			};

			template<> struct coordinate_system<gte::Point2d>
			{
				typedef cs::cartesian type;
			};

			template<> struct dimension<gte::Point2d> : boost::mpl::int_<2> {};

			template<>
			struct access<gte::Point2d, 0>
			{
				static gte::Point2d::coord_type get(gte::Point2d const& p)
				{
					return p.x();
				}

				static void set(gte::Point2d& p, gte::Point2d::coord_type const& value)
				{
					p.x() = value;
				}
			};

			template<>
			struct access<gte::Point2d, 1>
			{
				static gte::Point2d::coord_type get(gte::Point2d const& p)
				{
					return p.y();
				}

				static void set(gte::Point2d& p, gte::Point2d::coord_type const& value)
				{
					p.y() = value;
				}
			};
		}
	}
}
/// -------------------------------------------------------
// Adapt gte::Point2i to Boost.Polygon
namespace boost {
	namespace polygon {
		template <>
		struct geometry_concept<gte::Point2i> { typedef point_concept type; };

		template <>
		struct point_traits<gte::Point2i> {
			typedef gte::Point2i::coord_type coordinate_type;

			static inline coordinate_type get(const gte::Point2i& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x() : point.y();
			}
		};
		template <>
		struct point_mutable_traits<gte::Point2i> {
			typedef gte::Point2i::coord_type coordinate_type;

			static inline void set(gte::Point2i& point, orientation_2d orient, int value) {
				if (orient == HORIZONTAL)
					point.x() = value;
				else
					point.y() = value;
			}
			static inline gte::Point2i construct(int x_value, int y_value) {
				return gte::Point2i(x_value, y_value);
			}
		};
		//
		template <>
		struct geometry_concept<gte::Point2d> { typedef point_concept type; };

		template <>
		struct point_traits<gte::Point2d> {
			typedef gte::Point2d::coord_type coordinate_type;

			static inline coordinate_type get(const gte::Point2d& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x() : point.y();
			}
		};
		template <>
		struct point_mutable_traits<gte::Point2d> {
			typedef gte::Point2d::coord_type coordinate_type;

			static inline void set(gte::Point2d& point, orientation_2d orient, int value) {
				if (orient == HORIZONTAL)
					point.x() = value;
				else
					point.y() = value;
			}
			static inline gte::Point2d construct(int x_value, int y_value) {
				return gte::Point2d(x_value, y_value);
			}
		};
	}
}

#endif // !GTE_ADAPT_POINT_HPP

