// imageClass.cpp
// Author: Terence Ho
// 
// Abstract data type ImageClass is used to implement the image object.
// Each image object of the imageClass can be compared with the overridden 
// operator== and operator!= and copied using the operator= method. 
//---------------------------------------------------------------------------
#include "ImageLib.h"
#include "ImageClass.h"
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------
// imageClass(filename)
// Constructor with filename
// Precondition: Uses filename as input to create inputImage object
//				 Runs ImageLib to ReadGIF using filename
// Postcondition: Changes current inputImage object to Image based on filename
imageClass::imageClass(string filename) {
	inputImage = ReadGIF(filename);
}


//---------------------------------------------------------------------------
// imageClass(rows & columns)
// Constructor with rows and columns
// Precondition: Uses rows and columns as input to create a black image at 
//				 that size 
// Postcondition: Each pixel color value to 255 after creating a new
//				  inputImage object. 
imageClass::imageClass(int rows, int columns) {
	if (rows > 0 && columns > 0) {
		// Image Row & Column is flipped from the image library so I swapped 
		inputImage = CreateImage(rows, columns);

//		WriteGIF("output.gif", inputImage);
//		cout << "Image created!" << endl;
	} else {
		cout << "invalid image size!" << endl;
	}
}

//---------------------------------------------------------------------------
// imageClass(imageClass otherImage)
// Copy constructor 
// Precondition: Uses otherImage object and copies to current image using 
//				 ImageLib's CopyImage method.
// Postcondition: Creates deep copy of otherImage to current image
imageClass::imageClass(imageClass const & otherImage) {
	inputImage = CopyImage(otherImage.inputImage);  // Deep copy
//	cout << "Image object copied" << endl;
}

//---------------------------------------------------------------------------
// getImage()
// Image accessor
// Precondition: Runs when called through the ImageClass object
// Postcondition: Returns inputImage package
image imageClass::getImage() {
	return inputImage;
}

//---------------------------------------------------------------------------
// getPixel()
// Pixel accessor
// Precondition: Uses rows and columns as input
// Postcondition: Returns inputImage pixel
pixel imageClass::getPixel(int rows, int cols) {
	pixel retPixel = inputImage.pixels[rows][cols];
	return retPixel;
}

//---------------------------------------------------------------------------
// getRow()
// Row accessor
// Precondition: no input
// Postcondition: Returns inputImage row
int imageClass::getRow() {
	return inputImage.rows;
}

//---------------------------------------------------------------------------
// getCol()
// Col accessor
// Precondition: no input
// Postcondition: Returns inputImage col
int imageClass::getCol() {
	return inputImage.cols;
}

//---------------------------------------------------------------------------
// setPixel()
// Pixel mutator
// Precondition: Uses rows, columns, red color value, green color value, blue
//				 color value as input.
// Postcondition: Sets current image pixel colors individually
void imageClass::setPixel(int rows, int cols, int red, int green, int blue) {
	if (rows >= 0 && cols >= 0) {
		// Red overflow & underflow check
		if (red > 255) {
			red = 255;
		}
		else if (red < 0) {
			red = 0;
		}

		// Green overflow & underflow check
		if (green > 255) {
			green = 255;
		}
		else if (green < 0) {
			green = 0;
		}

		// Blue overflow & underflow check
		if (blue > 255) {
			blue = 255;
		}
		else if (blue < 0) {
			blue = 0;
		}

		// Set color values
		inputImage.pixels[rows][cols].red = red;
		inputImage.pixels[rows][cols].green = green;
		inputImage.pixels[rows][cols].blue = blue;
	}
	else {
		cout << "unable to set pixel." << endl;
	}
}



//---------------------------------------------------------------------------
// operator=
// Copies otherImage to current image
// Precondition: Uses another imageClass object to copy the image to the
//				 existing image.
// Postcondition: Returns the modified current imageClass copied 
//				  from the other image. 
imageClass& imageClass::operator=(const imageClass & otherImage) {
	if (this != &otherImage) {
		DeallocateImage(inputImage);
		inputImage = CopyImage(otherImage.inputImage);
	}
	cout << "Current image copied to existing image" << endl;
	return *this;
}

