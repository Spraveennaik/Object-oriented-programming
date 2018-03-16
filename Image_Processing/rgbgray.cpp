#include <bits/stdc++.h>
#define HEADER_LENGTH 54
#define MAX_ROW_SIZE 10000
using namespace std;

class Image
{
	ifstream fin;
public:
	Image(){}
	Image(const char filename[]){
		fin.open(filename, ios::binary);
	}
	~Image(){
		fin.close();
	}

	void open(char filename[]){
		fin.open(filename, ios::binary);
	}

	void RGB_toGrayScale(const char output_filename[]);
};

void Image::RGB_toGrayScale(const char output_filename[])
{
	ofstream fout(output_filename, ios::binary);
	unsigned char header[HEADER_LENGTH];

	fin.read((char *)header, HEADER_LENGTH);
	fout.write((char *)header, HEADER_LENGTH);

	int width = *(int *)&header[18];
	int height = *(int *)&header[22];

	int row_size = 4*ceil(width*3.0/4);

	unsigned char pixels[MAX_ROW_SIZE];

	for(int i=0; i<=height; i++)
	{
		//Default BGR
		fin.read((char *)pixels, row_size);

		for(int j=0; j<width*3; j+=3)
		{
			int avg = (int)pixels[j] + (int)pixels[j+1] + (int)pixels[j+2];
			avg/=3;

			pixels[j] = avg;
			pixels[j+1] = avg;
			pixels[j+2] = avg;
		}

		fout.write((char *)pixels, row_size);
	}

	fout.close();
}

int main()
{
	Image img("input.bmp");
	img.RGB_toGrayScale("grayscale.bmp");
}