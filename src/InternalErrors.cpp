#include "InternalErrors.h"

const char* ValueNotFoundError::what() const throw() {
	return "The value is not in the file/input/...!";
}

const char* MapIsNotStoragingError::what() const throw() {
	return "The used std::map hasn't the requested item!";
}

const char* ReadFileError::what() const throw() {
	return "The programm couldn't read the file, maybe it's not open?";
}

const char* DirMakeError::what() const throw() {
	return "The programm couldn't make the requested diktionarys. Maybe they are already there?";
}

const char* ResetFilesError::what() const throw() {
	return "The Programm coudn't open the files, maybe they are not existing?";
}

const char* MapIsAlreadyStoragingError::what() const throw() {
	return "The map storage the requested item already!";
}

const char* VecIsNotStoragingError::what() const throw() {
	return "The vector is not storaging the requested item!";
}

const char* FileIsAlreadyExistingError::what() const throw() {
	return "You want to re-create an existing file!";
}

const char* VecCantDeleteError::what() const throw() {
	return "The vector cant delete the requested item, it is mybe not storaging!";
}

const char* InvaildInputError::what() const throw() {
	return "Your input was incorrect!";
}