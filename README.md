# Volume under a 3D mask 
Computes the total volume of pixels in a binary or labelled image as indicated by a mask image. Labelled image may be labelled with any number of labels indicated by an integer 1,2,3, etc. Mask image also could have any number of labels as this label can be specified.

## Usage 
The usage is through command line: 
```
mirtk evaluate-la-wall -i1 <mask image> -t1 <label in mask image> -o <output file optional> 
```

## Image requirements 
This program outputs the total number of pixels and volume in mm^3 in label ```t1``` by obtaining the image resloution. 
All input image files are either NifTII or GIPL or HDR Analyze. 

## Parameters 
the ```<mask image>``` is an image with labels 1,2,3 and so on. the ```<label in mask image>``` specifies which label you wish to calculate the volume for

## Output 
The program optionally accepts a filename to which it can write the volume. 

## Testing
Not tested fully, only with a few images and comparison to ```Volume and Statistics``` option in ITK-Snap was OK. 

## Author 
```
Dr. Rashed Karim 
Department of Biomedical Engineering 
King's College London 
```
