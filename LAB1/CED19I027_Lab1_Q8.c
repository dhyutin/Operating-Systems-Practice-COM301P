// N Sree Dhyuti
// CED19I027
//Lab 1 : Q8
// Inclusion of required libraries
# include <stdio.h>
# include <string.h>

// Function to check if a character is a vowel or not
int is_vowel (char var)
{
	if (var == 'A' || var == 'a' || var == 'E' || var == 'e' || var == 'I'|| var == 'i' || var == 'O' || var == 'o' || var == 'U' || var == 'u')
		return 1;
	else return 0;
}

// Function to remove vowels from a file
void remove_vowels (FILE *input_file, FILE *output_file)
{
	char var;
	// We run the loop until we traverse to the End Of File (EOF)
	while ((var = fgetc(input_file)) != EOF)
	{
		// If the current character is not a vowel, only then we will export it to the output file
		if (!(is_vowel(var)))
		{
			fprintf(output_file, "%c", var);
		}
	}
}

// Main
int main()
{
	// Define required variables
	FILE *input_file, *output_file;

	// Open Input and create Output files	
	input_file = fopen("input.txt", "r");
	output_file = fopen("output.txt", "w");
	
	// Call function to remove vowels
	remove_vowels(input_file, output_file);
	
	printf("Vowels from input file have been removed and stored in output.txt file\n");
	
	// Close the files used
	fclose(input_file);
	fclose(output_file);
	
	return 0;	
}
