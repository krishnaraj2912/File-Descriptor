# File-Descriptor
### Video Explanation Link:
https://drive.google.com/file/d/1D3Mv8GzciETwDfaVGfh-UPbddwwNIFF-/view?usp=sharing

### Objective:
Building a program to display the properties of a file.

### Implementation Details:
The file is read as a command line argument. With the help of stat data structure, we create a stat structure and use stat() function to list properties of a file identified by path. It reads all file properties and dumps to buf structure. The function is defined in sys/stat.h header file.
