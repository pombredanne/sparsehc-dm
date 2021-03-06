/*
 * mincluster.h
 *
 *  Created on: Apr 12, 2013
 *      Author: kristin
 */

#ifndef MINCLUSTER_H_
#define MINCLUSTER_H_

#include "cluster.h"
using namespace std;

struct SingleCluster: public Cluster {

	SingleCluster(uint matDim) :
			Cluster(matDim) {
	}

	Vertex* createVertex(uint id);

	// overrider super methods
	Dendrogram clusterMatrix(InMatrix * mat);
};

#endif /* MINCLUSTER_H_ */
