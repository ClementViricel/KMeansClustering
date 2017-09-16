#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "Cluster.hpp"

using namespace std;

class KMean
{
private:

  // This variables are parsed from the data file (look like .csp file).
  // This can be improved by automatically check if file is consistent but more time is needed for that
	unsigned int K; // number of clusters
	unsigned int number_of_values; // number of dimensions
  unsigned int number_of_points; // number of points
  unsigned int max_iterations; // number of iteration for Clustering
  char* filename;
	vector<Cluster> clusters; // Vector of clusters


public:
	KMean(int m_K, int m_number_of_points, int m_number_of_values, int m_max_iterations, char* m_filename) // COnstructor (from parsed info)
	{
		this->K = m_K;
		this->number_of_points = m_number_of_points;
		this->number_of_values = m_number_of_values;
		this->max_iterations = m_max_iterations;
    this->filename = m_filename;
	}
  
  unsigned int getIDNearestCenter(Point m_point); 	// return cluster ID of the nearest representative (central) value using L2 distance from m_point
  void writeOutput(ostream &ofs); // write the output
	void solve(vector<Point> & points); // Run the algorithm 
};

