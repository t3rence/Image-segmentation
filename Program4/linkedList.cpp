// linkedList.cpp
// Author: Terence Ho
//
// This file is the linked list class. 
// Linked lists are used to store pixels with similar color found by recursion.
// Linked list can be merged and extended through the insert and remove function. 
// There is a method that uses recursion to create a new image with the 
// average color of pixel colors in the image.
//---------------------------------------------------------------------------
#include "linkedList.h"
#include "imageClass.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
// Constructor
// Starts with empty list by setting head to NULL.
// Precondition: Has no inputs into the function
// Postcondition: Creates empty linked list by setting a new head to null
//                The next that after the head pointer is nullptr
linkedList::linkedList() {
	head = nullptr;
}

//----------------------------------------------------------------------------
// Copy Constructor
// Starts with empty list by setting head to NULL.
// Precondition: Has no inputs into the function
// Postcondition: Creates empty linked list by setting a new head to null
//                The next that after the head pointer is nullptr
linkedList::linkedList(linkedList const & rightSide) {
	head = nullptr;
	*this = rightSide;
}

//----------------------------------------------------------------------------
// Destructor
// Delete contents in linked list by deleting individual nodes
// Delete contents of node and head pointer
// Precondition: Has no input parameters
// Postcondition: Walks through the linked list and deletes the nodes
//                through recursion. head is set to nullptr at the end
linkedList :: ~linkedList() {
	// check if head is nullptr
	if (head != nullptr) {
		Node* curr = head;

		// walk through linkedlist
		while (head != nullptr) {
			head = head->next;
			delete curr;
			curr = head;
		}
		head = nullptr;
	}
}

//----------------------------------------------------------------------------
// addPixel to linkedList
// Precondtion: Takes in a valid linked list and pixel.
// Postcondition: No return value
//                Walks through the linked list by checking if the nodes are
//                  equal to nullptr
//                Create new node with node using the pixel object as Node data
//                  and add to linked list.
void linkedList::addPixel(int r, int c, const pixel& newPixel) {
	// checks if the list is empty, if so create a new node as head
	if (isEmpty()) {
		head = new Node;
		head->rowNum = r;
		head->colNum = c;
		head->data = newPixel;
		head->next = nullptr;
	} else {
		// create a new node and add to the linked list
		Node *newNode = new Node;
		newNode->rowNum = r;
		newNode->colNum = c;
		newNode->data = newPixel;

		// reset head, set the new node as head
		newNode->next = head;
		head = newNode;
	}

}

//----------------------------------------------------------------------------
// merge linkedLists
// Precondtion: Takes in 2 sorted linkedlists and merges into one
// Postcondition: Return true if linked list are sucessfully linked.
//                Check to find the larger sized linked list.
//                Walk through the larger list and add the head of the second
//                  list to the first list to merge it.
//
void linkedList::merge(const linkedList& secondList) {
	// check if both objects have the same address
	if (this == &secondList) {
		return;
	}

	// check if list is empty
	if (secondList.isEmpty()) {
		return;
	}

    Node *current = secondList.head;
	// walk through the list
    while (current != nullptr) {
		int row = current->rowNum;
		int col = current->colNum;
		pixel data = current->data;
		// add each pixel into the linked list from the second list
		addPixel(row, col, data);	
		current = current->next;
    }
}

//----------------------------------------------------------------------------
// Finds the size of the linked list
// Precondition: Requires an existing linked list.
// Postcondition: Calculates the size of the linked list by walking through x
//                  the list and incrementing a counter.
//                Return the counter
int linkedList::size() {
    int retVal = 0;
	// check if list is empty
	if (!isEmpty()) {
		Node *current = head;
		// walk through the list
		while (current != nullptr) {
			retVal++;
			current = current->next;
		}
	}
	return retVal;
}

