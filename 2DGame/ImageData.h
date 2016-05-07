#pragma once


struct ColorData {
	U8 red;
	U8 green;
	U8 blue;
	U8 alpha;
};

class ImageData {
public:

	ImageData(const string& filename);

	~ImageData();

	ColorData getPixel(U32 x, U32 y) const;


	U32 getWidth() const;

	U32 getHeight() const;


	


private:

	
	void* image;




};



