#include "contact.h"
#include "file.h"
// Function to save all contacts from the AddressBook into a file (contacts.csv)
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr ;
    fptr = fopen("contacts.csv", "w"); // Open file in write mode (overwrite existing content)
    if (fptr == NULL) {
        printf("Error saving contacts.\n");
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }
    //write the contact count in a file
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Write each contact in CSV format: name,phone,email
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr); // Close the file after saving
}


// Function to load all contacts from the file (contacts.csv) into the AddressBook
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "r"); // Open file in read mode
    if (fptr == NULL) {
        printf("Error load contacts.\n");
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }
     //read the contactcount value
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    // Read each contact in CSV format and store into AddressBook
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr); // Close the file after loading
}
