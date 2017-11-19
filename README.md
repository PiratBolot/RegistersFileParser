# RegistersFileParser
A programm that converts source file into .ini and/or .h files

## Program variations
There are Windows and Linux versions of program in the project 

## Usage
<b>For Linux:</b> <main_file_name> [parameters]

Parameters:
 * -f source - set source file name
 * -h file - set file name of output header, default - <sourceName>.h
 * -i file - set file name of output ini file, default - <sourceName>.ini
 * Without -h and -i arguments you can set source file name without -f : <executable_name> <file>
              
               
<b>For Windows:</b> <execution_file_path> <input_file_name>

## Files Format

   Source file format - <Register_name><tab><Register_address[0]><Register_address[1]><Command>  
                        Register_address[0], Register_address[1] and Command are one 3-byte HEX number,  
                        e.g: R267  0x010B07 means:  Name                  = R267  
                                                    Register_address[0]   = 0x01  
                                                    Register_address[1]   = 0x0B  
                                                    Command               = 0x07 
    
 
   Ini output format  - same ordered data without name of register
 
                               0x01,  0x13,  0x07,
                               0x01,  0x14,  0x20,
                               0x01,  0x15,  0x11,
                                       ...
                               0x05,  0x0B,  0x0D
 
   Header output format - need to include into project
  
                               #ifndef INPUT_FILE_NAME
                               #define INPUT_FILE_NAME
 
                               const uint32_t numCommands = 3;
                               const uint8_t LmkConfigCmds[numCommands][3]={
                                     { 0x00, 0x00, 0x80 },
                                     { 0x00, 0x00, 0x00 },
                                     { 0x00, 0x00, 0x80 }
                                     };
 
                               #endif //INPUT_FILE_NAME                                           
