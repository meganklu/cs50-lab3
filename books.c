/**
 * books.c
 * Megan Lu
 * COSC050, 26S
 *
 * Description: organizes books and their information into a library
 * prints the library in a table
 * modifies the number of available copies of a book in the library
 * finds books written by a particular author
 *
 * Usage: books
 *
 * Exit: always exits with zero status
 * (program has no arguments and does not read from stdin).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilation flag for debugging (extra print statements of pointers, etc.)
#ifdef DEBUG
	#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINT(...)
#endif

// Global type and constant definitions
typedef struct {
	char* title; // book title
	char* author; // author name
	int year; // publication year
	char* isbn; // ISBN-13 lookup number
	int copies; // number of available copies
} Book;

typedef struct {
	Book* books; // array of Book structs 
	int size; // size of library
} Library;

Book books[] = {
        {"1984", "George Orwell", 1949, "9780451524935", 3},
        {"Animal Farm", "George Orwell", 1945, "9780451526342", 5},
        {"To Kill a Mockingbird", "Harper Lee", 1960, "9780061120084", 2},
        {"Pride and Prejudice", "Jane Austen", 1813, "9780141439518", 4},
        {"The Great Gatsby", "F. Scott Fitzgerald", 1925, "9780743273565", 3},
        {"Moby Dick", "Herman Melville", 1851, "9781503280786", 2},
        {"War and Peace", "Leo Tolstoy", 1869, "9781420954207", 1},
        {"The Catcher in the Rye", "J.D. Salinger", 1951, "9780316769488", 4},
        {"Brave New World", "Aldous Huxley", 1932, "9780060850524", 2},
        {"The Picture of Dorian Gray", "Oscar Wilde", 1890, "9780141439570", 5},
        {"The Hobbit", "J.R.R. Tolkien", 1937, "9780547928227", 6},
        {"Fahrenheit 451", "Ray Bradbury", 1953, "9781451673319", 3},
        {"The Odyssey", "Homer", -800, "9780140268867", 1},
        {"Gone with the Wind", "Margaret Mitchell", 1936, "9781451635621", 3},
        {"The Brothers Karamazov", "Fyodor Dostoevsky", 1880, "9780374528379", 2},
        {"Wuthering Heights", "Emily Brontë", 1847, "9781853260018", 4},
        {"Jane Eyre", "Charlotte Brontë", 1847, "9780374531553", 2},
        {"Crime and Punishment", "Fyodor Dostoevsky", 1866, "9780486457888", 1},
        {"The Grapes of Wrath", "John Steinbeck", 1939, "9780143039433", 3},
        {"The Kite Runner", "Khaled Hosseini", 2003, "9781594631930", 2},
        {"The Fault in Our Stars", "John Green", 2012, "9780525478812", 5},
    };


// Function prototypes
void displayBooks(Library library);
void addCopies(Library library, char isbn[], int copies);
Book* findByISBN(Library library, char isbn[]);
Library findByAuthor(Library library, char author[]);

/* ***************************
 * main
 */
int main() 
{
	// This is the size of the static books array, defined above
	int size = 21;
    
	Library library = {books, size};
	DEBUG_PRINT("library: %p\n", &library);
	DEBUG_PRINT("books: %p\n", &books);
	DEBUG_PRINT("books[2]: %p\n", &books[2]);

	displayBooks(library);

	// Add copies to "9781853260018" (Wuthering Heights)
	printf("\nAdd 3 copies to \"9781853260018\" (Wuthering Heights)\n");
	addCopies(library, "9781853260018", 3);
	displayBooks(library);

	// Add copies to book not in the library "9781982112820" (My Friends)
	printf("\nAdd 1 copy to \"9781982112820\" (My Friends)\n");
	addCopies(library, "9781982112820", 1);
	displayBooks(library);

	// Remove copies from "9780143039433" (The Grapes of Wrath) 
	// (remove fewer copies than initial)
        printf("\nAdd -2 (remove 2) copies from \"9780143039433\" (The Grapes of Wrath)\n");
        addCopies(library, "9780143039433", -2);
        displayBooks(library);

	// Remove copies from "9780525478812" (The Fault in Our Stars)
        // (remove exactly all copies)
        printf("\nAdd -5 (remove 5) copies from \"9780525478812\" (The Fault in Our Stars)\n");
        addCopies(library, "9780525478812", -5);
        displayBooks(library);

	// Remove copies from "9780141439518" (Pride and Prejudice)
        // (remove more copies than available)
        printf("\nAdd -5 (remove 5) copies from \"9780141439518\" (Pride and Prejudice)\n");
        addCopies(library, "9780141439518", -5);
        displayBooks(library);

	// Find books by "George Orwell"
	printf("\nFind books by \"George Orwell\"\n");
	Library orwell = findByAuthor(library, "George Orwell");
	DEBUG_PRINT("orwell: %p\n", &orwell);
	displayBooks(orwell);
	DEBUG_PRINT("orwell books: %p\n", orwell.books);
	free(orwell.books);

	// Find books by "F. Scott Fitzgerald"
	printf("\nFind books by \"F. Scott Fitzgerald\"\n");
	Library fitzgerald = findByAuthor(library, "F. Scott Fitzgerald");
	DEBUG_PRINT("fitzgerald: %p\n", &fitzgerald);
	displayBooks(fitzgerald);
	DEBUG_PRINT("fitzgerald books: %p\n", fitzgerald.books);
	free(fitzgerald.books);

	// Find books by "Megan Lu"
	printf("\nFind books by \"Megan Lu\"\n");
	Library lu = findByAuthor(library, "Megan Lu");
	DEBUG_PRINT("lu: %p\n", &lu);
	displayBooks(lu);
	DEBUG_PRINT("lu books: %p\n", lu.books);
	free(lu.books);

	return 0;
}

