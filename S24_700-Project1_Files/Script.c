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
#include <ctype.h>
#include <unistd.h>

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
 *  pointer = *hdr(Pointer to Elf64_Ehdr structure containing information about the elf binary)
 * @ret: null
 * @desc: This function prints all the information in the structure Elf64_Ehdr.
 */
void AllInfo(const Elf64_Ehdr *hdr) 
{
    printf("ELF Header Information:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", hdr->e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             %u\n", hdr->e_ident[EI_CLASS]);
    printf("  Data:                              %u\n", hdr->e_ident[EI_DATA]);
    printf("  Version:                           %u\n", hdr->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %u\n", hdr->e_ident[EI_OSABI]);
    printf("  ABI Version:                       %u\n", hdr->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %u\n", hdr->e_type);
    printf("  Machine:                           %u\n", hdr->e_machine);
    printf("  Version:                           0x%x\n", hdr->e_version);
    printf("  Entry point address:               0x%lx\n", hdr->e_entry);
    printf("  Start of program headers:          %lu (bytes into file)\n", hdr->e_phoff);
    printf("  Start of section headers:          %lu (bytes into file)\n", hdr->e_shoff);
    printf("  Flags:                             %u\n", hdr->e_flags);
    printf("  Size of this header:               %u (bytes)\n", hdr->e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", hdr->e_phentsize);
    printf("  Number of program headers:         %u\n", hdr->e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", hdr->e_shentsize);
    printf("  Number of section headers:         %u\n", hdr->e_shnum);
    printf("  Section header string table index: %u\n", hdr->e_shstrndx);
}

/*
 * @param:
 *  pointer = *sections(Pointer to an Elf64_Shdr structure containing section information)
 *  pointer = *names(Pointer to string array containing section names)
 *  integer = num_sections(Number of sections that are in the ELF binary)
 * @ret: null
 * @desc: This function prints the names of all sections present in the ELF binary.
 */
void PrintAllSections(Elf64_Shdr *sections, char *names, int num_sections) {
    printf("All Section Names:\n");
    for (int i = 0; i < num_sections; i++) {
        printf("Section: %s\n", &names[sections[i].sh_name]);
    }
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
void DisplaySection(Elf64_Shdr *sections, char *names, int index, unsigned machine, unsigned long entry_point) 
{
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
 * 	pointer = *filename(Pointer to a string that holds the filename which was passed as an argument to the main function)
 * @ret: integer = return EXIT_SUCCESS if the file is a ELF binary and the process information regarding the binary, else returns EXIT_FAILURE if the file is not an ELF Binary)
 * @desc: This function processes a 64-bit ELF binary and then stores the information about the file which can be viewed using DisplaySection.
 */ 
int process_elf(const char *filename) 
{
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
    printf("This is a valid ELF Binary!\n");
    AllInfo(&header);
    printf("Type \"all\" to view all section information at once or \"view\" to go through each section yourself or \"sections\" to print all section names: ");
    scanf("%9s", response);

    if (strcmp(response, "all") == 0) 
    {
        for (int i = 0; i < header.e_shnum; i++) 
        {
            DisplaySection(sections, names, i, header.e_machine, header.e_entry);
        }
    } 
    else if (strcmp(response, "sections") == 0)
    {
        PrintAllSections(sections, names, header.e_shnum);
    }
    else if (strcmp(response, "view") == 0) 
    {
        int index = 0;
        char command[10];
        while (1) 
        {
            clear_screen();
            DisplaySection(sections, names, index, header.e_machine, header.e_entry);
            printf("Enter 'next', 'prev', a section number (0 to %d), or 'exit' to finish: ", header.e_shnum - 1);
            scanf("%9s", command);
            
            if (strcmp(command, "next") == 0 && index < header.e_shnum - 1) 
            {
                index++;
            } 
            else if (strcmp(command, "prev") == 0 && index > 0) 
            {
                index--;
            } 
            else if (isdigit(command[0])) 
            {
                int new_index = atoi(command);
                if (new_index >= 0 && new_index < header.e_shnum) 
                {
                    index = new_index;
                } 
                else 
                {
                    printf("Invalid section number! Please enter a number between 0 and %d.\n", header.e_shnum - 1);
                }
            } 
            else if (strcmp(command, "exit") == 0) 
            {
                break;
            }
        }
    }
    else
    {
        exit(0);
    }
    
    free(names);
    free(sections);
    fclose(file);
    return EXIT_SUCCESS;
}

/*
 * @param:
 *	integer = argc(Number of command line arguments)
 *	pointer = *argv(Pointer to an array of strings that hold each argument as a string)
 * @ret: int = returns EXIT_FAILURE if program is not run correctly, else inherits return from process_elf()
 * @desc: This is the main function of the program, it checks the correct usage of the program and then passes the argument to the process_elf().
 */
int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Correct Usage: %s <ELF-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return process_elf(argv[1]);
}

