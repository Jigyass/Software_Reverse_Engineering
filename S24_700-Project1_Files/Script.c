/*
 * @author: Jigyas Sharma
 * @course: Software Reverse Engineering
 * @description: This script takes a file as an input and if the file is an ELF Binary, then it prints out information regarding the file, else it prints an error
 */

//Library Import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

/*
 * @param: null
 * @ret: null
 * @desc: This function just clears the terminal screen for a better viewing experience
 */
void clear_screen() 
{
    system("clear"); // use system("cls") if on windows
}

/*
 * @param: 
 * 	pointer = *section(Pointer to an array of information about ELF Sections)
 * 	pointer = *names(Pointer to an array containing section names)
 * 	integer = index(Index in the array for the section to be displayed)
 * 	unsigned integer = machine(Value represents machine architecture)
 * 	unsigned long integer = entry_point(Address of the entry point of the executable)
 * @ret: null
 * @desc: This function displays the details of the specific ELF section from the file that is being analyzed.
 */
void display_section_details(Elf64_Shdr *sections, char *names, int index, unsigned machine, unsigned long entry_point) {
    clear_screen();
    printf("ELF 64-bit Header:\n");
    printf("  Machine: %u\n", machine);
    printf("  Entry point address: 0x%lx\n\n", entry_point);

    printf("Section %d: %s\n", index, &names[sections[index].sh_name]);
    printf("  Address: 0x%lx\n", sections[index].sh_addr);
    printf("  Permissions: %c%c%c\n",
           (sections[index].sh_flags & SHF_WRITE) ? 'W' : '-',
           (sections[index].sh_flags & SHF_ALLOC) ? 'R' : '-',
           (sections[index].sh_flags & SHF_EXECINSTR) ? 'X' : '-');
}

/*
 * @param:
int process_elf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    Elf64_Ehdr header;
    if (fread(&header, 1, sizeof(header), file) != sizeof(header)) {
        fprintf(stderr, "Failed to read ELF header\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0 || header.e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "This file is not a valid 64-bit ELF file.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    Elf64_Shdr *sections = malloc(header.e_shentsize * header.e_shnum);
    if (!sections) {
        perror("Failed to allocate memory for section headers");
        fclose(file);
        return EXIT_FAILURE;
    }

    fseek(file, header.e_shoff, SEEK_SET);
    if (fread(sections, header.e_shentsize, header.e_shnum, file) != header.e_shnum) {
        fprintf(stderr, "Failed to read section headers\n");
        free(sections);
        fclose(file);
        return EXIT_FAILURE;
    }

    Elf64_Shdr strtab = sections[header.e_shstrndx];
    char *names = malloc(strtab.sh_size);
    fseek(file, strtab.sh_offset, SEEK_SET);
    fread(names, 1, strtab.sh_size, file);

    char response[10];
    printf("Do you want to view section details? (yes/no): ");
    scanf("%9s", response);

    if (strcmp(response, "yes") == 0) {
        int index = 0;
        char command[10];
        while (1) {
            display_section_details(sections, names, index, header.e_machine, header.e_entry);
            printf("Type 'next', 'prev' to navigate, 'exit' to finish: ");
            scanf("%9s", command);
            
            if (strcmp(command, "next") == 0 && index < header.e_shnum - 1) {
                index++;
            } else if (strcmp(command, "prev") == 0 && index > 0) {
                index--;
            } else if (strcmp(command, "exit") == 0) {
                break;
            }
        }
    }

    free(names);
    free(sections);
    fclose(file);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Correct Usage: %s <ELF-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return process_elf(argv[1]);
}

