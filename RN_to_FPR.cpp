#include <string>
#include <iostream>
#include <math.h>           
using namespace std;

//The union combines the following integers
//and stores them in the same location. However the
//order must go from least-significant-bit to 
//most-significant-bit in order to properly print
//the result.
typedef union { 
    float f; 
    struct{ 
        unsigned int mantissa : 23; 
        unsigned int exponent : 8; 
        unsigned int sign : 1; 
    } raw; 
} floatingPoint;

//Converts binary integer array into related integer
unsigned int convertToInt(int* arr, int low, int high){ 
    unsigned f = 0, i; 
    for (i = high; i >= low; i--){ 
        f = f + arr[i] * pow(2, high - i); 
    } 
    return f; 
}

//Prints binary representation of decimal (n)
//according to the number of bits(i)
void printBinary (int n, int i){
    int k;
    for (k = i - 1; k >= 0; k--){
        if(n >> k){
            printf("1");
        } else {
            printf("0");
        }
    }
}

//Function prints IEE-754 F.P.R of
//decimal value
void printIEEE(floatingPoint var){
    printf("%d | ", var.raw.sign); 
    printBinary(var.raw.exponent, 8); 
    printf(" | "); 
    printBinary(var.raw.mantissa, 23); 
    printf("\n");
}

//Main Module
int main()
{
    string number;
    float decimalGet;
    int ieee[32];
    cout << "Will you input a Decimal or FPR?" << endl;
    cin >> number;
    
    if (number == "Decimal"){
        cout << "Enter decimal value to be converted:" << endl;
        // Get the real value
        cin >> decimalGet;
    } else {
        cout << "Enter IEEE-754 Floating Point Representation to be converted:" << endl;
        // Get the 32-bit floating point number
        cin >> ieee[32];
    }
    
    if (number == "Decimal"){
        // Instantiate the union 
        floatingPoint var; 
        
        //Get Decimal
        var.f = decimalGet;
        
        // Get the IEEE floating point representation 
        printf("IEEE 754 representation of %f is : \n", var.f); 
        printIEEE(var);
        
    } else if (number == "FPR"){
        floatingPoint var; 
      
        // Convert the least significant 
        // mantissa part (23 bits) 
        // to corresponding decimal integer 
        unsigned f = convertToInt(ieee, 9, 31); 
      
        // Assign integer representation of mantissa 
        var.raw.mantissa = f; 
      
        // Convert the exponent part (8 bits) 
        // to a corresponding decimal integer 
        f = convertToInt(ieee, 1, 8); 
      
        // Assign integer representation 
        // of the exponent 
        var.raw.exponent = f; 
      
        // Assign sign bit 
        var.raw.sign = ieee[0]; 
      
        printf("The decimal value of the given"
               " IEEE-754 representation is : \n"); 
        printf("%f", var.f);
        
    } else {
        cout << "Input invalid" << endl;
    }
    
    return 0;
}