//----------------------------------------------------------------------------
// Returns the average color of 4 pixels
// Precondition: Requires 4 pixels as input
// Postcondition: Returns the average color values of the pixels
//                Adds the pixel color values together and divides it by 4
//                  for the number of pixels
//                Takes O(n) time
pixel linkedList::averageColor() {
	pixel temp;
	temp.blue = 250;
	temp.red = 250;
	temp.green = 250;

	// check if list is empty or size is 0
	if (isEmpty() || size() == 0) {
		return temp;
	}

    int redSum = 0;
    int greenSum = 0;
    int blueSum = 0;
	int count = size();
    Node *current = head;
    while (current != nullptr) {
        redSum += temp.red;
        greenSum += temp.green;
        blueSum += temp.blue;
		count++;
        current = current->next;
    }
	temp.red = redSum / count;
	temp.green = greenSum / count;
	temp.blue = blueSum/count;
    return temp;
}

//----------------------------------------------------------------------------
// Check if pixel is in the linked list
// Precondition: Requires an existing linked list and pixel
// Postcondition: Walk through the linked list and check if pixel is equal to
//                  current data
//                Return true if found, false if not found
bool linkedList:: isInLinkedList(pixel data) {
    Node *current = head;
	// walk through linked list to check if data exists
    while (current != nullptr) {
        if (current->data.red == data.red &&
			current->data.green == data.green &&
			current->data.blue == data.blue) {
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------
// operator=
// Overloads operator assignment.
// Precondition: Takes in another linkedList
//                  Linked list must be valid, size > 0 or not empty
// Postcondition: returns reference to this list.
//                  Assigns one list to another, deep copy (all new memory).
//                  Template list input parameter used to assign data to current list.
linkedList& linkedList:: operator= (const linkedList& rightSide) {
	// check if both objects have the same address
    if (this == &rightSide) {
        return *this;
    }
	makeEmpty(); //empty the current list
	if (rightSide.head == nullptr) {
		return *this;
	}

	// set the first new node as head with copied data
	head = new Node;
	head->rowNum = rightSide.head->rowNum;
	head->colNum = rightSide.head->colNum;
	head->data = rightSide.head->data;

	Node *currentRight = rightSide.head->next;
	Node *current = head;

	// walk through both linked lists
	while (currentRight != nullptr) {
		current->next = new Node;
		current->next->rowNum = current->rowNum;
		current->next->colNum = current->colNum;
		current->data = currentRight->data;
		current = current->next;
		currentRight = currentRight->next;
	}
	current->next = nullptr;
    return *this;
}

//----------------------------------------------------------------------------
// isEmpty
// Precondition: Takes in the current linkedList
// Postcondition: returns true if the head is null pointer
bool linkedList :: isEmpty() const {
	return head == nullptr;
}

//----------------------------------------------------------------------------
// deleteFirst()
// Precondition: Takes in the current linkedList
//				requires a valid linked list that isn't empty
// Postcondition: Deletes the first node of the linked list and 
//						sets the temporary node to null pointer
//						deletes the temporary node
void linkedList :: deleteFirst() {
	if (!isEmpty()) {
		Node* temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
	}
}

//----------------------------------------------------------------------------
// makeEmpty
// Precondition: Takes in the current linkedList
//				requires a valid linked list that isn't empty
// Postcondition: void method
//                 wallks through the linked list and deletes each node, 
//					sets the head to null pointer at the end
void linkedList::makeEmpty() {
	if (!isEmpty()) {
		Node* current = head;

		// walk through linkedlist
		while (head != nullptr) {
			head = head->next;
			delete current;
			current = head;
		}
		head = nullptr;
	}
}

/*
//----------------------------------------------------------------------------
// Overrides output stream
// Walks through the linked list and returns the data from the linked list
friend ostream& operator<<(ostream& output, const linkedList& theList) {
	Node* current = theList.head;
	while (current != NULL) {
		output << *current->data;
		current = current->next;
	}
	return output;
}

*/