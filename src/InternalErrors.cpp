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

const char* NoMatchingVirtualPathError::what() const throw() {
	return "The given virtual path makes no sense";
}
const std::string NoMatchingVirtualPathError::toString() const {
	return "NoMatchingPathError";
}

const char* SyntaxError::what() const throw() {
	return "Found a Syntax error in a File!";
}
const std::string SyntaxError::toString() const {
	return "SyntaxError";
}

const char* ParserTagCantHaveAGetFunctionError::what() const throw() {
	return "A LangParse::Command::Arg with type \"ATAG\" cant have a get function!";
}
const std::string ParserTagCantHaveAGetFunctionError::toString() const {
	return "ParserTagCantHaveAGetFunctionError";
}


const char* ExpressionSyntaxError::what() const throw() {
	return "A Expression error was cought!";
}
const std::string ExpressionSyntaxError::toString() const {
	return "ExpressionSyntaxError";
}


const char* VariableAccessError::what() const throw() {
	return "You cant access that variable!";
}
const std::string VariableAccessError::toString() const {
	return "VariableAccessError";
}


const char* CommandNotFoundError::what() const throw() {
	return "Found an unknown Command!";
}
const std::string CommandNotFoundError::toString() const {
	return "CommandNotFoundError";
}

const char* BracesMisMatchError::what() const throw() {
	return "found a braces-mismatch in your file somewhere";
}
const std::string BracesMisMatchError::toString() const {
	return "BracesMisMatchError";
}

const char* TypeMissmatchError::what() const throw() {
	return "Wrong type given!";
}
const std::string TypeMissmatchError::toString() const {
	return "TypeMissmatchError";
}


const char* StringToIntCastError::what() const throw() {
	return "Failed to cast string to int!";
}
const std::string StringToIntCastError::toString() const {
	return "StringToIntCastError";
}

const char* ArrayOutOfRangeError::what() const throw() {
	return "The current Array is out of range!";
}
const std::string ArrayOutOfRangeError::toString() const {
	return "ArrayOutOfRange";
}

const char* ParametherMissmatchError::what() const throw() {
	return "The given paramether is not correct, this might happen because you gave an nullptr or something like that";
}
const std::string ParametherMissmatchError::toString() const {
	return "ParametherMissmatchError";
}