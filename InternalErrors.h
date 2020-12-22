#ifndef INTERNAL_ERRORS_H
#define INTERNAL_ERRORS_H

#include <exception>

class ValueNotFoundErrorc : public std::exception
{
	public: virtual const char* what() const throw();
	
} ValueNotFoundError;

class MapIsNotStoragingErrorc : public std::exception
{
	public: virtual const char* what() const throw();
} MapIsNotStoragingError;

class ReadFileErrorc : public std::exception
{
	public: virtual const char* what() const throw();
} ReadFileError;
	
class DirMakeErrorc : public std::exception
{
	public: virtual const char* what() const throw();
} DirMakeError;

class ResetFilesErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}ResetFilesError;

class MapIsAlreadyStoragingErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}MapIsAlreadyStoragingError;

class InternalEventVecIsAlreadyStoragingErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}InternalEventVecIsAlreadyStoragingError;

class VecIsNotStoragingErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}VecIsNotStoragingError;

class FileIsAlreadyExistingErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}FileIsAlreadyExistingError;

class VecCantDeleteErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}VecCantDeleteError;

class InvaildInputErrorc : public std::exception
{
	public: virtual const char* what() const throw();
}InvaildInputError;

#endif