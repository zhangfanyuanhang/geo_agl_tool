#pragma once

#ifndef TRI_MESH_H
#define TRI_MESH_H

#include <string>
#include <Python.h>
#include <numpy/arrayobject.h>

#include "Point.hpp"
#include "Vector3.hpp"
#include "Polygon2.hpp"
#include "Polygons2.hpp"

class TriMesh
{
public:
	TriMesh();
	~TriMesh();

	int init();
	int loadMesh(const std::string& file);
	int slice(const gte::Point3d& point,const gte::Vector3d& direction,gte::Polygons2d* plys);
	void showSlice()const;
private:
	
private:
	PyObject* mpTriMeshModule = nullptr;
	PyObject* mpShapelyModule = nullptr;

	PyObject* mpTriMesh = nullptr;
	PyObject* mpSlice = nullptr;
};


#endif // !TRI_MESH_H


