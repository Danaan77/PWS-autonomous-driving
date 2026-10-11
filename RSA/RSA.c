// includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
 
//variabele declaraties
__uint128_t m; // 128 bit waarde
int64_t d ,K ,e;
int64_t versleuteld_bericht;
int64_t ontgrendeld_bericht;
char Final_Mesage[1000]; int Final_letter = 0;

// Functie Declaraties
int64_t bijbehorende_letters(int64_t ontgrendeld_bericht);
int64_t mod_of_pow(int64_t base, __uint128_t mod, int64_t exponent); // kan ook voor versleuteling worden gebruikt
int64_t calc_K(__uint128_t prod); // werkt sws met 2 priemen van 10 cijfers :)
int64_t calc_euclides(int64_t d, int64_t K);

__uint128_t string_to_128int(char string[]) {

    __uint128_t result = 0;

    for (int i = 0 ; string[i] != '\0' ; i++) {
        int nr = ((int)string[i]) -'0'; // char naar getal
        result = result * 10 + (__uint128_t)nr;
        //printf("%d--- \n", nr);
    }
    return result;
}

// main programma
int main() {

    printf("------START PROGRAMMA------\n");

    // vraag public key
    char m_input[100];
    printf("wat is m: "); scanf("%s", m_input);
    m = string_to_128int(m_input);// input naar int

    printf("wat is d: "); scanf("%lld", &d);
    printf("--------PRIVATE KEY--------\n");

    // kraak voor e
    K = calc_K(m);
    if (K == -1) { printf("-----kon K niet vinden-----"); return 0;}
    else { printf("K: %lld\n", K); }

    e = calc_euclides(d,K);
    if (e == -1) { printf("-----kon e niet vinden-----"); return 0;}
    else {printf("e: %lld\n", e);}
    printf("---------------------------");
    
    // ontgrendel bericht loop
    printf("\nversleuteld bericht: ");
    while(versleuteld_bericht != -67) {

        versleuteld_bericht = 0;
        ontgrendeld_bericht = 0;

        scanf("%lld", &versleuteld_bericht);

        if(versleuteld_bericht != -67){
            ontgrendeld_bericht = mod_of_pow(versleuteld_bericht, m, e);
            printf("%lld-" , ontgrendeld_bericht);
            bijbehorende_letters(ontgrendeld_bericht);}
        }

    printf("\nhet uiteindelijke bericht: ");
        
    for (int i = 0; i < Final_letter; i++){
        printf("%c", Final_Mesage[i]);
    }

    return 0;
}

// Functie Defenities
int64_t mod_of_pow(int64_t base, __uint128_t mod, int64_t exponent) {

    __uint128_t s = 1; // begint met *1 want *1 is hetzelfe
    __uint128_t u_base = (__uint128_t) base;
    __uint128_t u_exponent = (__uint128_t) exponent;
    
    u_base %= mod;

    while (u_exponent > 0) {
        if (u_exponent % 2 == 1) { s = (s * u_base) % mod; }
        u_exponent /= 2;
        u_base = (u_base*u_base)% mod;
    }

    return (int64_t)s;
}

int64_t calc_K(__uint128_t prod) {

    int64_t p; int64_t q;

    for (__uint128_t i = 3; i < prod; i+=2) {
        if (prod % i == 0) {
        p = (int64_t)i;
        q = (int64_t) (prod / (__uint128_t)p);
        i = prod;
        printf("p: %lld | q: %lld\n", p, q); // voor debug
        return (p - 1)*(q - 1);
        }
    }

    return -1; // voor error message dat K niet is gevonden
}

int64_t calc_euclides(int64_t pub_d, int64_t pub_K) {

    if (pub_K <= 0) { return -1; }

    // r0 en r1 zijn de resten
    int64_t r0 = pub_d;
    int64_t r1 = pub_K;

    // x0 en x1 zijn de coëfficiënten van d
    int64_t x0 = 1;
    int64_t x1 = 0;

    while (r1 != 0) {

        int64_t quotient = r0 / r1;
        int64_t temp; // voor doorschuiven
        
        // Nieuwe rest berekenen
        temp = r0 - quotient * r1;
        r0 = r1;
        r1 = temp;

        // Coëfficiënt van pub_d berekenen
        temp = x0 - quotient * x1;
        x0 = x1;
        x1 = temp;
    }

    // Een inverse bestaat alleen als ggd(d, K) gelijk is aan 1
    if (r0 != 1) { return -1; }

    // x0 is de inverse van pub_d modulo pub_K
    x0 %= pub_K;

    // Tel er K bij op tot positief
    if (x0 < 0) { x0 += pub_K; }

    return x0;
}

int64_t bijbehorende_letters(int64_t cijfer){

    char letter_array[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int count = 0; int digits[10]; int64_t number = cijfer; int letter_count = 0; char letters[10]; int amount_of_digits;
    //split that shit
    //printf("\nsplittin' that shiy");
    //printf("\nnumber: %lld", number);

    while (number > 0){
    digits[count] = (int) number % 10;
    number /= 10;
    //printf("\ndigit: %d  at index: %d", digits[count], count);
    count++;
    }

    amount_of_digits = count;

    //printf("\namount_of_digits: %d", amount_of_digits);
    //printf("\nDigits seperated");

    if (amount_of_digits % 2 != 0){
        letters[letter_count] = letter_array[digits[amount_of_digits-1-letter_count]-1];
        Final_Mesage[Final_letter] = letters[letter_count];
        Final_letter++;
        //printf("\nletter: %c", letters[letter_count]);
        letter_count++;
    }

    while(letter_count<count){
        letters[letter_count] = letter_array[10*digits[amount_of_digits-1-letter_count]+digits[amount_of_digits-1-(letter_count+1)]-1];
        Final_Mesage[Final_letter] = letters[letter_count];
        Final_letter++;
        //printf("\nletter: %c", letters[letter_count]);
        letter_count += 2;
        //printf("\nletter_count: %d", letter_count);
    }

    return 0;
}