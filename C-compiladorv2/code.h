#ifndef _CODE_H_
#define _CODE_H_

#include "cgen.h"

void emitSpaces(int indent);

void emitComment(const char * c, int indent);

void emitCode(const char * c);

const char * toString(enum instrucao i);

void emitObjectCode(const char * c, int indent);

#endif
