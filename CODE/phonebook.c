// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// Defined or constant values
#define MAX_INPUT 10
#define MAX_LENGTH 100
#define MAX_KB 1024

// Storage to store contact info
char name[MAX_LENGTH];
char number[MAX_LENGTH];
char res_number[MAX_LENGTH];
char office_number[MAX_LENGTH];
char email[MAX_LENGTH];


// Function Prototype
bool check_name(char *person_name);
bool check_num(char *person_num);
bool check_res(char *person_res_num);
bool check_office(char *person_office_num);
bool check_email(char *person_email);

// strtok function prototype
char *strtok_r(char *str, const char *delim, char **saveptr);

// Main
int main(int argc, char *argv[])
{
    // Storage to store user input
    char input[MAX_INPUT];

    // Welcome screen
    printf("*****************************************************************\n");
    printf("                    WELCOME TO PHONEBOOK\n\n");
    printf("          Software Developed By: Syed Shehroz Ali\n");
    printf("*****************************************************************\n");
    printf("    1. Open Phonebook     2.Create New Contact     3.Find Contact\n");
    printf("*****************************************************************\n");
    printf("                        What do you want to do?\n");
    printf("                1.Open      2.Create        3.Find\n");
    // Prompt for user input
    scanf("                                             %s", input);

    // Strings
    char *string[] = {"open", "create", "find"};

    // If input is read or write
    if (strcmp(input, string[0]) == 0 || strcmp(input, string[1]) == 0 || strcmp(input, string[2]) == 0)
    {
        // If input is read
        if(strcmp(input, string[0]) == 0)
        {
            // Open file in read mode
            FILE *fp = fopen("phonebook.csv", "r");

                if (fp == NULL)
                {
                    printf("File not created yet/not present.\n");
                    return 1;
                }

            // Storage to store input 1024 bytes
            char buffer[MAX_KB];

            // Loop till end of the file
            while(fgets(buffer, 100, fp))
            {
                printf("%s", buffer);
            }

            // End
            return 0;
        }

        // If input is write
        if (strcmp(input, string[1]) == 0)
        {
            FILE *fp = fopen("phonebook.csv", "a");

                if (fp == NULL)
                {
                    printf("Error opening file for writing contact...\n");
                    return 2;
                }

            // Start writing new contact
            printf("NEW CONTACT\n\n");

            // Check name (if invalid prompt again)
            printf("Name of person:  ");
            do
            {
                scanf("%s", name);
            }
            while (!check_name(name));

            // Check number (if invalid prompt again)
            printf("Number of person:  ");
            do
            {
                scanf("%s", number);
            }
            while (!check_num(number));

            // Check residential number (if invalid prompt again)
            printf("Residential Number:  ");
            do
            {
                scanf("%s", res_number);
            }
            while (!check_res(res_number));

            // Check office number (if invalid prompt again)
            printf("Office Number:  ");
            do
            {
                scanf("%s", office_number);
            }
            while (!check_office(office_number));

            // Check email id (if invalid prompt again)
            printf("Email:  ");
            do
            {
                scanf("%s", email);
            }
            while (!check_email(email));

            // Check if file is empty or not
            fseek(fp, 0, SEEK_END);
            long int res = ftell(fp);

            // If file is empty
            if (res == 0)
            {
                fprintf(fp, "PHONEBOOK MANAGEMENT SOFTWARE (Developed By Shahroz Ali)\n\n\n");
                fprintf(fp, "Name, Number, Residential Number, Office Number, Email ID\n");
                fprintf(fp, "%s, %s, %s, %s, %s\n", name, number, res_number, office_number, email);

                // Done
                printf("\n\n---| CONTACT CREATED |---\n");
                printf("Name: %s\n", name);
                printf("Number: %s\n", number);
                printf("Res Number: %s\n", res_number);
                printf("Office Number: %s\n", office_number);
                printf("Email: %s\n", email);
                printf("Success\n");

                fclose(fp);
                return 0;
            }

            // If file is already open or has data stored
            if (res != 0)
            {
                fprintf(fp, "%s, %s, %s, %s, %s\n", name, number, res_number, office_number, email);

                // Done
                printf("\n\n---| CONTACT CREATED |---\n");
                printf("Name: %s\n", name);
                printf("Number: %s\n", number);
                printf("Res Number: %s\n", res_number);
                printf("Office Number: %s\n", office_number);
                printf("Email: %s\n", email);
                printf("Success\n");

                fclose(fp);
                return 0;
            }

        }

        // If input is find
        if (strcmp(input, string[2]) == 0)
        {
            // Storage to store contact name for searching
            char find_name[] = "";

            // Prompt for contact name
            printf("Search Name: ");
            scanf("%s", find_name);

            // Open file in read mode
            FILE *fp = fopen("phonebook.csv", "r");

            if (fp == NULL)
            {
                printf("Error opening the file for searching\n");
                return 1;
            }

            // Storage for existing contact name in the .CSV file
            char search[MAX_LENGTH];

            // Loop till EOF
            while (fgets(search, 100, fp))
            {
                // Assign read data to new string
                char *rest = search;

                // String to store new token
                char *token;

                // Loop till delimiter (,)
                while ((token = strtok_r(rest, ",", &rest)))
                {
                    // If name matches
                    if (strcmp(find_name, token) == 0)
                    {
                        // Print contact exists
                        printf("Contact Exists.\n");
                        return 0;
                    }
                }
            }

            // In case contact doesn't exists
            printf("Contact doesn't exists.\n");

            // Closes *fp, end program
            fclose(fp);
            return 1;
        }
    }

    // If input is not correct
    else
    {
        printf("Not correct input\n\n");
        return 1;
    }
}

// Function to check valid name
bool check_name(char *person_name)
{
    for (int i = 0; i < strlen(person_name); i++)
    {
        if (!isalpha(person_name[i]))
        {
            printf("Invalid Name...Type again\n");
            return false;
        }
    }

    return true;
}

// Function to check valid number
bool check_num(char *person_num)
{
    for (int i = 0; i < strlen(person_num); i++)
    {
        if (!isdigit(person_num[i]))
        {
            printf("Invalid Number...Type again\n");
            return false;
        }
    }

    return true;
}

// Function to check valid person residential number
bool check_res(char *person_res_num)
{
    for (int i = 0; i < strlen(person_res_num); i++)
    {
        if (!isdigit(person_res_num[i]))
        {
            printf("Invalid Residential Number...Type again\n");
            return false;
        }
    }

    return true;
}

// Function to check valid person office number
bool check_office(char *person_office_num)
{
    for (int i = 0; i < strlen(person_office_num); i++)
    {
        if (!isdigit(person_office_num[i]))
        {
            printf("Invalid Office Number...Type again\n");
            return false;
        }
    }

    return true;
}

// Function to check valid email ID
bool check_email(char *person_email)
{
    for (int i = 0; i < strlen(person_email); i++)
    {
        if (person_email[i] == '@')
        {
            return true;
        }
    }

    printf("Invalid Email ID...Type again\n");
    return false;
}
