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

int main(int argc, char *argv[])
{
	srand (time(0));

  if (argc < 2){
    cerr<< "Missing data file or number of iteration"<<endl;
    return EXIT_FAILURE;
  }
  unsigned int max_iterations = 1000;
  char* filename = argv[1];
  cout << "Number of Iterations : "<< max_iterations <<endl;
  cout << "Reading files : "<<filename<<endl;
  ifstream data(argv[1]);
  vector<Point> points;
  string point_name;
  unsigned int number_of_points, number_of_values, K, has_name;
  data >> number_of_points >> number_of_values >> K >> max_iterations >> has_name; // parse first line

  //cout << number_of_points <<" "<< number_of_values <<" "<< K <<" "<< max_iterations <<" "<< has_name<<endl; 
  for(unsigned int p = 0; p < number_of_points; p++) // for every point
  {
      vector<double> values;

      for(unsigned int d = 0; d < number_of_values; d++) // in each dimension
      {
        double value;
        data >> value;
        //cout << value << " ";
        values.push_back(value);
      }
      //cout <<endl;
      if(has_name)
      {
        data >> point_name;
        Point point(p, values, point_name); // create the point with, id of the poin ; values for each dimension ; name of the point
        points.push_back(point);
      }
      else
      {
        Point point(p, values);
        points.push_back(point);
      }
  }
  cout<<"Lunching K-Mean Clustering...."<<endl;
  KMean kmean(K, number_of_points, number_of_values, max_iterations,filename); // create the solver
  kmean.solve(points); // solve
  cout<<"end."<<endl;
	return 0;
}
