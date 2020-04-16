/*
    Rubrica
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

void print_contact(contact_type * person){
	printf("Person: ID: %d, NAME: %s, PHONE: %s\n", person->id, person->name, person->phone);
}

int emptyCase(contact_type * contact){
	int is_empty;
	if(contact == NULL){
		is_empty = 0;
	} else {
		is_empty = -1;
	}
	return is_empty;
}

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

bool samePhone(contact_type * c1, contact_type * c2){
	bool sameP;
	if((strcmp(c1->phone, c2->phone)) == 0){
		sameP = true;
	}
	else {
		sameP = false;
	}
	return sameP;
}

int compare_contacts(contact_type * c1, contact_type * c2){
	int comp;
	if((emptyCase(c1) == 0) || (emptyCase(c2) == 0)){
		// DEBUG printf("Errore: rilevato contatto vuoto");
		comp = -1;
	} else if(isEqual(c1, c2) == true){
		comp = 0;
	} else if(sameName(c1, c2) == true){
		// DEBUG printf("I contatti comparati hanno lo stesso nome");
		int result = strcmp(c1->phone, c2->phone);
		if(result > 0){
			comp = 2;
		} else if(result < 0){
			comp = -2;
		}
	} else if(samePhone(c1, c2) == true){
		// DEBUG printf("I conttatti comparati hanno lo stesso numero di telefono");
		int result = strcmp(c1->name, c2->name);
		if(result > 0){
			comp = 2;
		} else if(result < 0){
			comp = -2;
		}
	} else {
		int result = strcmp(c1->name, c2->name);
		if(result > 0){
			comp = 2;
		} else if(result < 0){
			comp = -2;
		}
	}
	return comp;
}

int add_to_address_book(contact_type * c){
	int i = 0;
	while(emptyCase(address_book[i]) == true){
		if(i == ADDRESS_BOOK_SIZE - 1){
			printf("Rubrica piena!\n");
			return -1;
		}
		i++;
	}
	address_book[i] = c;
	return i;
}

int remove_from_address_book(contact_type * c){
	int i = 0;
	int result;
	while(i < ADDRESS_BOOK_SIZE || compare_contacts(c, address_book[i]) != 0){
		i++;
	}
	if(compare_contacts(c, address_book[i]) == 0){
		address_book[i] = NULL;
		result = i;
	} else {
		printf("Contatto non esistente\n");
		result = -1;
	}
	return result;
}

int search_in_address_book(contact_type * c){
	int i = 0;
	int result;
	while(i < ADDRESS_BOOK_SIZE || compare_contacts(c, address_book[i]) != 0){
		i++;
	}
	if(compare_contacts(c, address_book[i]) == 0){
		result = i;
	} else {
		printf("Contatto non esistente\n");
		result = -1;
	}
	return result;
}

void swap_contact(contact_type ** c1, contact_type ** c2){
	contact_type temp;
	temp = **c1;
	**c1 = **c2;
	**c2 = temp;
}

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
	add_to_address_book(dino);
	contact_type * filippo = create_contact("filippo\0", "+391239\0");
	if(filippo == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(filippo);
	contact_type * barbara = create_contact("barbara\0","+391235\0");
	if(barbara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(barbara);
	contact_type * antonio = create_contact("antonio\0","+391234\0");
	if(antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(antonio);
	contact_type * enrico = create_contact("enrico\0","+391238\0");
	if(enrico == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(enrico);
	contact_type * chiara = create_contact("chiara\0","+391236\0");
	if(chiara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(chiara);
	int nAnto = search_in_address_book(antonio);
	if(nAnto > 0){
		remove_from_address_book(antonio);
	}
	contact_type * pino = create_contact("pino\0","+399999\0");
	if(pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(pino);
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
	add_to_address_book(antonio);
	sort_by_name(address_book);
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
	return 0;
}
