#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

/*
 * 0:   8d 04 37                lea    eax, [rdi + rsi * 1]
 * 3:   c3                      ret    
 */
const uint8_t shellcode[] = { 0x8d, 0x04, 0x37, 0xc3 };

int main(int argc, const char* argv[])
{
	size_t length = sizeof(shellcode);
	uint8_t* memory = mmap(NULL, length, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	memcpy(memory, shellcode, length);
	mprotect(memory, length, PROT_EXEC);

	int (*f)(int, int) = (int (*)(int, int)) memory;

	int a = 24;
	int b = 7;
	int y = f(a, b);
	printf("addme(%d, %d) = %d\n", a, b, y);

	return 0;
}