//---------------------------------------------------------------------------
// operator==
// Boolean comparison with current object and other object
// Precondition: Uses another imageClass object to compare the image to the
//				 existing image.
// Postcondition: Compares each color of pixel from the current image
//				  with the pixel of the otherImage
//				  Returns true if both are the same, else false
bool imageClass::operator==(const imageClass & otherImage) const {
	int columnsInput = otherImage.inputImage.cols;
	int rowsInput = otherImage.inputImage.rows;
	for (int row = 0; row < rowsInput; row++) {
		for (int col = 0; col < columnsInput; col++) {
			if (inputImage.pixels[row][col].red != 
				otherImage.inputImage.pixels[row][col].red ||
				inputImage.pixels[row][col].blue != 
				otherImage.inputImage.pixels[row][col].blue ||
				inputImage.pixels[row][col].green != 
				otherImage.inputImage.pixels[row][col].green) {
				cout << "Images are different" << endl;
				return false;
			}
			
		}
	}
	cout << "Images the same" << endl;
	return true;
}

//---------------------------------------------------------------------------
// operator!=
// Boolean comparison does the opposite of operator==
// Precondition: Uses another imageClass object to compare the image to the
//				 existing image.
// Postcondition: Returns the opposite boolean of operator== 
bool imageClass::operator!=(const imageClass & otherImage) const {
	return !operator==(otherImage);
}


//---------------------------------------------------------------------------
// Overloaded <<
// Output stream, displays rows and columns of the image object
// Precondition: Uses another imageClass object and output stream
// Postcondition: Returns rows and columns
ostream & operator<<(ostream & output, const imageClass & otherImage) {
	// Image Row & Column is flipped from the image library so I swapped 
	output << "rows: " << otherImage.inputImage.cols << " columns: "
		<< otherImage.inputImage.rows << endl;
	return output;
}

//---------------------------------------------------------------------------
// ~imageClass()
// Destructor deletes the inputImage object
// Precondition: Runs through a ImageClass object
// Postcondition: Deallocates image from memory
imageClass::~imageClass() {
//	cout << "Deallocating image" << endl;
	DeallocateImage(inputImage);
}

//---------------------------------------------------------------------------
// compareImage()
// Precondition: Use another imageClass object to compare the pixels
//				 The images have the same dimensions
// Postcondition: 
//				Returns a counter based on the number of 
//				different pixels betweeen the two images.
int imageClass:: compareImage(imageClass otherImage) {
	int counter = 0;

	// Different sized images
	if (inputImage.rows != otherImage.inputImage.rows || 
		inputImage.cols != otherImage.inputImage.cols) {
		return NULL;
	}

	for (int row = 0; row < inputImage.rows; row++) {
		for (int col = 0; col < inputImage.cols; col++) {
			// Increase counter if pixel is different colored
			if (getPixel(row, col).blue != otherImage.getPixel(row, col).blue ||
				getPixel(row, col).red != otherImage.getPixel(row, col).red ||
				getPixel(row, col).green != otherImage.getPixel(row, col).green) {
				counter++;
			}
		}
	}
	return counter;
}

//---------------------------------------------------------------------------
// photoNegative()
// Precondition: Use another imageClass object to create photonegative
//				 valid imageClass object used
// Postcondition: Returns new photonegative imageClass object
imageClass imageClass:: photoNegative() {
	imageClass negImage(*this); // Duplicate imageClass object
	for (int row = 0; row < inputImage.rows; row++) {
		for (int col = 0; col < inputImage.cols; col++) {
			// Column modulus 9 + red pixel value
			// Blue pixel value - row modulus 7
			setPixel(row, col, (int)(255-getPixel(row, col).red),
				(int)(255-getPixel(row, col).green),
				(int)(255-getPixel(row, col).blue));
		}
	}
	return negImage;
}

//---------------------------------------------------------------------------
// createGIF()
// Precondition: Filename as a string is used as input
// Postcondition: Writes a GIF using the image library
void imageClass::createGIF(string filename) {
	WriteGIF(filename,inputImage);
}
