// includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//variabele declaraties
long long m; long long d; long long K; long long e;
long long versleuteld_bericht;
long long ontgrendeld_bericht;
char Final_Mesage[100]; int Final_letter = 0;

// Functie Declaraties
long long bijbehorende_letters(long long ontgrendeld_bericht);
long long mod_of_pow(long long base, long long mod, long long exponent);// kan ook voor versleuteling worden gebruikt
long long calc_K(long long prod); // werkt sws met 2 priemen van 9 cijfers :)
long long calc_euclides( long long d, long long K);

// main programma
int main() {
    printf("------START PROGRAMMA------\n");

    // vraag public key
    printf("wat is m: "); scanf("%llu", &m);
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

        //printf("\nversleuteld bericht: "); 
        scanf("%lld", &versleuteld_bericht);

        if(versleuteld_bericht != -67){
            ontgrendeld_bericht = mod_of_pow(versleuteld_bericht, m, e);
            //printf("---------------------------");
            //printf("\nuw bericht:|%lld|" , ontgrendeld_bericht);
            bijbehorende_letters(ontgrendeld_bericht);}
        }

    printf("\nhet uiteindelijke bericht: ");
        
    for (int i = 0; i < Final_letter; i++){
        printf("%c", Final_Mesage[i]);
    }

    return 0;
}

// Functie Defenities
long long mod_of_pow(long long base, long long mod, long long exponent) {

    long long s = 1; // begint met 1 want 1 is hetzelfe
    base %= mod;

    while (exponent > 0) {
        if (exponent % 2 == 1) { s = (s * base) % mod; }
            exponent /= 2;
            base = (base*base)% mod;
        }

    return s;
}

long long calc_K(long long prod) {

    long long p; long long q;

    for (long long i = 3; i < prod; i+=2) {
        if (prod % i == 0) {
        p = i;
        q = prod / p;
        i = prod;
        printf("p: %llu | q: %llu\n", p, q); // voor debug
        return (long long)(p - 1)*(q - 1);
        }
    }

    return -1; // voor error message dat K niet is gevonden
}

long long calc_euclides(long long pub_d, long long pub_K) {

    if (pub_K <= 0) { return -1; }

    // r0 en r1 zijn de resten
    long long r0 = pub_d;
    long long r1 = pub_K;

    // x0 en x1 zijn de coëfficiënten van d
    long long x0 = 1;
    long long x1 = 0;

    while (r1 != 0) {
        long long quotient = r0 / r1;
        long long temp; // voor doorschuiven
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

long long bijbehorende_letters(long long cijfer){

    char letter_array[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int count = 0; int digits[10]; long long number = cijfer; int letter_count = 0; char letters[10]; int amount_of_digits;
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
