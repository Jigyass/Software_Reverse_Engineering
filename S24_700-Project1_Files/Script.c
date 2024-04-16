#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Read the ELF header
    Elf64_Ehdr header;
    if (fread(&header, 1, sizeof(header), file) != sizeof(header)) {
        fprintf(stderr, "Failed to read ELF header\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Check for valid ELF magic number
    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "This is not an ELF file.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Check for 64-bit ELF binary
    if (header.e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "This file is not a 64-bit ELF binary.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("ELF 64-bit Header:\n");
    printf("  Machine: %u\n", header.e_machine);
    printf("  Entry point address: 0x%lx\n", header.e_entry);

    // Reading section headers
    Elf64_Shdr *sec_headers = malloc(header.e_shentsize * header.e_shnum);
    if (!sec_headers) {
        perror("Failed to allocate memory for section headers");
        fclose(file);
        return EXIT_FAILURE;
    }

    fseek(file, header.e_shoff, SEEK_SET);
    if (fread(sec_headers, header.e_shentsize, header.e_shnum, file) != header.e_shnum) {
        fprintf(stderr, "Failed to read section headers\n");
        free(sec_headers);
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < header.e_shnum; i++) {
        printf("Section %d: offset 0x%lx, size 0x%lx\n", i, sec_headers[i].sh_offset, sec_headers[i].sh_size);
    }

    free(sec_headers);
    fclose(file);
    return EXIT_SUCCESS;
}

