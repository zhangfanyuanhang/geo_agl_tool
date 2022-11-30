// geo_agl_tool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <array>

#include "MedialAxis/MedialAxisTransform.h"

#include "Graphic2.h"

#include "GeometricToolsEngine.h"
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
		//std::string stl_path = "E:\\Models\\zigzag\\a.stl";
		std::string stl_path = "E:\\Models\\DType\\D.STL";
		TriMesh trimesh;
		trimesh.init();
		trimesh.loadMesh(stl_path);
		trimesh.slice(pt,dir,&plys);

		
		gte::Polygons2i umPlys;
		gte::polygonsConvertorMM2UM(plys,umPlys);
		gte::BoundingBox<gte::Point2i> aabb;
		umPlys.AABB(aabb);
		MedialAxisTransform mat(umPlys);
		mat.ConstructVoronoi();
		mat.show();

		
		/*gui::Graphic2 graphic2;
		graphic2.initWindow(1000,1000);
		graphic2.show(&umPlys);
		graphic2.closeWindow();*/

	}

	return 0;
}

