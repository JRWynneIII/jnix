#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_handler(struct regs *r);

bool enter = false;

extern uint16_t keyboard_isEnter;

#endif
