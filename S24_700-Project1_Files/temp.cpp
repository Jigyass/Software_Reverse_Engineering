#include<iostream>
#include<fstream>
#include <libelf.h>
#include <fcntl.h>
#include <gelf.h>
#include <unistd.h>

void checkAndPrintELF(const char* filePath) {
    int fd;
    Elf *elf;
    Elf_Scn *scn = nullptr;
    GElf_Shdr shdr;
    Elf_Data *data;
    if (elf_version(EV_CURRENT) == EV_NONE)
        std::cerr << "ELF library initialization failed: " << elf_errmsg(-1) << std::endl;

    fd = open(filePath, O_RDONLY, 0);
    if (fd < 0) {
        std::cerr << "Error: File does not exist.\n";
        return;
    }

    elf = elf_begin(fd, ELF_C_READ, nullptr);
    if (gelf_getehdr(elf, new GElf_Ehdr()) == nullptr) {
        std::cerr << "Error: File is not a valid ELF file.\n";
        close(fd);
        elf_end(elf);
        return;
    }

    std::cout << "File is a valid ELF file.\n";
    while ((scn = elf_nextscn(elf, scn)) != nullptr) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            std::cerr << "Error reading section header.\n";
            continue;
        }

        std::cout << elf_strptr(elf, shdr.sh_name, shdr.sh_name) << ": ";
        if (shdr.sh_flags & SHF_WRITE) std::cout << "W";
        if (shdr.sh_flags & SHF_ALLOC) std::cout << "A";
        if (shdr.sh_flags & SHF_EXECINSTR) std::cout << "E";
        std::cout << std::endl;
    }

    close(fd);
    elf_end(elf);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    checkAndPrintELF(argv[1]);
    return 0;
}

