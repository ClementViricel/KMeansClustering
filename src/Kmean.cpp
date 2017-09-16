#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "Kmean.hpp"

using namespace std;

	// return cluster ID of the nearest representative (central) value using L2 distance from m_point
unsigned int KMean::getIDNearestCenter(Point m_point)
{
		double sum = 0.0; 
    double min_dist;
		unsigned int closed_cluster_ID = 0;

    /* Initialize minimum distance with the first cluster  */
		for(unsigned int i = 0; i < this->number_of_values; i++)
		{
			sum += pow(this->clusters[0].getCentralValue(i) - m_point.getValue(i), 2.0); // sum of the values = \Sigma (a - b)^2 
		}

		min_dist = sqrt(sum);
    /*     End Initiliase       */
    
		for(unsigned int i = 1; i < this->K; i++) // loop over the other clusters doig the same thing
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < this->number_of_values; j++)
			{
				sum += pow(this->clusters[i].getCentralValue(j) - m_point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				closed_cluster_ID = i;
			}
		}

		return closed_cluster_ID;
}

void KMean::writeOutput(ostream &ofs)
{
    for(int i = 0; i < K; i++)
		{
			int number_of_points_cluster =  clusters[i].getNumberOfPoints();

			ofs << "Cluster " << clusters[i].getID() << endl;
			for(int p = 0; p < number_of_points_cluster; p++)
			{
			  ofs << "Point " << clusters[i].getPoint(p).getID() + 1 << ": ";
				for(int d = 0; d < this->number_of_values; d++)
        {
	  ofs << clusters[i].getPoint(p).getValue(d) << " ";
        }

				string point_name = clusters[i].getPoint(p).getName();

				if(point_name != "")
				  ofs << " - ";
				  ofs << point_name;

				ofs << endl;
			}

				ofs << "Central value : ";

			for(int d = 0; d < this->number_of_values; d++)
			  {
	ofs << clusters[i].getCentralValue(d) << " ";
				}
			ofs << "\n\n";
		}
}
void KMean::solve(vector<Point> & points) // Run the algorithm 
{
		if(K > this->number_of_points) return; // Simple check. 

		vector<int> already_used_indexes;

		// choose K distinct (random) point to be the centers of the clusters
		for(unsigned int i = 0; i < K; i++)
		{
			while(true)
			{
				int point_ID = rand() % this->number_of_points; // randomize modulo the number of point

				if(find(already_used_indexes.begin(), already_used_indexes.end(),point_ID) == already_used_indexes.end()) // if the index is not already assign to a cluster
				{
					already_used_indexes.push_back(point_ID);
          Cluster cluster(i, points[point_ID]); // construct the cluster
					points[point_ID].setCluster(i); // Set the cluster
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;
    bool NotConverged = true;
		while(NotConverged || iter < max_iterations) // until max-iteration is reached or convergence is set 
		{
      NotConverged= false;
			// associates each point to the nearest center
			for(int i = 0; i < this->number_of_points; i++)
			{
				int id_old_cluster = points[i].getCluster(); // get precedent cluster id
				int id_nearest_center = getIDNearestCenter(points[i]); // get neareast cluster id

				if(id_old_cluster != id_nearest_center) // if they are different
				{
					clusters[id_old_cluster].removePoint(points[i].getID()); // remove it from the precedent cluster 
					points[i].setCluster(id_nearest_center); // change the cluster id of the point !
					clusters[id_nearest_center].addPoint(points[i]); // Add the point to the nearest cluster
					NotConverged = true;
				}
			}
			
			for(int i = 0; i < this->K; i++) // recalculating the center of each cluster
			{
				for(int d = 0; d < this->number_of_values; d++) // in each dimension
				{
					unsigned int number_of_points_cluster = clusters[i].getNumberOfPoints();
					double sum = 0.0;

					if(number_of_points_cluster > 0) // simple check
					{
						for(unsigned int p = 0; p < number_of_points_cluster; p++) // loop on the point of the cluster
            {
							sum += clusters[i].getPoint(p).getValue(d); // Sum to get the center (barycentre) for the d-th dimension
            }
						clusters[i].setCentralValue(d, sum / number_of_points_cluster);
					}
				}
			}
			iter++;
		}

		// Write output
    ofstream out_file("Results.txt");	
    writeOutput(out_file);
}
