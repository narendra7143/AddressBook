/*===AddressBook Project===
NAME:D.Narendra Kumar
DATE:17-09-2025
DESCRIPTION:To store the contact details like name,phone and email.*/

#include "contact.h"
#include "file.h"
int main()
{
    int  choice;//declare integer variable
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
//using do while without checking condition we can print atleast once
    do
    {
        printf("||-----------------------------||\n");
        printf("||------Address Book Menu------||\n");
        printf("||-----------------------------||\n");
        printf("||  1.  Create contact         ||\n");
        printf("||  2.  Search contact         ||\n");
        printf("||  3.  Edit contact           ||\n");
        printf("||  4.  Delete contact         ||\n");
        printf("||  5.  List all contacts      ||\n");
        printf("||  6.  Save contacts          ||\n");
        printf("||  7.  Exit                   ||\n");
        printf("||-----------------------------||\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);//read user choice
        switch (choice)//using swith case to directly go to matced location
        {
        case 1:
            createContact(&addressBook);//function call for create contact
            break;
        case 2:
            searchContact(&addressBook);//function call for search contact
            break;
        case 3:
            editContact(&addressBook);//function call for edit contact
            break;
        case 4:
            deleteContact(&addressBook);//function call for delete contact
            break;
        case 5:
            listContacts(&addressBook);//function call for list contact
            break;
        case 6:
            printf("Saving...\n");
             saveContactsToFile(&addressBook);//function call for save contact
            break;
        case 7://exit from the loop
               break;
        default:
            printf("Invalid choice. Please try again.\n");//if any choice not matched print default statement
        }
    } while (choice != 7);
   
    return 0;
}
