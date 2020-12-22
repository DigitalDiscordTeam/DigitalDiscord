#ifndef INTERNAL_ERRORS_H
#define INTERNAL_ERRORS_H

#include <exception>

class ValueNotFoundError : public std::exception
{
	public: virtual const char* what() const throw();
	
};

class MapIsNotStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
};

class ReadFileError : public std::exception
{
	public: virtual const char* what() const throw();
};
	
class DirMakeError : public std::exception
{
	public: virtual const char* what() const throw();
};

class ResetFilesError : public std::exception
{
	public: virtual const char* what() const throw();
};

class MapIsAlreadyStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
};

class VecIsNotStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
};

class FileIsAlreadyExistingError : public std::exception
{
	public: virtual const char* what() const throw();
};

class VecCantDeleteError : public std::exception
{
	public: virtual const char* what() const throw();
};

class InvaildInputError : public std::exception
{
	public: virtual const char* what() const throw();
};

#endif