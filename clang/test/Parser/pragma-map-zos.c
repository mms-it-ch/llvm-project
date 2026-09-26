// RUN: %clang_cc1 -triple s390x-ibm-zos -fsyntax-only -verify %s

#pragma map // expected-warning {{missing '(' after '#pragma map' - ignoring}}
#pragma map( // expected-warning {{expected identifier in '#pragma map' - ignored}}
#pragma map(f // expected-warning {{expected ',' in '#pragma map'}}
#pragma map(f, g) // expected-warning {{expected string literal in '#pragma map' - ignoring}}
#pragma map(f, "") // expected-warning {{expected string literal in '#pragma map' - ignoring}}
#pragma map(f, "F" // expected-warning {{missing ')' after '#pragma map' - ignoring}}
#pragma map(f, "F") x // expected-warning {{extra tokens at end of '#pragma map' - ignored}}
#pragma map(f, "F")
void f(void);
