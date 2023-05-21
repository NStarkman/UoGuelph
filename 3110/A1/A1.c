#include "A1.h"

/**
 * It reads a file and displays it in either ASCII or HEX mode. Create a menu to selected the mode and to exit the program.
 * 
 * @return The program is returning 0.
 */
int main() {
  char filename[100];
  int mode = MODE_ASCII;
  int file = 0;
  int size = 0;
  char * buffer = NULL;
  char option;
  int done = 1;

  while (done) {
    printf("\n");
    printf("Main Menu:\n");
    if (mode == MODE_ASCII) {
      printf("Current mode: ASCII\n");
    } else if (mode == MODE_HEX) {
      printf("Current mode: HEX\n");
    }
    printf("o - open file\n");
    printf("d - change display mode\n");
    printf("x - exit\n");
    printf("Enter option: ");

    scanf(" %c", & option);

    switch (option) {

    case 'o':
      printf("Enter filename: ");
      scanf("%s", filename);

      file = open(filename, O_RDONLY);
      if (file == -1) {
        printf("Cannot open file %s\n", filename);
        break;
      }  

      size = lseek(file, 0, SEEK_END);
      lseek(file, 0, SEEK_SET);
      buffer = (char * ) malloc(sizeof(char) * size);

      read(file, buffer, size);

      while (done == 1) {
        if (mode == MODE_ASCII) {
          displayASCII(buffer, size);
        } else if (mode == MODE_HEX) {
          displayHEX(buffer, size);
        }

        printf("\nInput:\n");
        printf("m - return to main menu\n");
        printf("x - exit\n");
        printf("Enter option: ");

        scanf(" %c", & option);

        if (option == 'm') {
          close(file);
          free(buffer);
          break;
        } else if (option == 'x') {
          close(file);
          free(buffer);
          exit(0);
          done = 0;
        } else {
          printf("Invalid input\n");
        }
      }
      break;
    
    case 'd':
      printf("Enter mode (a - ASCII, h - HEX): ");
      scanf(" %c", & option);

      if (option == 'a') {
        mode = MODE_ASCII;
      } else if (option == 'h') {
        mode = MODE_HEX;
      } else {
        printf("Invalid input\n");
      }
      break;
    
    case 'x':
      free(buffer);
      exit(0);
      done = 0;
      break;
    
    default:
      printf("Invalid input\n");
      break;
    }
  }

  return 0;
}


/**
 * It takes a buffer and a length, and prints the buffer to the screen, replacing any non-printable
 * characters with a question mark
 * 
 * @param buffer The buffer to display
 * @param length The length of the buffer.
 */
void displayASCII(char * buffer, int length) {
  printf("\n");
  int i;
  for (i = 0; i < length; i++) {
    if (buffer[i] >= 0x0 && buffer[i] <= 0x9) {
      buffer[i] = 0x20;
    } else if (buffer[i] >= 0xB && buffer[i] <= 0x1F) {
      buffer[i] = 0x20;
    } else if (buffer[i] >= 0x7F) {
      buffer[i] = 0x3F;
    }
    printf("%c", buffer[i]);
  }
  printf("\n");
}

/**
 * It prints out the contents of a buffer in hexadecimal format
 * 
 * @param buffer The buffer to display
 * @param length The length of the buffer.
 */
void displayHEX(char * buffer, int length) {
  printf("\n");
  int i;
  for (i = 0; i < length; i++) {
    if (i % 16 == 0) {
      printf("%07X ", i);
    }
    printf("%02X ", buffer[i]);
    if (i % 8 == 7) {
      printf("  ");
    }
    if (i % 16 == 15) {
      printf("\n");
    }
  }

  printf("\n%07X\n", length);
}