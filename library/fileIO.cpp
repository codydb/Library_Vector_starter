#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char comma = ",";

/*Parse strings to ints
 */
int strToInt(const string &str) {
	stringstream ssInt(str);
	int num;
	ssInt >> num;
	return num;
}

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	books.clear();
	fstream myfstream;
	myfstream.open(filename, ios::out);

	if (!myfstream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (myfstream.eof()) {
		return NO_BOOKS_IN_LIBRARY;
	}

	std::string fileLine = "";

	while (getline(myfstream, fileLine)) {

		book tempBook;
		std::stringstream ss(fileLine);
		std::string tempToken;

		getline(ss, tempToken, comma);
		tempBook.book_id = strToInt(tempToken);
		getline(ss, tempToken, comma);
		tempBook.title = tempToken;
		getline(ss, tempToken, comma);
		tempBook.author = tempToken;
		getline(ss, tempToken, comma);
		tempBook.state = strToInt(tempToken);
		getline(ss, tempToken, comma);
		tempBook.loaned_to_patron_id = strToInt(tempToken);

		books.push_back(tempBook);
	}
	myfstream.close();

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	if (books.empty()) {
		return NO_BOOKS_IN_LIBRARY;
	}

	fstream myfstream;

	myfstream.open(filename, ios::in);

	if (!myfstream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	std::vector<book>::iterator bookItr;

	for (bookItr = books.begin(); bookItr != books.end(); bookItr++) {

		myfstream
				<< (*bookItr).book_id + comma + (*bookItr).author + comma
						+ (*bookItr).author + comma + (*bookItr).state + comma
						+ (*bookItr).loaned_to_patron_id + "\n";
	}

	myfstream.close();

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	patrons.clear();
	fstream myfstream;
	myfstream.open(filename, ios::out);

	if (!myfstream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (myfstream.eof()) {
		return NO_PATRONS_IN_LIBRARY;
	}

	std::string fileLine = "";
	while (getline(myfstream, fileLine)) {

		patron tempPatron;
		std::stringstream ss(fileLine);
		std::string tempToken;

		getline(ss, tempToken, comma);
		tempPatron.patron_id = strToInt(tempToken);
		getline(ss, tempToken, comma);
		tempPatron.name = tempToken;
		getline(ss, tempToken, comma);
		tempPatron.number_books_checked_out = strToInt(tempToken);

		patrons.push_back(tempPatron);

	}

	myfstream.close();

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	if (patrons.empty()) {
		return NO_PATRONS_IN_LIBRARY;
	}

	fstream myfstream;

	myfstream.open(filename, ios::in);

	if (!myfstream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	std::vector<patron>::iterator patItr;

	for (patItr = patrons.begin(); patItr != patrons.end(); patItr++) {

		myfstream
				<< (*patItr).patron_id + comma + (*patItr).name + comma
						+ (*patItr).number_books_checked_out + "\n";
	}

	myfstream.close();
	return SUCCESS;
}
