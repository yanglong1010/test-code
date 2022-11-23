#include <sys/auxv.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    void *vdso = (uintptr_t) getauxval(AT_SYSINFO_EHDR);
    printf("vdso %p\n", vdso);

    Elf64_Ehdr *ptr = (Elf64_Ehdr *)vdso;
    printf("elf header %p\n", ptr);

    Elf64_Phdr *ph = (Elf64_Phdr *)((char*)ptr + ptr->e_phoff);
    printf("program header ptr %p\n", ph);

    int i;
    for (i = 0; i < ptr->e_phnum; i++) {
        printf("program header %d : type=%d vaddr=%p\n", i + 1, ph->p_type, ph->p_vaddr);
        ph++;
    }

    while (1) {
	sleep(1);
    }
}
