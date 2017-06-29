/****************************************************************
*      Author: 
*      Dr. Rashed Karim 
*      Department of Biomedical Engineering, King's College London
*      Email: rashed 'dot' karim @kcl.ac.uk  
*      Copyright (c) 2016
*****************************************************************/

// Makes use of the proprietory Image Registration Toolkit library (IRTK) from Imperial Colllege London. 
#include "mirtk/Common.h"
#include "mirtk/Options.h"
#include "mirtk/IOConfig.h"
#include "mirtk/GenericImage.h"

// Other standard C libraries 
#include <fstream>
#include <vector>

using namespace mirtk;

void MaskedVolume(char* fn1, char* fn2, int t1, int t2, char* output_f) 
{
	double x_size, y_size, z_size, vol, vol_mask; 
	double xm_size, ym_size, zm_size;
	int n_mask=0, n_image= 0;

    // read image
    InitializeIOLibrary();
    UniquePtr<BaseImage> img1(BaseImage::New(fn1));
    UniquePtr<BaseImage> img2(BaseImage::New(fn2));

    RealImage m1, m2; 
    m1 = img1; 
    m2 = img2;

	RealPixel* mp1, *mp2; 

	mp1 = m1.GetPointerToVoxels();
	mp2 = m2.GetPointerToVoxels();

	m1.GetPixelSize(&x_size, &y_size, &z_size);
	m2.GetPixelSize(&xm_size, &ym_size, &zm_size);
	
	for (int i=0;i<m1.GetNumberOfVoxels();i++)
	{
		if (*mp2 == t2 && *mp1 == t1)	{
			n_image++;
		}
		
		if (*mp2 == t2) 
		{
			n_mask++;
			
		}
		mp1++; 
		mp2++;
	}
	
	vol = n_image*x_size*y_size*z_size;
	vol_mask = n_mask*xm_size*ym_size*zm_size;
	if (string(output_f) == "")
		cout << "Report\n========\nTotal pixels (image, mask)= \t" << n_image << "," << n_mask << "\nVolume image = \t\t\t" << vol << "\nVolume in mask = \t\t" << vol_mask << endl; 
	else 
	{
		ofstream out; 
		out.open(output_f, ios::app); 
		cout << "Outputting to " << output_f << "as: total pixels in image, total pixels in mask, image volume, mask volume" << endl;
		out << n_image << "\t" << n_mask << "\t" << vol << "\t" << vol_mask << endl;
		out.close();

	}
}


int main(int argc, char **argv)
{
	int option;
	bool foundArgs1=false,foundArgs2=false,foundArgs3=false, foundArgs4 = false, foundMethod=false, tofile =false; 
	char* input_f1="", *output_f="", *input_f2=""; 
	int t1, t2, t3; 

	if (argc >= 1)
	{
			for (int i = 1; i < argc; i++) {
				if (i + 1 != argc) {
					if (string(argv[i]) == "-i1") {
						input_f1 = argv[i+1]; 
						foundArgs1 = true;
					} else if (string(argv[i]) == "-i2") {
						input_f2 = argv[i+1]; 
						foundArgs2 = true;
					} else if (string(argv[i]) == "-t1") {
						t1 = atoi(argv[i+1]);
						foundArgs3 = true;
					} else if (string(argv[i]) == "-t2") {
						t2 = atoi(argv[i+1]);
						foundArgs4 = true;
					} else if (string(argv[i]) == "-o") { 
						output_f = argv[i+1];
						tofile = true; 
					}

					
					
				}
			}
	}

	if (!(foundArgs1 && foundArgs2 && foundArgs3 && foundArgs4))
	{
		cout << "\n\nUsage: maskedvolume \n\n\tArguments:"
			"\n\t -i1 \t - image segmentation 1 and 0"
			"\n\t -i2 \t - mask" 
			"\n\t -t1 \t - Value in image"
			"\n\t -t2 \t - Value in mask"
			"\n\n";
		exit(0);
	}
	else
	{
		MaskedVolume(input_f1, input_f2, t1, t2, output_f);
	}
	

}       // end main 
