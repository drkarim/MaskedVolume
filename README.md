# Volume under a 3D mask 
Computes the total volume of pixels in a binary or labelled image as indicated by a mask image. Labelled image may be labelled with any number of labels indicated by an integer 1,2,3, etc. Mask image also could have any number of labels as this label can be specified.

## Usage 
The usage is through command line: 
```
mirtk evaluate-la-wall -i1 <labelled image> -i2 <mask image> -t1 <label in labelled image> -t2 <label in mask image> -o <output file optional> 
```

## Image requirements 
This program outputs the total volume in mm^3 by obtaining the image resloution. 
All input image files are either NifTII or GIPL or HDR Analyze. 

## Parameters 
the ```<labelled image>``` and ```<mask image>``` images 

## Output 
The program optionally accepts a filename to which it can write the volume. 

## Author 
```
Dr. Rashed Karim 
Department of Biomedical Engineering 
King's College London 
```
