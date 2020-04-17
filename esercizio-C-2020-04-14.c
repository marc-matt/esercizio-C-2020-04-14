/*
    rubrica.c
            Author: M. Marconi
            Date: 15th April 2020
            Version: 1.0.0
*/

// IN PROGRESS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

int id_counter;
contact_type * address_book[ADDRESS_BOOK_SIZE];
int lastIndex;

//WORK
contact_type * create_contact(char * name, char * phone){
    contact_type * person;
    person = calloc(1, sizeof(contact_type));
	person->id = id_counter;
	id_counter++;
	if (name != NULL){
		strncpy(person->name, name, NAME_LEN);
		}
	if (phone != NULL){
		strncpy(person->phone, phone, PHONE_LEN);
	}
    return person;
}

//WORK
void print_contact(contact_type * person){
	printf("Person: ID: %d, NAME: %s, PHONE: %s\n", person->id, person->name, person->phone);
}

//WORK
bool emptyCase(int * index){
	bool is_empty;
	int i = *index;
	if(address_book[i] == NULL){
		is_empty = true;
	} else {
		is_empty = false;
	}
	return is_empty;
}

//WORK
int add_to_address_book(contact_type * c){
	int i = lastIndex;
	while(emptyCase(&i) == false && i == ADDRESS_BOOK_SIZE - 1){
		i++;
	}
	address_book[i] = c;
	lastIndex++;
	return i;
}

//WORK
bool isEqual(contact_type * c1, contact_type * c2){
	bool eq;
	if((strcmp(c1->name, c2->name)) == 0 && (strcmp(c1->phone, c2->phone)) == 0){
		eq = true;
	}
	else {
		eq = false;
	}
	return eq;
}

//WORK
bool sameName(contact_type * c1, contact_type * c2){
	bool sameN;
	if((strcmp(c1->name, c2->name)) == 0){
		sameN = true;
	}
	else {
		sameN = false;
	}
	return sameN;
}

//WORK
int compare_contacts(contact_type * c1, contact_type * c2){
	int result = 0;
	if(c1 == NULL || c2 == NULL){
		return -1;
	}
	result = strcmp(c1->name, c2->name);
	if(result != 0){
		return result;
	}
	result = strcmp(c1->name, c2->name);
	if(result != 0){
		return result;
	}
	return 0;
}

//WORK
int remove_from_address_book(contact_type * c){
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(compare_contacts(c, address_book[i]) == 0){
			address_book[i] = NULL;
			return i;
		}
	}

	return -1;
}

//WORK
int search_in_address_book(contact_type * c){
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(compare_contacts(c, address_book[i]) == 0){
			return i;
		}
	}

	return -1;
}

//WORK
void swap_contact(contact_type ** c1, contact_type ** c2){
	contact_type temp;
	temp = **c1;
	**c1 = **c2;
	**c2 = temp;
}

//TO TEST
void sort_by_name(contact_type * address[]){
	int n, ultimoCambio;
	n = ADDRESS_BOOK_SIZE;
	while(n > 1){
		ultimoCambio =0;
		for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
			if(compare_contacts(address[i-1], address[i]) > 0){
				swap_contact(&address[i-1], &address[i]);
				ultimoCambio = i;
			}
		}
		n = ultimoCambio;
	}
}

int main(int argc, char *argv[]) {
	contact_type * dino = create_contact("dino\0","+391237\0");
	if(dino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int idin = add_to_address_book(dino);
	bool x = emptyCase(&idin);
	printf("%s", x ? "true" : "false");
	contact_type * filippo = create_contact("filippo\0", "+391239\0");
	if(filippo == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int ifil = add_to_address_book(filippo);
	contact_type * barbara = create_contact("barbara\0","+391235\0");
	if(barbara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int ibar = add_to_address_book(barbara);
	contact_type * antonio = create_contact("antonio\0","+391234\0");
	if(antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int iant = add_to_address_book(antonio);
	contact_type * enrico = create_contact("enrico\0","+391238\0");
	if(enrico == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int ienr = add_to_address_book(enrico);
	contact_type * chiara = create_contact("chiara\0","+391236\0");
	if(chiara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int ichi = add_to_address_book(chiara);
	int nAnto = search_in_address_book(antonio);
	if(nAnto >= 0){
		int rAnt = remove_from_address_book(antonio);
	}
	contact_type * pino = create_contact("pino\0","+399999\0");
	if(pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int ipin = add_to_address_book(pino);
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
	int iant2 = add_to_address_book(antonio);
	sort_by_name(address_book);
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
	return 0;
}
