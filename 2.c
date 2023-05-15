#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPTED_FILE "a.txt"
#define DECRYPTED_FILE "b.txt"

char decryption_symbols[100];

// Function prototype for the encryption algorithm
void encrypt(char*);
void decrypt(char*, char*);

int main(void)
{
	char* str = malloc(sizeof(char) * 100);

	// Read the original line of text from the keyboard
	printf("Enter the original line of text: ");
	fgets(str, sizeof(str), stdin);

	// Remove the newline character from the string
	str[strlen(str) - 1] = '\0';

	// Encrypt the line of text
	encrypt(str);

	// Write the encrypted line of text to the file
	FILE *fp = fopen(ENCRYPTED_FILE, "w");
	fputs(str, fp);
	fclose(fp);

	// Read the encrypted line of text from the file
	fp = fopen(ENCRYPTED_FILE, "r");
	fgets(str, sizeof(str), fp);
	fclose(fp);
	
	//Display the decrypted line
	decrypt(str, decryption_symbols);
	printf("Decrypted line of text from the file: %s\n", str);

	// Write the decrypted line of text to the output file
	fp = fopen(DECRYPTED_FILE, "w");
	fputs(str, fp);
	fclose(fp);

    free(str);

	return 0;
}

// Function definition for the encryption algorithm
void encrypt(char *str)
{
	char *p = str + 1;
	int i = 1;

	// Replace the symbols that are multiples of two in sequence with their sequence number
	while (*p != '\0')
	{
		decryption_symbols[(i-1)/2] = *p;
		*p = i;
		p += 2;
		i += 2;
	}
}

void decrypt(char *str, char* symbols_for_decryption){
    char *p = str + 1;
	char *p1 = symbols_for_decryption;

	// Replace the symbols that are multiples of two in sequence with their sequence number
	while (*p != '\0')
	{
		*p = *p1;
		p += 2;
		p1++;
	}
}