// Function definitions

/* *************************** 
 * displayBooks
 * Prints the details of each book of a library
 * in a readable table format for an 80-character window.
 * 
 * Assumptions:
 * 	Fields of the Book fit the following column sizes:
 * 	- year in a column for 4 digits
 * 	- ISBN in a column for 13 digits
 * 	- copies in a column for 9 digits
 * 
 * If the title or author name is greater than the column size
 * the text will wrap to an additional row.
 *
 * The spacing of the table will be maintained even if
 * title and author name contains wide characters
 * (e.g., ë in Brontë).
 */
void displayBooks(Library library)
{
	DEBUG_PRINT("displayBooks\n");
	DEBUG_PRINT("library: %p\n", &library);
        DEBUG_PRINT("books: %p\n", &books);
        DEBUG_PRINT("books[2]: %p\n", &books[2]);
	DEBUG_PRINT("library size: %d\n", library.size);

	// Column sizes
	int titleCol = 30;
	int authorCol = 20;
	int yearCol = 4;
	int isbnCol = 13;
	int copiesCol = 9;

	// Print table headers
	printf("%-*s %-*s %-*s %-*s %-*s\n",
			titleCol, "Title", 
			authorCol, "Author", 
			yearCol, "Year", 
			isbnCol, "ISBN", 
			copiesCol, "Copies");
	for (int i = 0; i < titleCol; i++) {
		printf("-");
	}
	printf(" ");
	for (int i = 0; i < authorCol; i++) {
		printf("-");
	}
	printf(" ");
	for (int i = 0; i < yearCol; i++) {
		printf("-");
	}
	printf(" ");
	for (int i = 0; i < isbnCol; i++) {
		printf("-");
	}
	printf(" ");
	for (int i = 0; i < copiesCol; i++) {
		printf("-");
	}
	printf("\n");

	// Loop through books in the library's array
	for (int i = 0; i < library.size; i++) {
		// Access each field for the book and print row
		/* printf("%-*s %-*s %-*d %-*s %-*d\n",
                        titleCol, book.title,
                        authorCol, book.author,
                        yearCol, book.year,
                        isbnCol, book.isbn,
                        copiesCol, book.copies); */

		// Keep adding rows for the entry until all info displayed
		// Track current character of title and author
		char* currentTitleChar = library.books[i].title;
		char* currentAuthorChar = library.books[i].author;

		int row = 0;
		while (*currentTitleChar != '\0' || *currentAuthorChar != '\0') {
			// Add the next characters of the title to fill the column
			int charAdded = 0;
			while (charAdded < titleCol 
					&& *currentTitleChar != '\0') {
				// Add the character and update the pointer
				printf("%c", *currentTitleChar);
				currentTitleChar++; // Next character in string
				charAdded++;
			}

			// Add author name next
                        // Add the next characters of the author name
                        // to fill the column
                        // Start by carriage returning to the start of the row
			// then move cursor to start of the author column
			// to avoid potential spacing issues 
			// when there is a wide character
			printf("\r\033[%dC", (titleCol + 1)); 
			charAdded = 0;
                        while (charAdded < authorCol && *currentAuthorChar != '\0') {
                                // Add the character and update the pointer
                                printf("%c", *currentAuthorChar);
                                currentAuthorChar++; // Next character in string
                                charAdded++;
                        }

			// Add rest of information 
			// only if in the first row (row 0)
                        // Carriage return to start of line then move cursor
                        // past the title and author name columns
                        // to avoid potential spacing issues 
			// when there is a wide character
                        // e.g., ë in Brontë
                        if (row == 0) {
                                // Carriage return then move forward in the line 
				// (enough to title column, author column,
                                // and space between columns)
                                printf("\r\033[%dC%-*d %-*s %*d",
						(titleCol + 1
                                                + authorCol + 1),
                                                yearCol, library.books[i].year,
                                                isbnCol, library.books[i].isbn,
                                                copiesCol, library.books[i].copies);
				DEBUG_PRINT(" %p", &library.books[i]);
                        }

			printf("\n");
			row++;
		}
	}
}

