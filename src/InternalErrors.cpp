#include "InternalErrors.h"

const char* ValueNotFoundError::what() const throw() {
	return "The value is not in the file/input/...!";
}
const std::string ValueNotFoundError::toString() const {
	return "ValueNotFoundError";
}

const char* OpenFileError::what() const throw() {
	return "The programm couldn't open the requestet file!";
}
const std::string OpenFileError::toString() const {
	return "OpenFileError";
}

const char* MapIsNotStoragingError::what() const throw() {
	return "The used std::map hasn't the requested item!";
}
const std::string MapIsNotStoragingError::toString() const {
	return "MapIsNotStoragingError";
}

const char* ReadFileError::what() const throw() {
	return "The programm couldn't read the file, maybe it's not open?";
}
const std::string ReadFileError::toString() const {
	return "ReadFileError";
}

const char* DirMakeError::what() const throw() {
	return "The programm couldn't make the requested diktionarys. Maybe they are already there?";
}
const std::string DirMakeError::toString() const {
	return "DirMakeError";
}

const char* ResetFilesError::what() const throw() {
	return "The Programm coudn't open the files, maybe they are not existing?";
}
const std::string ResetFilesError::toString() const {
	return "ResetFilesError";
}

const char* MapIsAlreadyStoragingError::what() const throw() {
	return "The map storage the requested item already!";
}
const std::string MapIsAlreadyStoragingError::toString() const {
	return "MapIsAlreadyStoragingError";
}

const char* VecIsNotStoragingError::what() const throw() {
	return "The vector is not storaging the requested item!";
}
const std::string VecIsNotStoragingError::toString() const {
	return "VecIsNotStoragingError";
}

const char* FileIsAlreadyExistingError::what() const throw() {
	return "You want to re-create an existing file!";
}
const std::string FileIsAlreadyExistingError::toString() const {
	return "FileIsAlreadyExistingError";
}

const char* VecCantDeleteError::what() const throw() {
	return "The vector cant delete the requested item, it is mybe not storaging!";
}
const std::string VecCantDeleteError::toString() const {
	return "VecCantDeleteError";
}

const char* InvaildInputError::what() const throw() {
	return "Your input was incorrect!";
}
const std::string InvaildInputError::toString() const {
	return "InvaildInputError";
}

const char* DeleteDirError::what() const throw() {
	return "No such dir or no permissions to delete dictionary!";
}
const std::string DeleteDirError::toString() const {
	return "DeleteDirError";
}