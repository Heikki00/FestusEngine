#include "ImageData.h"
#include "FreeImage.h"



ImageData::ImageData(const string& filename)
{
	//Image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	//Pointer to the image, once loaded
	image = nullptr;


	//Pointer to the image data
	BYTE* bits = nullptr;



	//Check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	//If still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename.c_str());

	//If still unknown, send an error message
	if (fif == FIF_UNKNOWN) {
		Debug::log(ErrorType::FILE_ERROR, "ERROR: Could not determine the type of the texture file %s\n", filename.c_str());
		return;
	}



	image = FreeImage_Load(fif, filename.c_str());

	//If the image failed to load, send an error message
	if (!image) {
		Debug::log(ErrorType::FILE_ERROR, "ERROR: Could not read the texture file %s\n", filename.c_str());
		return;
	}

}

ImageData::~ImageData()
{
	FreeImage_Unload(static_cast<FIBITMAP*>(image));
}

ColorData ImageData::getPixel(U32 x, U32 y) const
{
	RGBQUAD val;
	FreeImage_GetPixelColor(static_cast<FIBITMAP*>(image), x, y, &val);

	return{ val.rgbRed, val.rgbBlue, val.rgbGreen, val.rgbReserved };
}

U32 ImageData::getWidth() const
{
	return FreeImage_GetWidth(static_cast<FIBITMAP*>(image));
}

U32 ImageData::getHeight() const
{
	return FreeImage_GetHeight(static_cast<FIBITMAP*>(image));
}

