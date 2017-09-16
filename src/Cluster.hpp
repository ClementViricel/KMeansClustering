#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "Point.hpp"
using namespace std;
class Cluster
{
private:
	unsigned int ID; // Cluster ID
	vector<double> central_values; // representative associated with the cluster.
	vector<Point> points; // Points in the cluster

public:
	Cluster(unsigned int m_ID, Point m_point) // Construct the cluster with at least one point in it
	{
		this->ID = m_ID;

		unsigned int number_of_values = m_point.getNumberOfValues();

		for(unsigned int d = 0; d < number_of_values; d++)
    {
			this->central_values.push_back(m_point.getValue(d));
    }

		this->points.push_back(m_point);
	}

	void addPoint(Point m_point) // Add point to the Cluster
	{
		this->points.push_back(m_point);
	}

	bool removePoint(int m_point_ID) // Remove Point to the Cluster (maybe better way to do this, but it's working ! )
	{
		unsigned int number_of_points = this->points.size();

		for(unsigned int p = 0; p < number_of_points; p++)
		{
			if(this->points[p].getID() == m_point_ID) // if the IDs correspond then remove
			{
				this->points.erase(this->points.begin() + p);
				return true;
			}
		}
		return false; // return false if the ID is not in the cluster (can be used to check or debug)
	}

	double getCentralValue(unsigned int index) 
	{
		return central_values[index];
	}

	void setCentralValue(unsigned int index, double value) 
	{
		central_values[index] = value;
	}

	Point getPoint(int index) // get point from the cluster
	{
		return this->points[index];
	}

	unsigned int getNumberOfPoints()
	{
		return this->points.size();
	}

	unsigned int getID()
	{
		return this->ID;
	}
};

