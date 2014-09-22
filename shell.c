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
  unsigned int len;
  void (*cmd)();
  char c1;
  char c2;
  char c3;
  char* name;
  struct nodeT* next;
} NODE;

/*SHELL COMMANDS*/
NODE head;
NODE cmdHelp;
NODE cmdInfo;
NODE cmdRun;
NODE mallocTest;
int numOfCmds = 5;

void mallocTestCmd()
{
  tcputs("MallocTest\n", COLOR_WHITE);
  int* testArray = (int*)malloc(5*sizeof(int));
  testArray[0] = 10;
  testArray[1] = 22;
  testArray[2] = 33;
  testArray[3] = 45;
  testArray[4] = 56;

  if (testArray[0] == 10)
    tputs("\tPASS\n");
  else
    tcputs("\tFAIL\n", COLOR_RED);
  if (testArray[1] == 22)
    tputs("\tPASS\n");
  else
    tcputs("\tFAIL\n", COLOR_RED);
  if (testArray[2] == 33)
    tputs("\tPASS\n");
  else
    tcputs("\tFAIL\n", COLOR_RED);
  if (testArray[3] == 45)
    tputs("\tPASS\n");
  else
    tcputs("\tFAIL\n", COLOR_RED);
  if (testArray[4] == 56)
    tputs("\tPASS\n");
  else
    tcputs("\tFAIL\n", COLOR_RED);
}

void run()
{
  tcputs("Running...\n",COLOR_WHITE);
}

void time()
{
  tcputs("Time\n", COLOR_WHITE);
}

void help()
{
  tcputs("Availible Commands:\n",COLOR_WHITE);
  NODE* current = &head;
  for (int i = 0; i < numOfCmds; i++)
  {
    tcputs(current->name, COLOR_WHITE);
    tputs("\n");
    current = current->next;  
  }
}

void info()
{
  tcputs("HobbyOS\nCopyright GPUJake 2014\n", COLOR_WHITE);
}

void getCmdCount()
{
  NODE* current;
  current = &head;
  while (current->next)
  {
    numOfCmds++;
    current = current->next;
  }
}

void populateCommands()
{
  head.cmd = &time;
  head.name = "time";
  head.len = 4;
  head.c1 = 't';
  head.c2 = 'i';
  head.c3 = 'm';
  head.next = &cmdHelp;

  cmdHelp.cmd = &help; 
  cmdHelp.name = "help";
  cmdHelp.len = 4;
  cmdHelp.c1 = 'h';
  cmdHelp.c2 = 'e';
  cmdHelp.c3 = 'l';
  cmdHelp.next = &cmdInfo;

  cmdInfo.cmd = &info;
  cmdInfo.name = "info";
  cmdInfo.len = 4;
  cmdInfo.c1 = 'i';
  cmdInfo.c2 = 'n';
  cmdInfo.c3 = 'f';
  cmdInfo.next = &cmdRun;

  cmdRun.cmd = &run;
  cmdRun.name = "run";
  cmdRun.len = 3;
  cmdRun.c1 = 'r';
  cmdRun.c2 = 'u';
  cmdRun.c3 = 'n';
  cmdRun.next = &mallocTest;

  mallocTest.cmd = &mallocTestCmd;
  mallocTest.name = "mallocTest";
  mallocTest.len = 10;
  mallocTest.c1 = 'm';
  mallocTest.c2 = 'a';
  mallocTest.c3 = 'l';
  mallocTest.next = NULL;
}

void init_shell()
{
  getCmdCount();
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

