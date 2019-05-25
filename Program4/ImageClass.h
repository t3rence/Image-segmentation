// imageClass.h
// Author: Terence Ho
//
// This file describes the interface to the ImageClass library used 
// to create ImageClass objects that can hold abstract data types. 
// This library overrides the default output method and holds the 
// header to the compare, assignment, destructor and additional 
// constructors. 
//---------------------------------------------------------------------------

#pragma once
#include "ImageLib.h"
#include <iostream>

using namespace std;

class imageClass {
	// Overloaded <<
	// Output stream, displays rows and columns of the image object
	// Precondition: Uses another imageClass object and output stream
	// Postcondition: Returns rows and columns
	friend ostream& operator<<(ostream & output, const imageClass & otherImage);

public:

	// imageClass(filename)
	// Constructor with filename
	// Precondition: Uses filename as input to create inputImage object
	//				 Runs ImageLib to ReadGIF using filename
	// Postcondition: Changes current inputImage object to Image based on filename
	imageClass(string filename);

	// imageClass(rows & columns)
	// Constructor with rows and columns
	// Precondition: Uses rows and columns as input to create a black image at 
	//				 that size 
	// Postcondition: Each pixel color value to 255 after creating a new
	//				  inputImage object. 
	imageClass(int rows, int columns);

	// imageClass(imageClass otherImage)
	// Copy constructor 
	// Precondition: Uses otherImage object and copies to current image using 
	//				 ImageLib's CopyImage method.
	// Postcondition: Creates deep copy of otherImage to current image
	imageClass(imageClass const & otherImage);

	// getImage()
	// Image accessor
	// Precondition: Runs when called through the ImageClass object
	// Postcondition: Returns inputImage package
	image getImage();

	// getPixel()
	// Pixel accessor
	// Precondition: Uses rows and columns as input
	// Postcondition: Returns inputImage pixel
	pixel getPixel(int rows, int cols);

	int getRow();

	int getCol();

	// setPixel()
	// Pixel mutator
	// Precondition: Uses rows, columns, red color value, green color value, blue
	//				 color value as input.
	// Postcondition: Sets current image pixel colors individually
	void setPixel(int rows, int cols, int red, int green, int blue);

	// operator=
	// Copies otherImage to current image
	// Precondition: Uses another imageClass object to copy the image to the
	//				 existing image.
	// Postcondition: Returns the modified current imageClass copied 
	//				  from the other image. 
	imageClass& operator=(const imageClass & otherImage);

	// operator==
	// Boolean comparison with current object and other object
	// Precondition: Uses another imageClass object to compare the image to the
	//				 existing image.
	// Postcondition: Compares each color of pixel from the current image
	//				  with the pixel of the otherImage
	//				  Returns true if both are the same, else false
	bool operator==(const imageClass & otherImage) const; 

	// operator!=
	// Boolean comparison does the opposite of operator==
	// Precondition: Uses another imageClass object to compare the image to the
	//				 existing image.
	// Postcondition: Returns the opposite boolean of operator== 
	bool operator!=(const imageClass & otherImage) const;

	// ~imageClass()
	// Destructor deletes the inputImage object
	// Precondition: Runs through a ImageClass object
	// Postcondition: Deallocates image from memory
	~imageClass();

	// compareImage()
	// Precondition: Use another imageClass object to compare the pixels
	// Postcondition: 
	//				Returns a counter based on the number of 
	//				different pixels betweeen the two images.
	int compareImage(imageClass otherImage);

	// photoNegative()
	// Precondition: Use another imageClass object to create photonegative
	//				 valid imageClass object used
	// Postcondition: Returns new photonegative imageClass object
	imageClass photoNegative();

	void createGIF(string filename);

private:
	image inputImage;
};
