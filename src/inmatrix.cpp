/*
 * inmatrix.cpp
 *
 *  Created on: Apr 25, 2013
 *      Author: kristin
 */

#include "inmatrix.h"

InMatrix::InMatrix(unsigned numpoints, const string cachefile,
		   const string cacheOptions, unsigned long ramUse):sorter(Cmp(),ramUse) {

	//set Matrix::threshold, numPoints
	stxxl::config * cfg = stxxl::config::get_instance();
	unsigned long diskSize=numpoints?12L*numpoints*(numpoints-1)/2:2L*1024L*1024L*1024L;
	stxxl::disk_config disk1(cachefile, diskSize, cacheOptions);
	//disk1.direct = stxxl::disk_config::DIRECT_OFF;
	cfg->add_disk(disk1);
}

bool InMatrix::getNext(uint &row, uint &col, float &value) {
	if (!sorter.empty()) {
		Element e=*sorter;
		row=e.row;
		col=e.col;
		value=e.value;
		++sorter;
		return true;
	}
	else {
		return false;
	}
}

Element* InMatrix::getNext() {
	if (pos < elements.size())
		return elements[pos++];
	else {
		if (loadElements())
			return elements[pos++];
		else
			return NULL;
	}
}

bool InMatrix::loadElements() {

	this->clear();
	pos = 0;

	uint size = 0;
	Element e;

	while (!sorter.empty() && size < 4096) {
		e=*sorter;
		++sorter;
		if ( e.value < threshold ) {
			this->push(e.row, e.col, e.value);
			++size;
		} else {
			fprintf(stderr, "Stop at: %u %u %f\n", e.row, e.col, e.value);
		}
	}

	numElements += size;
	if (size > 0)
		return true;
	else
		return false;
}
