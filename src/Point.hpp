#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Point
{
private:
	unsigned int point_ID; // Point ID (if there is redundant point and you want to take them in account)
  unsigned int cluster_ID; // Cluster ID where the point is 
	vector<double> values; // values constituing the point
	unsigned int number_of_values; // number of total values in the point (Warning, each point must have the same length)
	string name; // name of the point if the name is provided

public:
	Point(unsigned int m_id_point, vector<double>& m_values, string m_name = "")
	{
		this->point_ID = m_id_point;
		this->number_of_values = m_values.size();
    //cout<<"Creating Point "<<this->point_ID<<endl;
		for(unsigned int i = 0; i < this->number_of_values; i++)
    {
			this->values.push_back(m_values[i]);
    }
		this->name = m_name;
		cluster_ID = 0; // Initialized to 0
	}

	int getID()
	{
		return this->point_ID;
	}

	void setCluster(unsigned int m_cluster_ID)
	{
		this->cluster_ID = m_cluster_ID;
	}

	int getCluster()
	{
		return this->cluster_ID;
	}

	double getValue(unsigned int index)
	{
		return this->values[index];
	}

	int getNumberOfValues()
	{
		return this->number_of_values;
	}

	void addValue(double value)
	{
		this->values.push_back(value);
	}

	string getName()
	{
		return this->name;
	}
};
