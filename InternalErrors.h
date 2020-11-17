#ifndef INTERNAL_ERRORS_H
#define INTERNAL_ERRORS_H

#include <exception>

class ValueNotFoundErrorc : public std::exception
{
	public: virtual const char* what() const throw()
	{
		return "The value is not in the file/input/...!";
	}
	
} ValueNotFoundError;

class MapIsNotStoragingErrorc : public std::exception
{
	public: virtual const char* what() const throw()
	{
		return "The used std::map hasn't the requested item!";
	}
} MapIsNotStoragingError;

class ReadFileErrorc : public std::exception
{
	public: virtual const char* what() const throw()
	{
		return "The programm couldn't read the file, maybe it's not open?";
	}
} ReadFileError;
	
class DirMakeErrorc : public std::exception
{
	public: virtual const char* what() const throw()
	{
		return "The programm couldn't make the requested diktionarys. Maybe they are already there?";
	}
} DirMakeError;

class EventTriggerErrorc : public std::exception
{
	public: virtual const char* what() const throw()
	{
		return "The programm couldn't trigger the requested Event. Are you sure that you have triggert the right event?";
	}
} EventTriggerError;

class ResetFilesErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "The Programm coudn't open the files, maybe they are not existing?";
}
}ResetFilesError;

class MapIsAlreadyStoragingErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "The map storage the requested item already!";
}
}MapIsAlreadyStoragingError;

class InternalEventVecIsAlreadyStoragingErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "The vector is already storaging the requested item!";
}
}InternalEventVecIsAlreadyStoragingError;

class InternalEventVecIsNotStoragingErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "The vector is not storaging the requested item!";
}
}InternalEventVecIsNotStoragingError;

class FileIsAlreadyExistingErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "You want to re-create an existing file!";
}
}FileIsAlreadyExistingError;

class VecCantDeleteErrorc : public std::exception
{
public: virtual const char* what() const throw()
{
	return "The vector cant delete the requested item, it is mybe not storaging!";
}
}VecCantDeleteError;

#endif