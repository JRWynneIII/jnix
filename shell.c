#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#include "include/keyboard.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif


typedef struct nodeT
{
  int len;
  void (*cmd)();
  char c1;
  char c2;
  char c3;
  struct nodeT* next;
}NODE;

/*SHELL COMMANDS*/
NODE head;
NODE cmdHelp;
NODE cmdInfo;
int numOfCmds = 3;

void time()
{
  tcputs("Time\n", COLOR_WHITE);
}

void help()
{
  tcputs("Help\n",COLOR_WHITE);
}

void info()
{
  tcputs("HobbyOS\nCopyright GPUJake 2014\n", COLOR_WHITE);
}

void populateCommands()
{
  head.cmd = &time;
  head.len = 4;
  head.c1 = 't';
  head.c2 = 'i';
  head.c3 = 'm';
  head.next = &cmdHelp;

  cmdHelp.cmd = &help; 
  cmdHelp.len = 4;
  cmdHelp.c1 = 'h';
  cmdHelp.c2 = 'e';
  cmdHelp.c3 = 'l';
  cmdHelp.next = &cmdInfo;

  cmdInfo.cmd = &info;
  cmdInfo.len = 4;
  cmdInfo.c1 = 'i';
  cmdInfo.c2 = 'n';
  cmdInfo.c3 = 'f';
  cmdInfo.next = NULL;
}

void init_shell()
{
  populateCommands();
	tcputs("$>> ", COLOR_GREEN);
	irq_install_handler(1, keyboard_handler);
}

NODE* findCommand(char* command)
{
  int i = 0;
  NODE* current;
  current = &head;
  for(i = 0; i<numOfCmds; i++)//while(current->next)
  {
    if (current->c1 == command[0])
    {
      if (current->c2 == command[1])
      {
        if (current->c3 == command[2])
        {
          if (current->len == (strlen(command)-1))
          {
            return current;
          }
        }
      }
    }
    current = current->next;
  }
  tcputs("ERROR COMMAND NOT FOUND\n", COLOR_RED);
  return NULL;
}

void runShell(char* command)
{
  NODE* cmd;
  cmd = findCommand(command);
  if (cmd)
    cmd->cmd();
	tcputs("$>> ", COLOR_GREEN);
}

