#include "Bitmap.h"
#include <iostream>
void LoadBitmapReturnValue(int input)
{
	switch (input)
	{
	case ERR_CANNOT_OPEN_FILE:
		std::cerr << "Can not open the file!The path can be incorrect,not have permission to the fil.....!\n";
		break;
	case ERR_WRONG_FILE_TYPE:
		std::cerr << "The load bitmap file is not valid 24-bits bitmap file!\n";
		break;
	case ERR_BUFFER_TOO_SMALL:
		std::cerr << "The load bitmap file array is not enought big to store the image!\n";
		break;
	case ERR_FILE_READ_ERROR:
		std::cerr << "ERROR while reading the file!\n";
		break;
	case ERR_CANNOT_ALLOCATE_MEMORY:
		std::cerr << "Save bitmap file can not to allocate the needed memory!Probably the value of weight of the image is too big!\n";
		break;
	case ERR_ZERO_SIZE:
		std::cerr << "On function SaveBitpam is hand a size ZERO for hight or weight of the image\n";
		break;
	default:
		std::cerr << "Unknown ERROR.Try again!\n";
	}
}
//here the function find how many row of the image are in background!Begin from image[0]
//when it find pixel different from the background it return this row.If the function do not find a such pixel 
//it return zero
	size_t FindFirtsRowWithoutBackground(size_t array_image[], size_t width_image, size_t  height_image, size_t background)
	{
		for (size_t row = 0; row < height_image; row++)
		{
			for (size_t col = 0; col < width_image; col++)
			{
				if (array_image[row*width_image + col] != background)
				{
					return  row;
				}
			}

		}
		return 0;
	}
	//the function find how many row of the image are in background!Begin from the back of the image
	//when it find pixel diferent from the background it retrun this row
	//if the function do not find a such pixel it return zero
	//if the function find a such pixel it change the height of the image according the find row,from this function
	//and the upper one,that contain the background 
	size_t FindLastRowWithoutBackground(size_t array_image[], size_t  width_image, size_t & height_image, size_t background)
	{
		size_t FindBackgroundRow = 0;
		for (int row = height_image-1 ; row >= 0; --row)
		{
			++FindBackgroundRow;
			for (int col = width_image-1 ; col >= 0; --col)
			{
				if (array_image[row*width_image + col] != background)
				{
					height_image -= FindFirtsRowWithoutBackground(array_image, width_image, height_image,background);
					height_image -= FindBackgroundRow;
					return row ;
				}
			}
		}
		return 0;
	}
	//the function find how many colum of the image are in background!Begin from the image[0]
	//when it find pixel diferent from the background it retrun this colum
	//if the function do not find a such pixel it return zero
	size_t FindFristColumWithoutBackground(size_t array_image[], size_t  width_image, size_t  height_image, size_t background)
	{
		for (size_t col = 0; col < width_image; ++col)
		{
			for (size_t row = 0; row < height_image; ++row)
			{
				if (array_image[row*width_image + col ] != background)
				{
					return col;
				}
			}
		}	
		return 0;
	}
	//the function find how many colum of the image are in background!Begin from the back of the image
	//when it find pixel deferent from the background it retrun this colum
	//if the function do not find a such pixel it return zero
	size_t FindLastColumWithoutBackground(size_t array_image[], size_t   width_image, size_t  height_image, size_t background)
	{
		for (int col = width_image-1; col>=0; --col)
		{
			for (int row = height_image-1;row>=0; --row)
			{
				if (array_image[row*width_image + col] != background)
				{
					return col;
				}
			}
		}
		return 0;
	}
	//the function make a call to the other four function and copy ther result in four variables
	//the fuction first make one new variable for the new wight of the image
	//from this variable is removed the colums with the background
	//then change the height
	//the function copy the image in new array from the old one
	//and return the new wight for the image
	size_t CopyNewImageAndReturnItNewWight(size_t array_image[],size_t newarray_image[], size_t   width_image, size_t  & height_image,size_t background)
	{
		
		size_t firstRowWithDiffPixel = FindFirtsRowWithoutBackground(array_image, width_image, height_image, background);
		size_t LastRowWithDiffPixel = FindLastRowWithoutBackground(array_image, width_image, height_image, background);
		size_t firstColumWithDiffPixel = FindFristColumWithoutBackground(array_image, width_image, height_image, background);
		size_t LastColumWithDiffPixel = FindLastColumWithoutBackground(array_image, width_image, height_image, background);
		size_t newwidth = width_image;
		newwidth -= (width_image - LastColumWithDiffPixel + (firstColumWithDiffPixel));
		for (int col = 0, col1 = firstColumWithDiffPixel; col <height_image && col1 <= LastColumWithDiffPixel; ++col, ++col1)
		{
			for (int row = 0, row1 = firstRowWithDiffPixel; row < newwidth && row1 <= LastRowWithDiffPixel; ++row, ++row1)
			{
				newarray_image[row*newwidth + col] = array_image[row1*width_image + col1];
			}
		}
		return newwidth;
	}
int main()
{
	const size_t MAX_SIZE = 100000; 
	unsigned int width, height, image[MAX_SIZE];
	int rval;
	rval = LoadBitmap("sample.bmp", image, MAX_SIZE, width, height);
	if (rval != ALL_OK)
	{
		std::cerr << "Error code " << rval << "\n";
		LoadBitmapReturnValue(rval);
		system("pause");
		return 1;
	}

	std::cout << "Enter a number in hex in ARGB encoding from 0 to 32 bits that indicates the background of the image\n";
	unsigned int background;
	std::cout << "0x";
	std::cin >> std::hex >> background;
	unsigned int newimage[MAX_SIZE];
	unsigned int width1=CopyNewImageAndReturnItNewWight(image, newimage, width, height, background);
	rval = SaveBitmap("sample_new.bmp", newimage, width1, height);

	if (rval != ALL_OK)
	{
		LoadBitmapReturnValue(rval);
		system("pause");
		return 2;
	}
	std::cout << "The image was successfully croped!" << std::endl;
	system("pause");
	return 0;
}

