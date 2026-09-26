// RUN: %clang_cc1 -triple s390x-ibm-zos -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -triple s390x-linux-gnu -emit-llvm -Wunknown-pragmas -verify=linux -o - %s | FileCheck --check-prefix=LINUX %s

// Before the declaration; escape sequences are EBCDIC code points
// (\174 = X'7C' = '@', \x7C likewise), other characters are taken as written.
#pragma map(before, "\174\174BEFORE") // linux-warning {{unknown pragma ignored}}
int before(int);

// After the declaration.
int after(int);
#pragma map(after, "\x7C_AFTER") // linux-warning {{unknown pragma ignored}}

// Variables are mapped as well.
extern int var;
#pragma map(var, "VARNAME") // linux-warning {{unknown pragma ignored}}

int use(void) { return before(1) + after(2) + var; }

// CHECK: @VARNAME = external
// CHECK: call{{.*}} @"@@BEFORE"(
// CHECK: call{{.*}} @"@_AFTER"(
// CHECK: declare{{.*}} @"@@BEFORE"(
// CHECK: declare{{.*}} @"@_AFTER"(

// LINUX: call{{.*}} @before(
// LINUX: call{{.*}} @after(
