// N Sree Dhyuti
// CED19I027
//Lab 1 : Q7 
// Inclusion of required libraries
# include <stdio.h>
# include <string.h>

// Function to copy a file to another file
void copy (FILE *input_file, FILE *output_file)
{
	char var;
	// We run the loop until we traverse to the End Of File (EOF)
	while ((var = fgetc(input_file)) != EOF)
	{
		fputc(var, output_file);
	}
}

// Function to convert all characters in a file to small letters
void convert_small (FILE *input_file, FILE *output_file)
{
	char var;
	// We run the loop until we traverse to the End Of File (EOF)
	while ((var = fgetc(input_file)) != EOF)
	{
		// If the character is a capital letter, we convert it to small by replacing it with the letter after 32 positions in ASCII Table
		if (var >= 65 && var <= 90)
		{
			var = var + 32;
		}
		fputc(var, output_file);
	}
}

// Function to convert all characters in a file to capital letters
void convert_capital (FILE *input_file, FILE *output_file)
{
	char var;
	// We run the loop until we traverse to the End Of File (EOF)
	while ((var = fgetc(input_file)) != EOF)
	{
		// If the character is a capital letter, we convert it to small by replacing it with the letter after 32 positions in ASCII Table
		if (var >= 97 && var <= 122)
		{
			var = var - 32;
		}
		fputc(var, output_file);
	}
}

// Main
int main()
{
	// Define required variables
	FILE *input_file, *output_file;
	int choice;
	
	// Open Input and create Output files
	input_file = fopen("input.txt", "r");
	output_file = fopen("output.txt", "w");

	// User Manual
	printf("Enter : \n");
    printf("1 for copying the input file exactly\n");
	printf("2 for converting to small letters\n");
	printf("3 for converting to capital letters\n");
	scanf("%d", &choice);
	
	// Switch control as per user choice
	switch (choice)
	{
		case 1:
			{
                // Copy Function Call
				copy (input_file, output_file);
				printf("input.txt file has been copied to output.txt file\n");
				break;
			}
		case 2:
			{
				// Function call to convert to small letters
				convert_small (input_file, output_file);
				printf("input.txt file has been converted to small letters in output.txt file\n");
				break;
			}
		case 3:
			{
				// Function call to convert to capital letters
				convert_capital (input_file, output_file);
				printf("input.txt file has been converted to capital letters in output.txt file\n");
				break;
			}
		default:
			{
				// Incase of wrong input by user
				printf("Invalip input by user. Try again.\n");
				break;
			}
	}
	
	// Close the files used
	fclose(input_file);
	fclose(output_file);
	
	return 0;
}
