#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/system.h>
#include <kernel/keyboard.h>
#include <kernel/pci.h>

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

typedef struct subClassNode
{
  uint8_t data;
  struct treeNode* child0 = NULL;
  struct treeNode* child1 = NULL;
  struct treeNode* child2 = NULL;
  struct treeNode* child3 = NULL;
  struct treeNode* child4 = NULL;
  struct treeNode* child5 = NULL;
  struct treeNode* child6 = NULL;
  struct treeNode* child7 = NULL;
  struct treeNode* child8 = NULL;
  struct treeNode* child9 = NULL;
} subClassNODE;

typedef struct progIFNode
{
  uint8_t data;
  struct progIF* child0;
  struct progIF* child1;
  struct progIF* child2;
  struct progIF* child3;
  struct progIF* child4;
  struct progIF* child5;
  struct progIF* child6;
} progIFNODE;

typedef struct discNode
{
  char* data;
} discNODE;

typedef struct classList
{
  uint8_t data;
  subClassNode* subnode;
  struct classList * next;
} classNODE;

/*Nodes for head*/
classNODE Head;
subClassNODE headSub;
subClassNODE headSubChild0;
subClassNODE headSubChild1;
progIFNODE hsc0PIF0;
progIFNODE hsc1PIF0;
discNODE headDisc0;
discNODE headDisc1;

/*Nodes for 0x01*/
classNODE CC1;
subClassNODE CC1Sub;

subClassNODE CC1Sub0;
progIFNODE CC1Sub0_IF
discNODE CC1SUB0_DISC

subClassNODE CC1Sub1;
progIFNODE CC1Sub1_IF
discNODE CC1SUB1_DISC

subClassNODE CC1Sub2;
progIFNODE CC1Sub2_IF
discNODE CC1SUB2_DISC

subClassNODE CC1Sub3;
progIFNODE CC1Sub3_IF
discNODE CC1SUB3_DISC

subClassNODE CC1Sub4;
progIFNODE CC1Sub4_IF
discNODE CC1SUB4_DISC

subClassNODE CC1Sub5;
progIFNODE CC1Sub5_IF_0
discNODE CC1SUB5_DISC_0
progIFNODE CC1Sub5_IF_1
discNODE CC1SUB5_DISC_1

subClassNODE CC1Sub6;
progIFNODE CC1Sub6_IF_0
discNODE CC1SUB6_DISC
progIFNODE CC1Sub6_IF_1
discNODE CC1SUB6_DISC

subClassNODE CC1Sub7;
progIFNODE CC1Sub7_IF
discNODE CC1SUB7_DISC

subClassNODE CC1Sub80;
progIFNODE CC1Sub80_IF
discNODE CC1SUB80_DISC


void assembleIDStructure()
{
  /*Structure for class Code 0x00*/
  Head.data = 0x00;
  Head.subnode = &headSub;
  Head.next = &CC1
  
  headSub.data = NULL;
  headSub.child0 = &,headSubChild0;
  headSub.child1 = &headSubChild1;

  headSubChild0.data = 0x00;
  headSubChild1.data = 0x01;
  headSubChild0.child0 = &hsc0PIF0;
  headSubChild1.child0 = &hsc1PIF0;
  
  hsc0PIF0.child0 = &headDisc0;
  hsc0PIF1.child0 = &headDisc1;

  headDisc0.data = "Non VGA Device\0";
  headDisc1.data = "VGA compatable Device\0";
  
  /*Structure for class code 0x01*/
  CC1.data = 0x01;
  CC1.subnode = &CC1Sub;




}
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
  uint32_t address;
  uint32_t lbus = (uint32_t)bus;
  uint32_t lslot = (uint32_t)slot;
  uint32_t lfunc = (uint32_t)func;
  uint16_t tmp = 0;

  //create address packet
  address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
  outl(CONFIG_ADDRESS, address);
  tmp = (uint16_t)((inl(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
  return tmp;
}

uint16_t pciCheckVendor(uint8_t bus, uint8_t slot, uint8_t function)
{
  uint16_t vendor, device;

  //if vendor is 0xFFFF then it is non-existant i.e. no device
  if ((vendor = pciConfigReadWord(bus,slot,function,0)) != 0xFFFF)
  {
    device = pciConfigReadWord(bus,slot,function,2);
  }
  return vendor;
}

void checkFunction(uint8_t bus, uint8_t device, uint8_t function)
{
	
}

uint8_t getHeaderType(uint8_t bus, uint8_t device, uint8_t function)
{
  uint8_t header = 11;
  header = pciConfigReadWord(bus,device,function,3);
  return header;
}

void init_PCI()
{
}

void checkDevice(uint8_t bus, uint8_t device)
{
  uint8_t function = 0;
  uint8_t vendor, headerType;

  vendor = pciCheckVendor(bus, device, function);
  if (vendor == 0xFFFF) return;
  checkFunction(bus,device,function);
  headerType = getHeaderType(bus,device,function);
  if ((headerType & 0x80) != 0)
  {
    for (function = 1; function < 8; function++)
      if(pciCheckVendor(bus,device,function) != 0xFFFF) checkFunction(bus,device,function);
  }
}


