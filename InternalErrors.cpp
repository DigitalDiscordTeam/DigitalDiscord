#include "InternalErrors.h"

const char* ValueNotFoundErrorc::what() const throw() {
	return "The value is not in the file/input/...!";
}

const char* MapIsNotStoragingErrorc::what() const throw() {
		return "The used std::map hasn't the requested item!";
}

const char* ReadFileErrorc::what() const throw() {
	return "The programm couldn't read the file, maybe it's not open?";
}

const char* DirMakeErrorc::what() const throw() {
	return "The programm couldn't make the requested diktionarys. Maybe they are already there?";
}

const char* ResetFilesErrorc::what() const throw() {
	return "The Programm coudn't open the files, maybe they are not existing?";
}

const char* MapIsAlreadyStoragingErrorc::what() const throw() {
	return "The map storage the requested item already!";
}

const char* InternalEventVecIsAlreadyStoragingErrorc::what() const throw() {
	return "The vector is already storaging the requested item!";
}

const char* VecIsNotStoragingErrorc::what() const throw() {
	return "The vector is not storaging the requested item!";
}

const char* FileIsAlreadyExistingErrorc::what() const throw() {
	return "You want to re-create an existing file!";
}

const char* VecCantDeleteErrorc::what() const throw() {
	return "The vector cant delete the requested item, it is mybe not storaging!";
}

const char* InvaildInputErrorc::what() const throw() {
	return "Your paramether was incorrect!";
}