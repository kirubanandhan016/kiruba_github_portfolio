# Address Book in C

A menu-driven C contact-management application with persistent file storage.

## Features
- Add contacts
- Search contacts
- Edit contacts
- Delete contacts
- Display all contacts
- Persistent CSV-like storage
- Basic validation
- Duplicate-name rejection

## Build
```bash
make
```

## Run
```bash
./addressbook
```

The data file defaults to `contacts.txt` in the working directory.

## Validation
Test cases include empty database, duplicate entries, missing contacts, invalid menu choices, empty names/numbers, and file errors.
