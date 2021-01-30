#ifndef INTERNAL_ERRORS_H
#define INTERNAL_ERRORS_H

#include <exception>
#include <string>

class ValueNotFoundError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class OpenFileError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class MapIsNotStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class ReadFileError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};
	
class DirMakeError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class ResetFilesError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class MapIsAlreadyStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class VecIsNotStoragingError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class FileIsAlreadyExistingError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class VecCantDeleteError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class InvaildInputError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

class DeleteDirError : public std::exception
{
	public: virtual const char* what() const throw();
	const std::string toString() const;
};

#endif