/* ***************************
 * addCopies
 * Given a library and an ISBN of a book,
 * adds the specified number of copies.
 * 
 * Copies are not added and the library is not modified
 * if a book with the provided ISBN does not exist or is invalid.
 *
 * If the copies parameter is negative, the number of available copies
 * for the book will be decreased by that amount until zero.
 * i.e., The lowest number of available copies is zero. If the absolute
 * value of the negative copies parameter is greater than the book's
 * current copies value, the number of available copies will be set to 0.
 *
 * Assumptions:
 * 	The ISBN is a 13 character string of numbers in the form:
 * 	"XXXXXXXXXXXXX" (no dashes, extra punctuation, etc.)
 * 	Only one book in the library has the given ISBN.
 * 	The number of copies being added is a positive integer.
 */
void addCopies(Library library, char isbn[], int copies)
{
	DEBUG_PRINT("addCopies\n");
	DEBUG_PRINT("library: %p\n", &library);
        DEBUG_PRINT("books: %p\n", &books);
        DEBUG_PRINT("books[2]: %p\n", &books[2]);

	Book* book = findByISBN(library, isbn);
	
	// Check if book with the given ISBN was returned
	if (book != NULL) {
		// Increment the number of copies
		book->copies += copies;
		
		// Check if copies is now a negative number (invalid, set to 0)
		if (book->copies < 0) {
			book->copies = 0;
		}
	}
}

/* ***************************
 * findByISBN
 * Finds the book in the library with the given ISBN.
 *
 * Assumptions:
 * 	The ISBN is a valid 13 character string of numbers.
 * 	Only one book in the library has the given ISBN.
 *
 * Return value:
 * 	Returns a pointer to the Book struct with the given ISBN.
 * 	Returns NULL if no book in the library has a matching ISBN.
 */
Book* findByISBN(Library library, char isbn[])
{
	DEBUG_PRINT("findByISBN\n");
	// Loop the books in the library
	for (int i = 0; i < library.size; i++) {
		// Check if the book matches the given ISBN
		if (strcmp(library.books[i].isbn, isbn) == 0) {
			// Exact match (strings are identical)
			// Return the address to this book
			DEBUG_PRINT("book with ISBN %s: %p\n", isbn, &library.books[i]);
			return &library.books[i];
		}
	}
	// No matching ISBN found, return NULL
	DEBUG_PRINT("no book with ISBN %s found\n", isbn);
	return NULL;
}

/* ***************************
 * findByAuthor
 * Finds the books in the library by written by an author
 * provided the author's name as a parameter and the library.
 *
 * Assumptions:
 * 	The name provided exactly matches the author's name in the library.
 *
 * Return value:
 * 	Returns a Library struct containing an array of the Book structs
 * 	written by the author.
 * 	The Book structs will be a copy of the original Book structs in
 * 	the parameter library's array of books.
 *	
 *	If no books in the library were written by the input author,
 *	the Library struct will have a size of 0.
 *	
 *	If there is an error (e.g., unable to allocate memory for the 
 *	array of books), the Library will have a size of -1 and
 *	the array will point to NULL.
 *
 * Caller is responsible for freeing the memory allocated for the
 * array of Book struct in the Library struct returned
 * (i.e., the caller must free the pointer to the first element 
 * in the array of books).
 */
Library findByAuthor(Library library, char author[])
{
	DEBUG_PRINT("findByAuthor\n");
	DEBUG_PRINT("library: %p\n", &library);
        DEBUG_PRINT("books: %p\n", &books);
        DEBUG_PRINT("books[2]: %p\n", &books[2]);

	// Allocate memory in the heap for an array of Book structs
	// Maximum size of the array is the size of the parameter library's array
	Book* authorBooks = malloc(sizeof(Book) * library.size);
	DEBUG_PRINT("authorBooks: %p\n", authorBooks);
	// Failed to allocate memory
	if (authorBooks == NULL) {
		return (Library) {NULL, -1};
	}

	// Track the number of books added to the array
	int authorSize = 0;

	// Loop through the parameter library
	for (int i = 0; i < library.size; i++) {
		// Check if the book was written by the parameter author
		if (strcmp(library.books[i].author, author) == 0) {
                        // Exact match (strings are identical)
                        // Add the book to the new array
                        DEBUG_PRINT("book with author %s: %p\n", author, &library.books[i]);
                        authorBooks[authorSize] = library.books[i];
			authorSize++;
                }
	}

	// Return Library struct with completed array
	return (Library) {authorBooks, authorSize};
}
