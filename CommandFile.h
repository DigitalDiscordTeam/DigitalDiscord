#ifndef COMMAND_FILE_H
#define COMMAND_FILE_H

#include "InternalDef.h"
#include "InternalFsys.h"
#include "InternalSys.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalFileVec.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define isEght(tokens) if(((tokenType)tokens).size() < 2) {return false;}

class CommandFile {
private:
	std::string filename;
	std::string path;
	std::ifstream file;
	tokenType read;

	bool comInfo(tokenType tokens);

	bool comCat(tokenType tokens);

	bool comCorr(tokenType tokens);
	
	bool comCout(tokenType tokens);

	bool comSer(tokenType tokens);
	
public:
	CommandFile(std::string path, std::string filename);

	void check();

	bool go();

	void copen();

	void cclose();

	bool run();
};

/////////////////////////////
///		Little docs for the CommandFiles:
/// 
/// ---Cout
/// #Syntax
/// Cout *text
/// 
/// #Extras
///   -br
/// addes an \r befor the text
///   -bn
/// addes an \n after the text
/// 
/// #info
/// this command ignores all \n and other \<letter>
/// 
/// ---Corr
/// #Syntax
/// Corr len
/// 
/// #info
/// this command prints random letters (len = count of all letters)
/// 
/// ---Cat
/// #Synatx
/// Cat *path
/// 
/// #Extras
///   -del
/// clears the file after reading it
///   -as
/// you use it as something
///   -as fvar <key>
/// searchs in the file for the var-key and return the value of it
/// 
/// #info
/// this command opens a file and print it
/// 
/// ---Ser
/// #Syntax
/// Ser *path
/// 
/// #Extras
///   -p
/// enables the path output
///   -s
/// enables the filesize output
///   -sl <from>:<to>
/// shows only files with a size between <from> and <to>
///   -f <filename>
/// shows only files with the name <filename>
/// 
/// #info
/// Prints all files in a dir + extra steps
/// 
/// ---info
/// >Working on<
/// 
/// 
/// 
 


#endif