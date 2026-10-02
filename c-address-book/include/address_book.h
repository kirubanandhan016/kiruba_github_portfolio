#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H
#define MAX_CONTACTS 200
#define NAME_LEN 64
#define PHONE_LEN 32
#define EMAIL_LEN 96

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

typedef struct {
    Contact items[MAX_CONTACTS];
    int count;
} AddressBook;

void load_book(AddressBook *book, const char *path);
int save_book(const AddressBook *book, const char *path);
void add_contact(AddressBook *book);
void search_contacts(const AddressBook *book);
void edit_contact(AddressBook *book);
void delete_contact(AddressBook *book);
void list_contacts(const AddressBook *book);
#endif
