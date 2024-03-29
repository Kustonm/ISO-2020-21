/**
* @file s_header.h
* @author   G.A.
* @date     23/02/2021
* @brief    Include file with struct s_header, struct s_info and s_mypack_header
* @details  A header file with the definition of struct s_header, struct s_info and 
*           s_mypack_headers of  mypackzip file format
*           +++++++++++++++++++++++
*           + struct s_header 0   +
*           +---------------------+
*           + struct s_header 1   +
*           +---------------------+
*           +        ...          +
*           +---------------------+
*           + struct s_header n-1 +
*           +++++++++++++++++++++++
*           +    Data File 0      +
*           +---------------------+
*           +    Data File 1      +
*           +---------------------+
*           +        ...          +
*           +---------------------+
*           +    Data File n-1    +
*           +++++++++++++++++++++++
*
*           n = NUM_HEADERS
*/

#define NUM_HEADERS     32
#define S_HEADER_SIZE   512
#define MAX_FILE_NAME   256

struct s_Info {
   char Type;                            // ='z'  (mypackzip file type) ('\' Empty data)
   char Compress;                        // ='n' (default) o 'y'. 'y' if the file data is stored in compressed form

   unsigned long DataSize;               // Original file size (uncompressed) 
   unsigned long CompSize;               // Size of the compressed file. If the data is not compressed, 
                                         //its value is the size of the original file 
   char DataFileName[MAX_FILE_NAME];     // Data file name  
   unsigned long DatPosition;            // Position within mypackzip where the original file data 
                                         // is stored (DataFileName)
   char FileType;                        // ='r'(regular file),   ='d'(directory),
                                         //   ='o'( other type)
};

#define S_INFO_SIZE sizeof(struct s_Info)

#define DUMMY_SIZE (S_HEADER_SIZE - S_INFO_SIZE)

struct  s_Header {
   struct s_Info FileInfo;            // File Information
   char Dummy[DUMMY_SIZE];            // ToDo...  
};
 
struct  s_mypack_headers {
   struct  s_Header vHead[NUM_HEADERS];    // File Headers Vector 
};

