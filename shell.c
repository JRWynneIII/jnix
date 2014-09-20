#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#include "include/keyboard.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

typedef struct node
{
  void (*cmd)();
  char* name;
  struct node* next;
} NODE;

/*SHELL COMMANDS*/
NODE head;
NODE cmdHelp;
NODE cmdInfo;
int numOfCmds = 3;

void time()
{
  tcputs("\nTime\n", COLOR_WHITE);
}

void help()
{
  tcputs("\nHelp\n",COLOR_WHITE);
}

void info()
{
  tcputs("\nHobbyOS\nCopyright GPUJake 2014\n", COLOR_WHITE);
}

void populateCommands()
{
  head.cmd = &time;
  head.name = "time";
  head.next = &help;

  cmdHelp.cmd = &help; 
  cmdHelp.name = "help";
  cmdHelp.next = &info;

  cmdInfo.cmd = &info;
  cmdInfo.name = "info";
  cmdInfo.next = NULL;
}

void init_shell()
{
	tcputs("$>> ", COLOR_GREEN);
	irq_install_handler(1, keyboard_handler);
}

NODE* findCommand(char* command)
{
  int i = 0;
  for (i = 0; i< numOfCmds; i++)
  {
    NODE* current;
    current = &head;
    if (current->name == command)
      return current;
    else
      current = current->next;
  }
}

void runShell(char* command)
{
  NODE* cmd;
  cmd = findCommand(command);
  cmd->cmd();
	tcputs("$>> ", COLOR_GREEN);
}

