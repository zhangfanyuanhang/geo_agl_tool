
#include "trimesh.h"
#include <iostream>

TriMesh::TriMesh()
{
	Py_Initialize();
}

TriMesh::~TriMesh()
{
	Py_Finalize();
}
int TriMesh::init()
{
	if (!Py_IsInitialized()) {
		std::cout << "python init fail" << std::endl;
		return 1;
	}
	import_array(); //numpy
	mpTriMeshModule = PyImport_ImportModule("trimesh");
	if (nullptr == mpTriMeshModule) {
		std::cout << "trimesh module not found" << std::endl;
		return 1;
	}
	mpShapelyModule = PyImport_ImportModule("shapely");
	if (nullptr == mpShapelyModule) {
		std::cout << "shapely module not found" << std::endl;
		return 1;
	}
	return 0;
}
int TriMesh::loadMesh(const std::string& file)
{
	PyObject* load_mesh = PyObject_GetAttrString(mpTriMeshModule, "load_mesh");
	PyObject * buildObject = Py_BuildValue("s", file.c_str(), file.length());
	PyObject * pStlPath = PyTuple_New(1);
	PyTuple_SetItem(pStlPath, 0, buildObject);
	mpTriMesh = PyObject_CallObject(load_mesh, pStlPath);
	if (nullptr == mpTriMesh) {
		std::cout << "not found trimesh" << std::endl;
		return 1;
	}

	return 0;
}
int TriMesh::slice(const gte::Point3d& point, const gte::Vector3d& direction,gte::Polygons2d* plys)
{

	//PyObject* pbounds = PyObject_CallObject(PyObject_GetAttrString(mpTriMesh, "bounds"), NULL);
	//PyObject* pmin = PySequence_GetItem(pbounds,0);
	//PyObject* pmax = PySequence_GetItem(pbounds, 1);

	//! slice plane
	PyObject* pCentroid = PyObject_GetAttrString(mpTriMesh, "centroid");
	double pt[] = { point.x(),point.y(),point.z()};
	float dir[] = { direction.x(),direction.y(),direction.z() };
	npy_intp dims[] = { 3 };
	PyObject* ppt = PyArray_SimpleNewFromData(1, dims, NPY_FLOAT, pt);
	PyObject* pdir = PyArray_SimpleNewFromData(1, dims, NPY_FLOAT, dir);
	PyObject * pSliceParam = PyTuple_New(2);
	PyTuple_SetItem(pSliceParam, 0, pCentroid);
	PyTuple_SetItem(pSliceParam, 1, pdir);

	//! slice mesh
	PyObject* pSection = PyObject_GetAttrString(mpTriMesh, "section");
	PyObject* mpSlice = PyObject_CallObject(pSection, pSliceParam);
	if (nullptr == mpSlice)
	{
		std::cout << "not found trimesh section" << std::endl;
		return 1;
	}
	//! to planar path
	PyObject* pToPlanar = PyObject_GetAttrString(mpSlice, "to_planar");
	PyObject* pToPlanarObject = PyObject_CallObject(pToPlanar, NULL);
	PyObject* pPath2D = PyTuple_GetItem(pToPlanarObject, 0);

	//Polygons2d polygons;
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

		gte::Polygon2d polygon;
		for (size_t i = 0; i < pt_size; i++)
		{
			float px = (float)PyFloat_AsDouble(PySequence_GetItem(pX, i));
			float py = (float)PyFloat_AsDouble(PySequence_GetItem(pY, i));
			polygon.push_back(gte::Point2d{ px,py });
		}
		plys->push_back(polygon);
	}
	{
		PyObject* pPolygons = PyObject_GetAttrString(pPath2D, "polygons_full");
		PyObject* pPlys = PySequence_GetItem(pPolygons, 0);

		PyObject* pInteriors = PyObject_GetAttrString(pPlys, "interiors");
		Py_ssize_t ply_size = PySequence_Size(pInteriors);
		for (size_t i = 0; i < ply_size; i++)
		{
			PyObject* pPly = PySequence_GetItem(pInteriors, i);

			PyObject* pCoords = PyObject_GetAttrString(pPly, "coords");
			PyObject* pXY = PyObject_GetAttrString(pCoords, "xy");
			Py_ssize_t pt_size = PySequence_Size(pCoords);
			PyObject* pX = PyTuple_GetItem(pXY, 0);
			PyObject* pY = PyTuple_GetItem(pXY, 1);
			gte::Polygon2d polygon;
			for (size_t i = 0; i < pt_size; i++)
			{
				float px = (float)PyFloat_AsDouble(PySequence_GetItem(pX, i));
				float py = (float)PyFloat_AsDouble(PySequence_GetItem(pY, i));
				std::cout << px << " " << py << std::endl;
				polygon.push_back(gte::Point2d{px,py});
			}
			plys->push_back(polygon);
		}
	}
	return 0;
}
void TriMesh::showSlice()const
{
	PyObject_CallObject(PyObject_GetAttrString(mpSlice, "show"), NULL);
}