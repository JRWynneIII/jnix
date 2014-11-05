#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/system.h>
#include <kernel/keyboard.h>

void waitCmd();

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
NODE itoaTest;
NODE cmdForth;
NODE cmdTestTimer;
NODE clear;
int numOfCmds = 9;

void clearCmd()
{
  cls();
}

void initForth()
{
  tcputs("ok\n", COLOR_WHITE);
  for(;;);
}

void testTimer()
{
  tcputs("Testing Timer....\n",COLOR_WHITE);
  int i = 0;
  for (i = 0; i < 10; i++)
  {
    wait(1000);  //wait for 100 milliseconds
    tcputs("TICK\n",COLOR_WHITE);
  }
}

void itoaTestCmd()
{
  int i = 0;
  for (i = 0; i<100; i++)
  {
    tputs(itoa(i));
    tputs("\n");
  }
}

void mallocTestCmd()
{
  tcputs("MallocTest\n", COLOR_WHITE);
  int* testArray = (int*)malloc(5*sizeof(int));
  int test[5] = {1,2,3,4,5};

  tputs("Array is allocated at: ");
  tputs(itoa(testArray));
  tputs("\n");

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
  int* test2 = (int*)malloc(100*sizeof(int));
  int i = 0;
  for (i = 0; i<100; i++)
   test2[i] = i;
  for (i = 0; i<100; i++)
  {
   tputs(itoa(test2[i])); 
  }
  tputs(itoa(test2));
  tputs("\n");
  tputs(itoa(test));
  tputs("\n");
}

void run()
{
  tcputs("Running...\n",COLOR_WHITE);
}

void time()
{
  printPrettyTime();
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
  mallocTest.next = &itoaTest;

  itoaTest.cmd = &itoaTestCmd;
  itoaTest.name = "itoaTest";
  itoaTest.len = 8;
  itoaTest.c1 = 'i';
  itoaTest.c2 = 't';
  itoaTest.c3 = 'o';
  itoaTest.next = &cmdForth;

  cmdForth.cmd = &initForth;
  cmdForth.name = "forth";
  cmdForth.len = 5;
  cmdForth.c1 = 'f';
  cmdForth.c2 = 'o';
  cmdForth.c3 = 'r';
  cmdForth.next = &cmdTestTimer;

  cmdTestTimer.cmd = &testTimer;
  cmdTestTimer.name = "testTimer";
  cmdTestTimer.len = 9;
  cmdTestTimer.c1 = 't';
  cmdTestTimer.c2 = 'e';
  cmdTestTimer.c3 = 's';
  cmdTestTimer.next = &clear;

  clear.cmd = &clearCmd;
  clear.name = "clear";
  clear.len = 5;
  clear.c1 = 'c';
  clear.c2 = 'l';
  clear.c3 = 'e';
  clear.next = NULL;
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
          if (current->len == (strlen(command)))
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
  waitCmd();
}

void waitCmd()
{
  char* cmd;
  gets(cmd);
  putchar('\n');
  runShell(cmd);
}

void init_shell()
{
  getCmdCount();
  populateCommands();
  tcputs("$>> ", COLOR_GREEN);
  irq_install_handler(1, keyboard_handler);
  waitCmd();
}
