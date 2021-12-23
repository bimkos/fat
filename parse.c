#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct BIOS {
	unsigned char jmp[3]; // offset 0x00
	unsigned char oem[8]; // offset 0x03
	unsigned char bps[2]; // offset 0x0b
	unsigned char spc[1]; // offset 0x0d
	unsigned char res[2]; // offset 0x0e
	unsigned char nof[1]; // offset 0x10
	unsigned char nod[2]; // offset 0x11
	unsigned char slv[2]; // offset 0x13
	unsigned char mdt[1]; // offset 0x15
	unsigned char spf[2]; // offset 0x16
	unsigned char spt[2]; // offset 0x18
	unsigned char nhs[2]; // offset 0x1A
	unsigned char noh[4]; // offset 0x1c
	unsigned char lsc[4]; // offset 0x20
} bios;

void print_hex(char * buff, int count) {
	for (int i = 0; i < count; i++) {
		printf("%02x ", (unsigned char)buff[i]);
	}
}

void parse_bios(char * buff) {
	memcpy(bios.jmp, buff + 0x00, 3);
	memcpy(bios.oem, buff + 0x03, 8);
	memcpy(bios.bps, buff + 0x0b, 2);
	memcpy(bios.spc, buff + 0x0d, 1);
	memcpy(bios.res, buff + 0x0e, 2);
	memcpy(bios.nof, buff + 0x10, 1);
	memcpy(bios.nod, buff + 0x11, 2);
	memcpy(bios.slv, buff + 0x13, 2);
	memcpy(bios.mdt, buff + 0x15, 1);
	memcpy(bios.spf, buff + 0x16, 2);
	memcpy(bios.spt, buff + 0x18, 2);
	memcpy(bios.nhs, buff + 0x1a, 2);
	memcpy(bios.noh, buff + 0x1c, 4);
	memcpy(bios.lsc, buff + 0x20, 4);

	printf("###### BIOS Parameter Block ######\n");
	printf("jmp:                   %02x %02x %02x\n", bios.jmp[0], bios.jmp[1], bios.jmp[2]);
	printf("oem:                   %02x %02x %02x %02x %02x %02x %02x %02x\n", bios.oem[0], bios.oem[1], bios.oem[2], bios.oem[3], bios.oem[4], bios.oem[5], bios.oem[6], bios.oem[7]);
	printf("bytes per sector:      %02x %02x\n", bios.bps[0], bios.bps[1]);
	printf("sectors per cluster:   %02x\n", bios.spc[0]);
	printf("reserved sectors:      %02x %02x\n", bios.res[0], bios.res[1]);
	printf("fats number:           %02x\n", bios.nof[0]);
	printf("directory entries:     %02x %02x\n", bios.nod[0], bios.nod[1]);
	printf("total sectors:         %02x %02x\n", bios.slv[0], bios.slv[1]);
	printf("media descriptor type: %02x\n", bios.mdt[0]);
	printf("sectors per fat:       %02x %02x\n", bios.spf[0], bios.spf[1]);
	printf("sectors per track:     %02x %02x\n", bios.spt[0], bios.spt[1]);
	printf("heads of sides:        %02x %02x\n", bios.nhs[0], bios.nhs[1]);
	printf("hidden sectors:        %02x %02x %02x %02x\n", bios.noh[0], bios.noh[1], bios.noh[2], bios.noh[3]);
	printf("large sector count:    %02x %02x %02x %02x\n", bios.lsc[0], bios.lsc[1], bios.lsc[2], bios.lsc[3]);
}


int main(int argc, char * argv[]) {
	int fd;
	unsigned char buffer [1024 + 1];
	fd = open(argv[1], O_RDONLY);
	read(fd, buffer, 32);
	parse_bios(buffer);
	return 0;
}
