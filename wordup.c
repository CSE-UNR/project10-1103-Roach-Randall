// Author: Randall Roach
// THE ULTIMATE FINAL PROJECT OF CS135 YIPPEEEEE!!!!!!
// Purpose: Have a *totally* not trademarked game recreated in C!
// Word length size can be changed so you can do more than 5 letters!
#include<stdio.h>
#include<stdbool.h>

#define WORDLENGTH 5
#define MAXATTEMPTS 6
#define MYSTERYFILE "mystery.txt"

bool loadmysteryword(char secret[]);
bool isguessvalid(char input[]);
void showpreviousguesses(char all[][WORDLENGTH+1], int count);
void assessguess(char secret[], char guess[], char display[], char marks[]);

int main(void){
	char secret[WORDLENGTH+1];
	if(!loadmysteryword(secret)){
		printf("Could not open %s\n", MYSTERYFILE);
		return 0;
	}

	char history[MAXATTEMPTS][WORDLENGTH+1] = {{0}};
	int attempts = 0;
	bool won = false;

	while(attempts < MAXATTEMPTS && !won){
		char raw[100] = {0};
		printf("Enter guess #%d: ", attempts + 1);
		int len = 0;
		int ch;
	while((ch = getchar()) != '\n' && ch != EOF && len < (int)sizeof(raw) - 1){
		raw[len++] = (char)ch;
	}
		raw[len] = '\0';

	if(!isguessvalid(raw)){
		printf("Woah man, you can only use %d letters!\n\n", WORDLENGTH);
		continue;
	}

	char guess[WORDLENGTH+1] = {0};
	for(int i = 0; i < WORDLENGTH; i++){
		char c = raw[i];
		if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
			guess[i] = c;
	}
	for(int i = 0; i <= WORDLENGTH; i++){
		history[attempts][i] = (i < WORDLENGTH ? guess[i] : '\0');
	}

	char display[WORDLENGTH+1] = {0}, marks[WORDLENGTH+1] = {0};
	assessguess(secret, guess, display, marks);
	showpreviousguesses(history, attempts + 1);
	printf("%s\n", display);
	printf("%s\n\n", marks);

	bool match = true;
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] != secret[i]){
			match = false;
			break;
		}
	}
	if(match){
		won = true;
		break;
	}

	attempts++;
	}

	if(won){
		printf("Winner, winner chicken dinner! \nThe word was \"%s\".\n", secret);
	}else{
		printf("Out of attempts! Womp, womp! \nThe word was \"%s\".\n", secret);
	}

	return 0;
	}

	bool loadmysteryword(char secret[]){
	FILE *f = fopen(MYSTERYFILE, "r");	
	if(!f) return false;
	int count = 0;
	int ch;
	while(count < WORDLENGTH && (ch = fgetc(f)) != EOF){
		if(ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
			if(ch >= 'a' && ch <= 'z'){
				secret[count++] = (char)ch;
			}
	}
	fclose(f);

	if(count < WORDLENGTH) return false;
		secret[WORDLENGTH] = '\0';
		return true;
	}

	bool isguessvalid(char input[]){
	int len = 0;
	while(input[len] != '\0') len++;
		if(len != WORDLENGTH) return false;
		for(int i = 0; i < WORDLENGTH; i++){
			char c = input[i];
			if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
				return false;
			}
		}
	return true;
	}

	void showpreviousguesses(char all[][WORDLENGTH+1], int count){
	printf("Your previous guesses:\n");
	for(int r = 0; r < count; r++){
		for(int c = 0; c < WORDLENGTH; c++){
			char ch = all[r][c];
			if(ch >= 'a' && ch <= 'z') ch -= 'a' - 'A';
				putchar(ch);
			}
		putchar('\n');
		}
	}

	void assessguess(char secret[], char guess[], char display[], char marks[]){
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] == secret[i]) {
			display[i] = guess[i] - ('a' - 'A');
			marks[i] = ' ';
		}else{
			display[i] = guess[i];
			marks[i] = ' ';
		}
	}
	display[WORDLENGTH] = marks[WORDLENGTH] = '\0';
	for(int i = 0; i < WORDLENGTH; i++){
		if(display[i] >= 'A' && display[i] <= 'Z') continue;
			for(int j = 0; j < WORDLENGTH; j++){
				if(i != j && guess[i] == secret[j] && guess[j] != secret[j]){
					marks[i] = '^';
					break;
				}
			}
		}
}
