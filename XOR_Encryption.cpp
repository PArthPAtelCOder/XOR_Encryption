
	// Program to Encrypt and Decrypt Data with password 
    // We are using XOR Encryption Method
    // Program's name is Ko0t

	#include<stdio.h>
	#include<string.h>
	
	#define SIZE 300        // Max No Character which can be stored as a input
	#define KEY_SIZE 101     // Max Size of Key is ( KEY_SIZE - 1 )  ,  because 1 byte is for '\0'

	void EncryptionDecryption( char* , int* , int ) ;  //Function declaration 
	
	int KeyLen, TextLen ;   //Global variable declaration
    char tmp ;
	int main()

	{      
        //Declaring variables
		int Choice ;
		char PlainText[SIZE];
		char EncryptedText[SIZE] ; 
		char Key[KEY_SIZE];
		int KeyModified[KEY_SIZE] = {0} ;
		char SecretKey1[] = "!$*(gi%~.,&fuam4^<[}\3em8os#*-";
		char SecretKey2[] = "gR3$7(~G `.<_&@!\%1*9Azf2-+:;\"P"; // Secret Key is arbitrary , Secret Key Size : 30 Char

		printf ( "\n\n Welcome to KoOt\n\n" ) ;
		printf ( " Please Select one of the following Options -:\n\n" ) ;
		printf ( " * Press 1 for Encryption\n * Press 2 for Decryption\n * Press 3 for Exit\n\n" ) ;
		scanf ( "%d" , &Choice ) ;

		fflush (stdin) ;
		while ( Choice >= 4 || Choice < 1 )    // IF choice is wrong , program will ask again
		{
			  printf ( "Something went wrong\n" ) ;
			  printf ( "Please Enter the Valid Choice\n" ) ;
			  printf ( " * Press 1 for Encryption\n * Press 2 for Decryption\n * Press 3 for Exit\n\n" ) ;
			  scanf ( "%d" , &Choice ) ;
			  fflush ( stdin ) ;
		}
		
		switch ( Choice )                          		
		{     //This case : Encryption
 		     case 1:
                      {
			 printf ( "\n Enter the Text to be Encrypted\n" ) ;      // Entering PlainText
		         gets ( PlainText ) ;
			 puts ( "\n Enter Password (length <= 100 ) : " ) ;        // Entering password for encryption
			 gets ( Key ); 
			 KeyLen = strlen ( Key ) ;
			 TextLen = strlen ( PlainText );

                         for ( int counter=0 ; counter < KeyLen ; counter++ )  // Or function on user key with our secret key
	                 {  
	                	if ( ('A' <= Key[counter])  && (Key[counter] <= 'Z') )
                                {
					 Key[counter] = Key[counter] | SecretKey2[counter % 30] ;
                                }	                   
	                        else
	                   	{
 				         Key[counter] = Key[counter] | SecretKey1[counter % 30] ;
			        } 
                         }

                         for (int i = 0 ; i < KeyLen ; ++i)
                         {   for (int j = 0 ; j < KeyLen; ++i)
                             {
                             	 if (j == i)
                             	    continue ;
                                 KeyModified[i] += Key[j] ;
                             }

                             KeyModified[i] = KeyModified[i] % 255 ;
                         }


		      	 EncryptionDecryption( PlainText , KeyModified, 0 ) ;
			 break ;
                      }

                      // This case : Decryption		
              case 2: FILE *Decryption ; // "Decryption" is pointing to Encrypted.txt file in which encrypted data is saved after encryption 
		      {
		         Decryption = fopen ( "Encrypted.txt" , "r" ) ;
     			 
				 // checking whether Encrypted.txt file is empty or not.
			        if (( '0' <= (tmp = fgetc(Decryption)))&& ( tmp <= '9' ))
			        {  
			           rewind(Decryption);
     			       
     			       for ( int counter=0 ; !feof(Decryption) ; counter++ )      // Inputing encrypted data
	    		       {   
	    		       	   fscanf ( Decryption , "%d" , &EncryptedText[counter] ) ;
                           TextLen++ ;
	     		           fgetc ( Decryption ) ;     // ignoring "\" in Encrypted.txt file
	       		       }
				  
			           fclose(Decryption);

			           printf ( "\n\n We got your Encrypted Data.\n\n" ) ;
	        
	                   printf(" Enter your Password ( length <= 100) : ");  
			           gets(Key);
			           KeyLen = strlen ( Key ) ;

			          for ( int counter=0 ; counter < KeyLen ; counter++ )    // Or function on user key with our secret key
	                  {  
	                      if ( (65 <= Key[counter])  && (Key[counter] <= 90) )
                          {
                             Key[counter] = Key[counter] | SecretKey2[counter % 30] ;
	                      }
	                      else
	                      {
                              Key[counter] = Key[counter] | SecretKey1[counter % 30] ;
				          } 
			          }

			           for (int i = 0 ; i < KeyLen ; ++i)
                         {   for (int j = 0 ; j < KeyLen; ++i)
                             {
                             	 if (j == i)
                             	    continue ;
                                 KeyModified[i] += Key[j] ;
                             }

                             KeyModified[i] = KeyModified[i] % 255 ;
                         }
		            }
		            else
			       {
			       	   fclose(Decryption);
			       	   printf("\n  Hey, there is nothing to decrypt in the file Encrypted.txt\n  Please add your data & try again.\n\n\n");
			       } 
			       
			 EncryptionDecryption( EncryptedText , KeyModified , 1 ) ;
	                 break ;
                      }
                      //This case : Exit		
                      case 3: 
                      {
                         return(1) ;
			 break ;
                      }
		}
	}

	// To XOR characters in text array with characters in Key array  ; for encryption mode=0 ; for decoding mode=1
	void EncryptionDecryption ( char *text , int *Key , int mode )     // using same function for Encryption and Decryption 
	{	
	    if ( mode == 0 )   // Mode '0' means Encryption
	    {  
	       for( int i=0 ; i < TextLen ; i++ )   
	       {
	       	  text[i] = text[i] ^ Key[i % KeyLen] ;
	       }
	        
	       FILE *Encryption = fopen("Encrypted.txt","w" );  // "Encryption" is pointing file in which encrypted will be stored 
               printf ( "\n----------------------------------------------------------") ;	 
	       printf ( "\n\n Encrypted Data : " ) ;
	       for ( int counter=0 ; counter < TextLen ; counter++ )     
               {
	          printf ( "%c" , text[counter] ) ;           // Printing encrypted data in terminal , like "@#$@$@#"
	          fprintf ( Encryption , "%d\\" , text[counter] ) ;    // Adding Encrypted data in the file , like 1\23\122\34\45\56    ;   firstChar\SecondChar\ so on
	       }
	       printf ( "\n\n----------------------------------------------------------") ;
	       fclose(Encryption);
	       printf ( "\n\n $$$ We saved your Encrypted Data into file Encrypted.txt in the same Directory in which you have our program.\n\n" ) ;
               printf ( " $$$ If you want to share your data then share this Encrypted.txt with our program .\n\n\n\n\n" ) ;
	    }
	    
	    else if ( mode == 1 )  // mode 1 means decryption
	    {   
	        for( int i=0 ; i < TextLen ; i++ )   
	       {
	       	  text[i] = text[i] ^ Key[i % KeyLen] ;
	       }
	        
	       printf ( "\n----------------------------------------------------------") ;
	       printf ( "\n\n Decrypted Data : " ) ;
	       for ( int counter=0 ; counter < (TextLen - 1) ; counter++ )
	       {
		   printf ( "%c" , text[counter] ) ;
	       }
	        printf ( "\n\n----------------------------------------------------------") ;
	        printf( "\n\n We hope that you liked our program !\n\n" ) ;
   	   }
      } 


 
