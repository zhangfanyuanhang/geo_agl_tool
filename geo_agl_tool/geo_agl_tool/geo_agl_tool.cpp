// geo_agl_tool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <array>

#include <boost/polygon/voronoi.hpp>

#include "MedialAxis/boost_polygon.h"
#include "MedialAxis/MedialAxisTransform.h"
#include "easyx_show.hpp"

#include "Point.h"
#include "Polygons2.h"

#include "trimesh.h"

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;


int main()
{
	/*std::vector<Point2d> points;
	points.push_back(Point2d(0, 0));
	points.push_back(Point2d(1, 6));
	
	std::vector<Segment2d> segments;
	segments.push_back(Segment2d(Point2d(-4, 5), Point2d(5, -1)));
	segments.push_back(Segment2d(Point2d(3, -11), Point2d(13, -1)));

	voronoi_diagram<double> vd;
	construct_voronoi(points.begin(), points.end(), &vd);
	construct_voronoi(segments.begin(), segments.end(), &vd);
	construct_voronoi(points.begin(), points.end(), segments.begin(), segments.end(), &vd);*/

	//std::vector<Polygons2d> section_polygons;


	{
		gte::Polygons2d plys;
		gte::Point3d pt({0,0,100});
		gte::Vector3d dir({ 0,0,1 });
		std::string stl_path = "D:\\Models\\zigzag\\a.stl";

		TriMesh trimesh;
		trimesh.init();
		trimesh.loadMesh(stl_path);
		trimesh.slice(pt,dir,&plys);

		//MedialAxisTransform mat(plys);
		//voronoi_diagram<double> vd;
		//construct_voronoi(points.begin(), points.end(), &vd);
		//construct_voronoi(segments.begin(), segments.end(), &vd);
		//construct_voronoi(points.begin(), points.end(), segments.begin(), segments.end(), &vd);

		EasyXShow2D easyx_show;
		easyx_show.setWindows();
		easyx_show.polygons(plys);
		easyx_show.closeWindows();
		

	}

	return 0;
}

