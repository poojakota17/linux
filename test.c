#include <stdio.h>
#include <string.h>
#include <linux/module.h>     /* Needed by all modules */
#include <linux/kernel.h>

int main()
{
  __uint64_t a = 0x4FFFFFFE;
  __uint64_t b, c, d;
  int i;
  for (i = 0; i < 66; i++) {
      __asm__ __volatile__("mov $0x4FFFFFFE, %eax\n\t");
    if (i == 0) { __asm__ __volatile__("mov $0, %ecx\n\t"); }
    else if (i == 1) {  __asm__ __volatile__("mov $1, %ecx\n\t"); }
    else if (i == 2) {  __asm__ __volatile__("mov $2, %ecx\n\t"); }
    else if (i == 3) {  __asm__ __volatile__("mov $3, %ecx\n\t"); }
    else if (i == 4) {  __asm__ __volatile__("mov $4, %ecx\n\t"); }
    else if (i == 5) {  __asm__ __volatile__("mov $5, %ecx\n\t"); }
    else if (i == 6) { __asm__ __volatile__("mov $6, %ecx\n\t"); }
    else if (i == 7) {  __asm__ __volatile__("mov $7, %ecx\n\t"); }
    else if (i == 8) { __asm__ __volatile__("mov $8, %ecx\n\t"); }
    else if (i == 9) { __asm__ __volatile__("mov $9, %ecx\n\t"); }
    else if (i == 10) { __asm__ __volatile__("mov $10, %ecx\n\t"); }
    else if (i == 11) {__asm__ __volatile__("mov $11, %ecx\n\t"); }
    else if (i == 12) {  __asm__ __volatile__("mov $12, %ecx\n\t"); }
    else if (i == 13) {__asm__ __volatile__("mov $13, %ecx\n\t"); }
    else if (i == 14) { __asm__ __volatile__("mov $14, %ecx\n\t"); }
    else if (i == 15) { __asm__ __volatile__("mov $15, %ecx\n\t"); }
    else if (i == 16) { __asm__ __volatile__("mov $16, %ecx\n\t"); }
    else if (i == 17) { __asm__ __volatile__("mov $17, %ecx\n\t"); }
    else if (i == 18) { __asm__ __volatile__("mov $18, %ecx\n\t"); }
    else if (i == 19) { __asm__ __volatile__("mov $19, %ecx\n\t"); }
    else if (i == 20) { __asm__ __volatile__("mov $20, %ecx\n\t"); }
    else if (i == 21) { __asm__ __volatile__("mov $21, %ecx\n\t"); }
    else if (i == 22) { __asm__ __volatile__("mov $22, %ecx\n\t"); }
    else if (i == 23) {  __asm__ __volatile__("mov $23, %ecx\n\t"); }
    else if (i == 24) {  __asm__ __volatile__("mov $24, %ecx\n\t"); }
    else if (i == 25) { __asm__ __volatile__("mov $25, %ecx\n\t"); }
    else if (i == 26) {  __asm__ __volatile__("mov $26, %ecx\n\t"); }
    else if (i == 27) {  __asm__ __volatile__("mov $27, %ecx\n\t"); }
    else if (i == 28) {  __asm__ __volatile__("mov $28, %ecx\n\t"); }
    else if (i == 29) {  __asm__ __volatile__("mov $29, %ecx\n\t"); }
    else if (i == 30) {  __asm__ __volatile__("mov $30, %ecx\n\t"); }
    else if (i == 31) { __asm__ __volatile__("mov $31, %ecx\n\t"); }
    else if (i == 32) {__asm__ __volatile__("mov $32, %ecx\n\t"); }
    else if (i == 33) { __asm__ __volatile__("mov $33, %ecx\n\t"); }
    else if (i == 34) { __asm__ __volatile__("mov $34, %ecx\n\t"); }
    else if (i == 35) { __asm__ __volatile__("mov $35, %ecx\n\t"); }
    else if (i == 36) { __asm__ __volatile__("mov $36, %ecx\n\t"); }
    else if (i == 37) { __asm__ __volatile__("mov $37, %ecx\n\t"); }
    else if (i == 38) {__asm__ __volatile__("mov $38, %ecx\n\t"); }
    else if (i == 39) { __asm__ __volatile__("mov $39, %ecx\n\t"); }
    else if (i == 40) { __asm__ __volatile__("mov $40, %ecx\n\t"); }
    else if (i == 41) { __asm__ __volatile__("mov $41, %ecx\n\t"); }
    else if (i == 42) {__asm__ __volatile__("mov $42, %ecx\n\t"); }
    else if (i == 43) {__asm__ __volatile__("mov $43, %ecx\n\t"); }
    else if (i == 44) {__asm__ __volatile__("mov $44, %ecx\n\t"); }
    else if (i == 45) { __asm__ __volatile__("mov $45, %ecx\n\t"); }
    else if (i == 46) { __asm__ __volatile__("mov $46, %ecx\n\t"); }
    else if (i == 47) {__asm__ __volatile__("mov $47, %ecx\n\t"); }
    else if (i == 48) { __asm__ __volatile__("mov $48, %ecx\n\t"); }
    else if (i == 49) { __asm__ __volatile__("mov $49, %ecx\n\t"); }
    else if (i == 50) {__asm__ __volatile__("mov $50, %ecx\n\t"); }
    else if (i == 51) { __asm__ __volatile__("mov $51, %ecx\n\t"); }
    else if (i == 52) { __asm__ __volatile__("mov $52, %ecx\n\t"); }
    else if (i == 53) {__asm__ __volatile__("mov $53, %ecx\n\t"); }
    else if (i == 54) { __asm__ __volatile__("mov $54, %ecx\n\t"); }
    else if (i == 55) {__asm__ __volatile__("mov $55, %ecx\n\t"); }
    else if (i == 56) { __asm__ __volatile__("mov $56, %ecx\n\t"); }
    else if (i == 57) { __asm__ __volatile__("mov $57, %ecx\n\t"); }
    else if (i == 58) {__asm__ __volatile__("mov $58, %ecx\n\t"); }
    else if (i == 59) { __asm__ __volatile__("mov $59, %ecx\n\t"); }
    else if (i == 60) { __asm__ __volatile__("mov $60, %ecx\n\t"); }
    else if (i == 61) { __asm__ __volatile__("mov $61, %ecx\n\t"); }
    else if (i == 62) { __asm__ __volatile__("mov $62, %ecx\n\t"); }
    else if (i == 63) { __asm__ __volatile__("mov $63, %ecx\n\t"); }
    else if (i == 64) {__asm__ __volatile__("mov $64, %ecx\n\t"); }
    else if (i == 65) { __asm__ __volatile__("mov $65, %ecx\n\t"); }
    else if (i == 66) { __asm__ __volatile__("mov $66, %ecx\n\t"); }
    else if (i == 67) { __asm__ __volatile__("mov $67, %ecx\n\t"); }
    else if (i == 68) { __asm__ __volatile__("mov $68, %ecx\n\t"); }
    __asm__ __volatile__("cpuid"
                   :"=a"(a), "=b"(b), "=c"(c), "=d"(d)
                   );
    printf("CPUID(0x4FFFFFFF)   Exits for exit = %d = %ld\t\n",i, a);
  }
  return 0;
}
