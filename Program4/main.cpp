// main.cpp
// Author: Terence Ho
//
// This is the driver of a linkedList that is used to find the image's 
// similar pixels and groups them together in linked lists.
//---------------------------------------------------------------------------
#include "linkedList.h"
#include "ImageClass.h"
#include <iostream>
using namespace std;

void pixelCheck(int row, int col, imageClass &inputIM, imageClass &outputIM, pixel &seed, linkedList &seedNode);
void colorOutputPixels(int row, int col, imageClass &inputIM, imageClass &outputIM, pixel &avgPix);
int main() {
	// Read file
	// Create input image object
	imageClass input = imageClass("test.gif");
	// Create output image object
	imageClass output = imageClass(input.getRow(),input.getCol());
/*
	for (int i = 0; i < input.getRow() - 1; i++) {
		for (int j = 0; j < input.getCol() - 1; j++) {
			output.setPixel(i, j, 255, 255, 255);
		}
	}
*/

	// Create linked list for merge
	linkedList merged = linkedList();
	// Create linked list for current
	linkedList current = linkedList();
	int segments = 0;

	// Loop through image
	for (int i = 0; i < input.getRow()-1; i++) {
		for (int j = 0; j < input.getCol() - 1; j++) {
			if (output.getPixel(i, j).red == 0 &&
				output.getPixel(i, j).green == 0 &&
				output.getPixel(i, j).blue == 0) {
				// make a seed pixel
				pixel seedPixel = input.getPixel(i, j);

				// if it's not part of a seed
				current.addPixel(i,j,seedPixel);

				// call recursion method for forming a connected group
				pixelCheck(i, j, input, output, seedPixel, current);


				// find the average color of connected group
				pixel averagePixel = current.averageColor();

				// merge the connected group to the merged object
				merged.merge(current);

				// color output image with pixels
				colorOutputPixels(i, j, input, output, averagePixel);

				segments++;
				current.makeEmpty();
			}
		}
	}
	cout << "Segements: " << segments << " Merged size:" << merged.size() << endl;
	cout << " Average color (red): " << (int) merged.averageColor().red << endl;
	cout << " Average color (green): " << (int) merged.averageColor().green << endl;
	cout << " Average color (blue): " << (int) merged.averageColor().blue << endl;

	// create output image file
	output.createGIF("output.gif");

	// Clean up memory automatically
	// Wait for user input before exiting
	system("PAUSE");
	return 0;
}

//----------------------------------------------------------------------------
// Precondition: Takes in a head node, inputImage, rows and columns.
//              Head node will be created if list is size 0.
//              inputImage must be valid, rows and columns must be
//              greater than and equal to 0.
// Postcondition: Recursively loop through the image pixels
//                Compare the pixel values to add to linked list.
//                Takes O(n^2) time
void pixelCheck(int row, int col, imageClass &inputIM, imageClass &outputIM, pixel &seed, linkedList &seedNode) {
	// Check if pixel is within input image bounds
    if (inputIM.getCol() <= col ||
		inputIM.getRow() <= row ||
		col < 0 || row < 0) {
		return;
	}

	// Check if pixel is already in linkedList
	if (outputIM.getPixel(row, col).red == 255 &&
		outputIM.getPixel(row, col).green == 255 &&
		outputIM.getPixel(row, col).blue == 255) {
		return;
	}

    // Check if pixel is close enough by color
    if (abs(seed.red - inputIM.getPixel(row,col).red) +
        abs(seed.green - inputIM.getPixel(row,col).green) +
        abs(seed.blue - inputIM.getPixel(row,col).blue) >= 100) {
		return;
	}

	// add pixels in the connected group
	seedNode.addPixel(row, col, inputIM.getPixel(row, col));
	// marks pixel as added into output image
	outputIM.setPixel(row, col, 255, 255, 255);

	// recursively call method on four directions
	pixelCheck(row, col + 1, inputIM, outputIM, seed, seedNode);
	pixelCheck(row, col - 1, inputIM, outputIM, seed, seedNode);
	pixelCheck(row-1, col, inputIM, outputIM, seed, seedNode);
	pixelCheck(row+1, col, inputIM, outputIM, seed, seedNode);
}

//----------------------------------------------------------------------------
// Color the pixels in the output image using the average pixel colors
// precondition: rows and columns must be valid/within bounds of input image
//				 input and output images are valid and can be accessed through the imageClass
// postcondition: void method, sets output image pixels with predetermined set colors
//					to the average color pixel
//			
void colorOutputPixels(int row, int col, imageClass &inputIM, imageClass &outputIM, pixel &avgPix) {
	// finds the marked pixels
	if(outputIM.getPixel(row,col).red == 255 &&
		outputIM.getPixel(row, col).green == 255 &&
		outputIM.getPixel(row, col).blue == 255) {
		// sets the pixel from the output image that has been marked into the average pixel values
		outputIM.setPixel(row, col, avgPix.red, avgPix.green, avgPix.blue);
	}
}
