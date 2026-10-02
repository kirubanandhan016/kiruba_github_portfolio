#include "address_book.h"
#include <stdio.h>

int main(void)
{
    AddressBook book = {0};
    const char *file = "contacts.txt";
    load_book(&book, file);

    for (;;)
    {
        int choice;
        printf("\n=== Address Book ===\n");
        printf("1. Add\n2. Search\n3. Edit\n4. Delete\n5. List\n6. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            puts("Invalid choice.");
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        switch (choice)
        {
            case 1: add_contact(&book); break;
            case 2: search_contacts(&book); break;
            case 3: edit_contact(&book); break;
            case 4: delete_contact(&book); break;
            case 5: list_contacts(&book); break;
            case 6:
                if (!save_book(&book, file)) {
                    fprintf(stderr, "Failed to save contacts.\n");
                    return 1;
                }
                return 0;
            default: puts("Choose 1-6.");
        }
    }
}
