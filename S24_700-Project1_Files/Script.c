/*
@author: Jigyas Sharma
@course: Software Reverse Engineering
@description: This is a script that takes a file as an input and then checks if the file is a ELF binary, and if it is then prints more information about each section of the executable
*/

#Importing Libraries
#include<iostream>
#include<string>

/*
@param: name of file or file path
@ret: null
@desc: This is the main function which takes in the file or file path and then calls different functions over the file to check the validity of the file and extract information about the file
*/
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cerr << "Correct Script Command: " << argv[0] <<" <file_name>/<file_path> \n";
		return 1;
	}
	std::string filePath = argv[1];	
	int fileStatus = checkELFStatus(filePath);
	
	switch(fileStatus) 
	{
		case 0:
			std::cout<<"File is a valid ELF binary.\n";
			std::cout<<"Processing Sections of Binary.\n";
		case -1:
			std::cerr<<"Error: System call failed.\n"
		case -2:
			std::cerr<<"Error: File is not a valid ELF
	}
}
