#include <stdio.h>
#include <string.h>

#define MAX_BUF  256

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char encode(unsigned char, unsigned char, int);


int main()
{
  char str[8];
  int  choice, i, counter;
  unsigned char plainArr[MAX_BUF];
  unsigned char cypherArr[MAX_BUF];
  unsigned char key, charValue;

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("\n  what is your selection: ");
  
  do{
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &choice);
      
    switch (choice) {
      
      case 1:
	/*
	  This case takes in plaintext and a key from the user.
	  It loops through the length of the string and encodes the character values and prints them out.
	*/
	printf("\nEnter plaintext:\n");
	fgets(plainArr, sizeof(plainArr), stdin);
	printf("Enter key:\n");
	scanf("%hhu", &key);
	printf("Cyphertext:\n");
	
	for(counter=0; counter< strlen(plainArr) ; counter++){
	    plainArr[counter] = encode(plainArr[counter],key,counter);
	    printf("%hhu ", plainArr[counter]);
	}
	printf("-1\n");
	break;

      case 2:

	/*
	  This case takes in cyphertext and a key from the user.
	  It first checks to see if the number is the terminating number -1 (this case it would be 255 in an unsigned char). 
	  If it is not the terminating number it sets it in an array of unsigned chars.
	  It loops through the amount of number, encodes it, and prints it to the screen as a string.
	*/
	counter = 0;
	printf("\nEnter cypthertext:\n");
	do{
	  scanf("%hhu", &charValue);
	  
	  if(charValue == 255){
	    cypherArr[counter] = '\0';
	    break;
	  }
	  else
	    cypherArr[counter] = charValue;
	  counter++;
	}while(counter<MAX_BUF);
	
	printf("Enter key:\n");
	scanf("%hhu", &key);
	printf("Plaintext:\n");
	
	for(i=0; i<counter; i++){
	  cypherArr[i] = encode(cypherArr[i],key,i);
	}
	printf("%s\n", cypherArr);
	break;

      default:

	//Prompts user to re-input a choice if they did not select option 1 or 2.
	printf("Error making selection.\n");
	printf("\nYou may:\n");
	printf("  (1) Encrypt a message \n");
	printf("  (2) Decrypt a message \n");
	printf("\n  what is your selection: ");

	break;
    }
  }while(choice < 1| choice > 2); 
  return 0;
}

/*
  Function:  encode
  Purpose:   To encode the values of plaintext or cyphertext
       in:   the source bit from the plaintext or cyphertext
       in:   the key to encode the bits with
       in:   the count to ensure that the same letters will be encoded differntly
   return:   the new encoded value to be stored


 */
unsigned char encode(unsigned char pt, unsigned char key, int count)
{
  unsigned char byte;
  int i;
  
  byte = pt;

  switch (count%3) {
    case 0:
      
      for(i=0; i<7; i+=2){
	byte = getBit(pt,i) ^ getBit(key,i) == 0 ?  clearBit(byte, i) : setBit(byte,i);	
      }		 
      break;
      
    case 1:

      for(i=1; i<7; i+=2){
	byte = getBit(pt,i) ^ getBit(key,i) == 0 ? clearBit(byte, i) : setBit(byte,i);
      }
      
      break;
      
    case 2:
      
      for(i=0; i<7; i++){
        byte = getBit(pt,i) ^ getBit(key,i) == 0 ? clearBit(byte, i) : setBit(byte,i);
      }
     
      break;
  }

  return byte;
}


/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)   
{ 
  
  return (c & (1 << n)) >> n;

}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)   
{ 

  c = c | (1 << n);

}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n) 
{ 

  c = c & (~(1 << n));

}
