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

void MaskedVolume(GreyImage* m1,  int t1,  char* output_f) 
{
	double x_size, y_size, z_size;
    double vol_mask; 
	
	int n_mask=0;

	
	m1->GetPixelSize(&x_size, &y_size, &z_size);
	
	cout << m1->GetX() << ", " << m1->GetY() << ", " << m1->GetZ();
    for (int i=0;i<m1->GetX();i++) 
    {
        for (int j=0;j<m1->GetY();j++) 
        {
	        for (int k=0;k<m1->GetZ();k++)
	        {
                
                if (m1->Get(i,j,k) == t1)
                {
                    n_mask++; 
                }
                
	        }
        }
    }

	
	vol_mask = n_mask*x_size*y_size*z_size;

	if (string(output_f) == "")
		cout << "Report\n========\nTotal pixels with label " << t1 << " =\t" << n_mask << " pixels\nVolume mask = \t\t\t" << vol_mask << " mm3 " <<endl; 
	else 
	{
		ofstream out; 
		out.open(output_f, ios::app); 
		cout << "Outputting to " << output_f << "as: total pixels in image, total pixels in mask, image volume, mask volume" << endl;
		out << vol_mask << endl;
		out.close();

	}
}


int main(int argc, char **argv)
{
	int option;
	bool foundArgs1=false,foundArgs2=false, tofile =false; 
	char* input_f1="", *output_f="";
	int t1; 

	if (argc >= 1)
	{
			for (int i = 1; i < argc; i++) {
				if (i + 1 != argc) {
					if (string(argv[i]) == "-i1") {
						input_f1 = argv[i+1]; 
						foundArgs1 = true;
					} else if (string(argv[i]) == "-t1") {
						t1 = atoi(argv[i+1]);
						foundArgs2 = true;
					} else if (string(argv[i]) == "-o") { 
						output_f = argv[i+1];
						tofile = true; 
					}

				}
			}
	}

	if (!(foundArgs1 && foundArgs2 ))
	{
		cout << "\n\nUsage: maskedvolume \n\n\tArguments:"
			"\n\t -i1 \t - mask image" 
			"\n\t -t1 \t - which label for volume"
			"\n\n";
		exit(0);
	}
	else
	{
         // read image
        InitializeIOLibrary();
        cout << "reading file " << input_f1 << endl;
        UniquePtr<BaseImage> img1(BaseImage::New(input_f1));
        GreyImage m1;
        m1.Read(input_f1);
		MaskedVolume(&m1, t1, output_f);
	}
	

}       // end main 
