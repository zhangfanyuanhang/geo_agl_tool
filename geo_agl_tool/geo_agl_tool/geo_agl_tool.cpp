// geo_agl_tool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <array>
#include <geometric_primitive.h>
#include <medial_axis.h>
#include <boost/polygon/voronoi.hpp>

#include <graphics.h>		// 引用 EasyX 绘图库头文件
#include <conio.h>

#include <Python.h>
#include <numpy/arrayobject.h>

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;

#define MM2UM(x) (static_cast<long>(x*1000.0))
#define UM2MM(x) (static_cast<double>((x*0.001))

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

	std::vector<Polygons2d> section_polygons;

	std::string stl_path = "D:\\Models\\zigzag\\a.stl";

	//!python init
	Py_Initialize();
	if (!Py_IsInitialized()) {
		std::cout << "python init fail" << std::endl;
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	//!numpy init
	import_array();
	//!
	PyObject* pShapely = PyImport_ImportModule("shapely");

	//!import trimesh modul
	PyObject* pTriMesh = PyImport_ImportModule("trimesh");
	if (pTriMesh == NULL) {
		std::cout << "module not found" << std::endl;
	}

	//!load mesh
	PyObject* pLoadMesh = PyObject_GetAttrString(pTriMesh, "load_mesh");
	if (!pLoadMesh || !PyCallable_Check(pLoadMesh)) {
		std::cout << "not found function load_mesh" << std::endl;
	}
	PyObject * buildObject = Py_BuildValue("s", stl_path.c_str(), stl_path.length());
	PyObject * pStlPath = PyTuple_New(1);
	PyTuple_SetItem(pStlPath, 0, buildObject);
	PyObject* pMesh = PyObject_CallObject(pLoadMesh, pStlPath);
	if (!pMesh || !PyCallable_Check(pMesh)) {
		std::cout << "not found function show" << std::endl;
	}

	//! slice plane
	float dir[] = {0.,0.,1.0};
	npy_intp dims[] = {3};
	PyObject* pDir = PyArray_SimpleNewFromData(1, dims, NPY_FLOAT, dir);
	PyObject* pCentroid = PyObject_GetAttrString(pMesh, "centroid");
	PyObject * pSliceParam = PyTuple_New(2);
	PyTuple_SetItem(pSliceParam, 0, pCentroid);
	PyTuple_SetItem(pSliceParam, 1, pDir);

	//! slice mesh
	PyObject* pSection = PyObject_GetAttrString(pMesh, "section");
	PyObject* pSlice = PyObject_CallObject(pSection, pSliceParam);

	//! show slice
	/*PyObject* pSliceShow = PyObject_GetAttrString(pSlice, "show");
	if (!pSliceShow || !PyCallable_Check(pSliceShow)) {
		std::cout << "not found function show" << std::endl;
	}
	PyObject_CallObject(pSliceShow, NULL);*/

	//! to planar path
	PyObject * pToPlanarObject = PyObject_CallMethod(pSlice,"to_planar",NULL);
	PyObject* pPath2D = PyTuple_GetItem(pToPlanarObject, 0);
	
	Polygons2d polygons;
	//! points
	{
		//! polygons
		PyObject* pPolygons = PyObject_GetAttrString(pPath2D, "polygons_closed");
		PyObject* pPly = PySequence_GetItem(pPolygons, 0);

		PyObject* pExterior = PyObject_GetAttrString(pPly, "exterior");
		PyObject* pCoords = PyObject_GetAttrString(pExterior, "coords");
		PyObject* pXY = PyObject_GetAttrString(pCoords, "xy");
		Py_ssize_t pt_size = PySequence_Size(pCoords);
		PyObject* pX = PyTuple_GetItem(pXY, 0);
		PyObject* pY = PyTuple_GetItem(pXY, 1);

		Polygon2d polygon;
		for (size_t i = 0; i < pt_size; i++)
		{
			float px = (float)PyFloat_AsDouble(PySequence_GetItem(pX, i));
			float py = (float)PyFloat_AsDouble(PySequence_GetItem(pY, i));
			//std::cout << px << " " << py << std::endl;
			polygon.polygon.push_back(Point2d{MM2UM(px),MM2UM(py)});
		}
		polygons.polygons.push_back(polygon);
	}
	{
		PyObject* pPolygons = PyObject_GetAttrString(pPath2D, " polygons_full");
		PyObject* pPlys = PySequence_GetItem(pPolygons, 0);

		PyObject* pInteriors = PyObject_GetAttrString(pPlys, "interiors");
		Py_ssize_t ply_size = PySequence_Size(pInteriors);
		for (size_t i = 0; i < ply_size; i++)
		{
			PyObject* pPly = PySequence_GetItem(pInteriors,i);

			PyObject* pCoords = PyObject_GetAttrString(pPly, "coords");
			PyObject* pXY = PyObject_GetAttrString(pCoords, "xy");
			Py_ssize_t pt_size = PySequence_Size(pCoords);
			PyObject* pX = PyTuple_GetItem(pXY, 0);
			PyObject* pY = PyTuple_GetItem(pXY, 1);
			Polygon2d polygon;
			for (size_t i = 0; i < pt_size; i++)
			{
				float px = (float)PyFloat_AsDouble(PySequence_GetItem(pX, i));
				float py = (float)PyFloat_AsDouble(PySequence_GetItem(pY, i));
				std::cout << px << " " << py << std::endl;
				polygon.polygon.push_back(Point2d{ MM2UM(px),MM2UM(py) });
			}
			polygons.polygons.push_back(polygon);
		}
		
	}
	
	Py_Finalize();

	{
		initgraph(1000, 800);	// 创建绘图窗口，大小为 640x480 像素
		setorigin(500, 400);

		
		std::array<POINT*, 2> plys;

		int ply_size = polygons.polygons.size();
		for (size_t i = 0; i < ply_size; i++)
		{
			//polygon(points, pt_size);
		}


		//polygon(points, pt_size);	// 画圆，圆心(200, 200)，半径 100
		_getch();				// 按任意键继续
		closegraph();			// 关闭绘图窗口

	}
	
	return 0;
}

