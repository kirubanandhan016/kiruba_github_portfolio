#include "address_book.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void trim(char *s)
{
    size_t n = strlen(s);
    while (n && isspace((unsigned char)s[n-1])) s[--n] = '\0';
    size_t i = 0;
    while (isspace((unsigned char)s[i])) i++;
    if (i) memmove(s, s+i, strlen(s+i)+1);
}

static int read_line(const char *prompt, char *buf, size_t cap)
{
    printf("%s", prompt);
    if (!fgets(buf, (int)cap, stdin)) return 0;
    if (!strchr(buf, '\n'))
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    buf[strcspn(buf, "\n")] = '\0';
    trim(buf);
    return 1;
}

static int find_name(const AddressBook *b, const char *name)
{
    for (int i = 0; i < b->count; ++i)
        if (strcmp(b->items[i].name, name) == 0) return i;
    return -1;
}

void load_book(AddressBook *b, const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return;
    char line[256];
    while (b->count < MAX_CONTACTS && fgets(line, sizeof line, fp))
    {
        Contact c = {0};
        if (sscanf(line, "%63[^|]|%31[^|]|%95[^\n]",
                   c.name, c.phone, c.email) == 3)
            b->items[b->count++] = c;
    }
    fclose(fp);
}

int save_book(const AddressBook *b, const char *path)
{
    FILE *fp = fopen(path, "w");
    if (!fp) return 0;
    for (int i = 0; i < b->count; ++i)
        fprintf(fp, "%s|%s|%s\n", b->items[i].name,
                b->items[i].phone, b->items[i].email);
    fclose(fp);
    return 1;
}

void add_contact(AddressBook *b)
{
    if (b->count >= MAX_CONTACTS) { puts("Address book is full."); return; }
    Contact c = {0};
    if (!read_line("Name: ", c.name, sizeof c.name) || !c.name[0]) return;
    if (find_name(b, c.name) >= 0) { puts("Contact already exists."); return; }
    if (!read_line("Phone: ", c.phone, sizeof c.phone) || !c.phone[0]) return;
    if (!read_line("Email: ", c.email, sizeof c.email) || !c.email[0]) return;
    b->items[b->count++] = c;
    puts("Contact added.");
}

void search_contacts(const AddressBook *b)
{
    char q[NAME_LEN];
    if (!read_line("Search name: ", q, sizeof q) || !q[0]) return;
    int found = 0;
    for (int i = 0; i < b->count; ++i)
        if (strstr(b->items[i].name, q))
        {
            printf("%d. %s | %s | %s\n", i+1, b->items[i].name,
                   b->items[i].phone, b->items[i].email);
            found = 1;
        }
    if (!found) puts("No matching contact.");
}

void edit_contact(AddressBook *b)
{
    char name[NAME_LEN], buf[EMAIL_LEN];
    if (!read_line("Name to edit: ", name, sizeof name)) return;
    int i = find_name(b, name);
    if (i < 0) { puts("Contact not found."); return; }

    if (read_line("New phone: ", b->items[i].phone, sizeof b->items[i].phone) &&
        read_line("New email: ", buf, sizeof buf) && buf[0])
        strcpy(b->items[i].email, buf);
    puts("Contact updated.");
}

void delete_contact(AddressBook *b)
{
    char name[NAME_LEN];
    if (!read_line("Name to delete: ", name, sizeof name)) return;
    int i = find_name(b, name);
    if (i < 0) { puts("Contact not found."); return; }
    memmove(&b->items[i], &b->items[i+1],
            (size_t)(b->count - i - 1) * sizeof(Contact));
    b->count--;
    puts("Contact deleted.");
}

void list_contacts(const AddressBook *b)
{
    if (!b->count) { puts("No contacts."); return; }
    for (int i = 0; i < b->count; ++i)
        printf("%d. %s | %s | %s\n", i+1, b->items[i].name,
               b->items[i].phone, b->items[i].email);
}
