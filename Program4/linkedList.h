// linkedList.h
// Author: Terence Ho
//
// This file describes header file for using a linked list and recursion to
// create a new image with the average color of pixel colors in the image.
// Linked lists are used to store pixels with similar color found by recursion.
// Linked list can be merged and extended through the insert and remove function. 
// Comments and prototypes for each function in the main as well as the
// pseudocode for important functions/methods are included.
//---------------------------------------------------------------------------

#pragma once
#include <iostream>
#include "imageClass.h"
using namespace std;

class linkedList {
/*
	//----------------------------------------------------------------------------
    // Overrides output stream
    // Walks through the linked list and returns the data from the linked list
	friend ostream& operator<<(ostream& output, const linkedList& theList);
	*/
public:
	linkedList();                                         // default constructor
	linkedList(linkedList const & rightSide);			  // copy constructor
	~linkedList();										  // destructor
	void addPixel(int r, int c, const pixel & newPixel);  // insert node to list
	void merge(const linkedList & secondList);            // merge
    bool isInLinkedList(pixel data);					  // check if is in linked list

	// check if pixel is in linked list
    int size();                                           // size of function
    pixel averageColor();								  // average color value
	bool isEmpty() const;								  // check if is empty 
	void deleteFirst();									  // delete first node
	void makeEmpty();									  // empty list

    // assignment operator
    linkedList& operator= (const linkedList& rightSide);

private:
	struct Node {
		pixel data;	// pointer to the data in the node
		int rowNum;
		int colNum;
		Node *next; // pointer to the next node
		};
	Node *head;		// pointer to the first node
};
