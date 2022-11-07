// geo_agl_tool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <array>

#include "MedialAxis/boost_polygon.h"
#include "MedialAxis/MedialAxisTransform.h"

//#include "easyx_show.h"
#include "Graphic2.h"

#include "Point.h"
#include "Polygons2.h"
#include "Convertor.h"
#include "Segment2.h"
#include "Segment.h"
#include "trimesh.h"




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

		
		gte::Polygons2i umPlys;
		gte::polygonsConvertorMM2UM(plys,umPlys);
		gte::BoundingBox<gte::Point2i> aabb;
		umPlys.AABB(aabb);
		//std::vector<gte::Point2i>  mat_pts;
		//MedialAxisTransform mat(umPlys);
		//mat.ConstructVoronoi(mat_pts);


		//EasyXShow2D easyx_show;
		//easyx_show.setWindows();
		//easyx_show.polygons(umPlys);
		//easyx_show.polylines(mat_pts);
		//easyx_show.show();
		//easyx_show.polygons(plys);
		//easyx_show.closeWindows();
		
		gui::Graphic2 graphic2;
		graphic2.initWindow(1000,1000);
		graphic2.show(&umPlys);
		graphic2.closeWindow();

	}

	return 0;
}

