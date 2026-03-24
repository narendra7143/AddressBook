#include "contact.h"
#include "file.h"
//name validation only letters & spaces allowed
int validname(char * name)
{
   for(int i=0;name[i]!='\0';i++)//chech upto null character
   {
      if(!isalpha(name[i])&&name[i]!=' ' && name[i]!='.')
      return 0;//invalid name(digits are special characters)
   }
    return 1;//valid name
}
//phone validation only digits allowed
int validphone(char * phone)
{
    int len=strlen(phone);//fing length of phone
     if(len!=10)
    {
     return -1;//invalid if numbers len not equals to 10
    }
     for (int i = 0; i < len; i++)//
      {
        if (isspace(phone[i])) 
            return -1; // invalid if space found
      }
   
   for(int i=0;phone[i]!='\0';i++)
   {
      if(!isdigit(phone[i]))
      return 0;//invalid if the number not a digit
   }
    return 1;//valid phone
}
//email validation only lowercase letters must and should one @ and one .com
int validemail(char *email)
{int atPos = -1, dotPos = -1;//declare initially (@) and (.) positions are -1
    int len = strlen(email);//find length of email

    for (int i = 0; i < len; i++) 
    {
        if (!(islower(email[i]) || isdigit(email[i]) || email[i]=='@' || email[i]=='.' || email[i]=='_'))
            return -1;//must lower case letters

        if (email[i] == '@') atPos = i;
        if (email[i] == '.') dotPos = i;
    }

     // Must have @ and .
    if (atPos <= 0 || dotPos < atPos) return 0;

    // At least one character between @ and .
    if (dotPos - atPos <= 1) return 0;

    if (len <4 || strcmp(email + len - 4, ".com") != 0) return 0;//must last four letters .com only

    return 1;//valid email 
}
//list all contacts
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }

    // Sort contacts alphabetically by name
    Contact temp;
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\n--------------------------------CONTACTS LIST-------------------------------\n");
    printf("\n----------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-25s |\n", "No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------\n");

    // Print contact list
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-3d | %-20s | %-15s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("----------------------------------------------------------------------------\n");
}
// Initialize from file (load saved contacts)
void initialize(AddressBook *addressBook)
{
    loadContactsFromFile(addressBook);
}
// Save contacts to file and exit
void saveAndExit(AddressBook *addressBook)
{
   saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

// Function to create a new contact and add it to the address book
void createContact(AddressBook *addressBook)
{
    // Check if the address book is full (max 100 contacts)
    if (addressBook->contactCount >= 100)
    {
        printf("Address Book is full\n");
        return;
    }

    // Temporary variables to store user input
    char name[50], phone[20], email[50];
    int flag1 = 0, flag2 = 0, flag3 = 0; // Validation flags initially all 0s

    // --- NAME INPUT ---
    do
    {
        printf("Enter name: ");
        scanf(" %[^\n]", name); // Read full line input

        int checkname = validname(name); // Validate name
        if (checkname == 0)
        {
            printf("Invalid name! Only letters and spaces allowed.\n");
        }
        else
        {
            break; // Exit loop if valid
        }
    } while (flag1 == 0); // Loop until valid name is entered

    // --- PHONE INPUT ---
    do
    {
        printf("Enter phone: ");
        scanf(" %[^\n]", phone);

        int checkphone = validphone(phone); // Validate phone number
        if (checkphone == -1)
        {
            printf("Invalid phone! Must be 10 digits.\n");
        }
        else if (checkphone == 0)
        {
            printf("Invalid phone! Only digits allowed.\n");
        }
        else
        {
            // Check for duplicate phone numbers
            int duplicate = 0;
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate)
                printf("Phone already exists! Enter another.\n");
            else
                flag2 = 1; // Valid and unique phone
        }
    } while (flag2 == 0);

    // --- EMAIL INPUT ---
    do
    {
        printf("Enter email: ");
        scanf(" %[^\n]", email);

        int checkemail = validemail(email); // Validate email id
        if (checkemail == 0)
        {
            printf("Invalid email! Must contain '@' and '.' properly.\n");
        }
        else if(checkemail==-1)
        {
            printf("Invalid email! only lower case letters.\n");
        }
        else
        {
            // Check for duplicate email
            int duplicate = 0;
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate)
                printf("Email already exists! Enter another.\n");
            else
                flag3 = 1; // Valid and unique email
        }
    } while (flag3 == 0);

    // Add the validated details into the contact list
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    // Increase contactcount
    addressBook->contactCount++;

    printf("------Contact successfully added!------\n");
}
// Function to search for a contact by name, phone, or email
void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to search.\n");
        return;
    }

    char searchname[50], searchphone[20], searchemail[50];
    int choice;

    printf("\n========== SEARCH MENU ==========\n");
    printf("1. Search by name\n2. Search by phone\n3. Search by email\n");
    printf("---------------------------------\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", searchname);
    }
    else if (choice == 2)
    {
        printf("Enter phone: ");
        scanf(" %[^\n]", searchphone);
    }
    else if (choice == 3)
    {
        printf("Enter email: ");
        scanf(" %[^\n]", searchemail);
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    int found = 0;

    printf("\n----------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-25s |\n", "No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char tempName[50], tempSearch[50];

        strcpy(tempName, addressBook->contacts[i].name);
        strcpy(tempSearch, searchname);

        // lowercase conversion
        for(int k=0; tempName[k]; k++) tempName[k] = tolower(tempName[k]);
        for(int k=0; tempSearch[k]; k++) tempSearch[k] = tolower(tempSearch[k]);

        if ((choice == 1 && strstr(tempName, tempSearch) != NULL) ||
            (choice == 2 && strstr(addressBook->contacts[i].phone, searchphone) != NULL) ||
            (choice == 3 && strstr(addressBook->contacts[i].email, searchemail) != NULL))
        {
            printf("| %-3d | %-20s | %-15s | %-25s |\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found++;
        }
    }

    printf("----------------------------------------------------------------------------\n");

    if (found == 0)
        printf("No matching contacts found.\n");
    else
        printf("%d contact(s) found.\n", found);
}
// Function to edit saved contacts by searching

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to edit.\n");
        return;
    }

    char searchname[50], searchphone[20], searchemail[50];
    int choice;

    printf("\n--- Edit Contact Menu ---\n");
    printf("1. Edit by name\n2. Edit by phone\n3. Edit by email\n");
    printf("-----------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear buffer

    // Get search input
    if (choice == 1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", searchname);
    }
    else if (choice == 2)
    {
        printf("Enter the phone: ");
        scanf(" %[^\n]", searchphone);
    }
    else if (choice == 3)
    {
        printf("Enter the email: ");
        scanf(" %[^\n]", searchemail);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    // Show matching contacts
    int found = 0;
    int matchedIndices[100]; // store indices of matched contacts

    printf("\n----------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-25s |\n", "S.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
{
    char tempName[50], tempSearch[50];

    strcpy(tempName, addressBook->contacts[i].name);
    strcpy(tempSearch, searchname);

    for(int k=0; tempName[k]; k++) tempName[k] = tolower(tempName[k]);
    for(int k=0; tempSearch[k]; k++) tempSearch[k] = tolower(tempSearch[k]);

    if ((choice == 1 && strstr(tempName, tempSearch) != NULL) ||
        (choice == 2 && strstr(addressBook->contacts[i].phone, searchphone) != NULL) ||
        (choice == 3 && strstr(addressBook->contacts[i].email, searchemail) != NULL))
    {
        matchedIndices[found] = i;

        printf("| %-3d | %-20s | %-15s | %-25s |\n",
               found + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        found++;
    }
}

    printf("----------------------------------------------------------------------------\n");

    if (found == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }

    // Ask user which contact to edit
    int select;
    printf("\n%d contact(s) found.\n", found);
    printf("Enter the number (S.No) of the contact you want to edit (0 to cancel): ");
    scanf("%d", &select);
    getchar();

    if (select == 0)
    {
        printf("Edit operation cancelled.\n");
        return;
    }
    if (select < 1 || select > found)
    {
        printf("Invalid selection.\n");
        return;
    }

    // Get selected contact index
    int i = matchedIndices[select - 1];

    printf("\nCurrent Details:\n");
    printf("-------------------------------------------------------------\n");
    printf("Name : %s\n", addressBook->contacts[i].name);
    printf("Phone: %s\n", addressBook->contacts[i].phone);
    printf("Email: %s\n", addressBook->contacts[i].email);
    printf("-------------------------------------------------------------\n");

    int editChoice;
    char newname[50], newphone[20], newemail[50];

    printf("1. Edit name\n2. Edit phone\n3. Edit email\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);
    getchar();

    // --- Edit Name ---
    if (editChoice == 1)
    {
        printf("Enter new name: ");
        scanf(" %[^\n]", newname);
        if (validname(newname))
        {
            strcpy(addressBook->contacts[i].name, newname);
            printf("Name updated successfully!\n");
        }
        else
            printf("Invalid name!\n");
    }
    // --- Edit Phone ---
    else if (editChoice == 2)
    {
        printf("Enter new phone: ");
        scanf(" %[^\n]", newphone);
        if (validphone(newphone))
        {
            int duplicate = 0;
            for (int j = 0; j < addressBook->contactCount; j++)
            {
                if (j != i && strcmp(addressBook->contacts[j].phone, newphone) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate)
            {
                strcpy(addressBook->contacts[i].phone, newphone);
                printf("Phone updated successfully!\n");
            }
            else
                printf("Phone already exists!\n");
        }
        else
            printf("Invalid phone!\n");
    }
    // --- Edit Email ---
    else if (editChoice == 3)
    {
        printf("Enter new email: ");
        scanf(" %[^\n]", newemail);
        if (validemail(newemail))
        {
            int duplicate = 0;
            for (int j = 0; j < addressBook->contactCount; j++)
            {
                if (j != i && strcmp(addressBook->contacts[j].email, newemail) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate)
            {
                strcpy(addressBook->contacts[i].email, newemail);
                printf("Email updated successfully!\n");
            }
            else
                printf("Email already exists!\n");
        }
        else
            printf("Invalid email!\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }

    // Show updated contact
    printf("\nUpdated Contact Details:\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-25s |\n", "S.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------\n");
    printf("| %-3d | %-20s | %-15s | %-25s |\n",
           i + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
    printf("----------------------------------------------------------------------------\n");
}


// Function to delete a contact by searching name/phone/email
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to delete.\n");
        return;
    }

    char searchname[50], searchphone[20], searchemail[50];
    int choice;

    printf("\n--- Delete Contact Menu ---\n");
    printf("1. Delete by name\n2. Delete by phone\n3. Delete by email\n");
    printf("---------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    // Get search input
    if (choice == 1)
    {
        printf("Enter the name of the contact to delete: ");
        scanf(" %[^\n]", searchname);
    }
    else if (choice == 2)
    {
        printf("Enter the phone of the contact to delete: ");
        scanf(" %[^\n]", searchphone);
    }
    else if (choice == 3)
    {
        printf("Enter the email of the contact to delete: ");
        scanf(" %[^\n]", searchemail);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    int found = 0;
    int matchedIndices[100]; // To store matched contact indices

    // Display header
    printf("\n----------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-25s |\n", "S.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------\n");

    // Find matches

for (int i = 0; i < addressBook->contactCount; i++)
{
    char tempName[50], tempSearch[50];

    strcpy(tempName, addressBook->contacts[i].name);
    strcpy(tempSearch, searchname);

    for(int k=0; tempName[k]; k++) tempName[k] = tolower(tempName[k]);
    for(int k=0; tempSearch[k]; k++) tempSearch[k] = tolower(tempSearch[k]);

    if ((choice == 1 && strstr(tempName, tempSearch) != NULL) ||
        (choice == 2 && strstr(addressBook->contacts[i].phone, searchphone) != NULL) ||
        (choice == 3 && strstr(addressBook->contacts[i].email, searchemail) != NULL))
    {
        matchedIndices[found] = i;

        printf("| %-3d | %-20s | %-15s | %-25s |\n",
               found + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        found++;
    }
}
    printf("----------------------------------------------------------------------------\n");

    if (found == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }

    // If multiple matches, ask user which one to delete
    int select;
    printf("\n%d contact(s) found.\n", found);
    printf("Enter the number (S.No) of the contact you want to delete (0 to cancel): ");
    scanf("%d", &select);
    getchar();

    if (select == 0)
    {
        printf("Delete operation cancelled.\n");
        return;
    }
    if (select < 1 || select > found)
    {
        printf("Invalid selection.\n");
        return;
    }

    // Get actual contact index
    int delIndex = matchedIndices[select - 1];

    // Show contact being deleted
    printf("\nDeleting Contact:\n");
    printf("-------------------------------------------------------------\n");
    printf("Name : %s\n", addressBook->contacts[delIndex].name);
    printf("Phone: %s\n", addressBook->contacts[delIndex].phone);
    printf("Email: %s\n", addressBook->contacts[delIndex].email);
    printf("-------------------------------------------------------------\n");

    // Shift remaining contacts left
    for (int j = delIndex; j < addressBook->contactCount - 1; j++)
    {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}

