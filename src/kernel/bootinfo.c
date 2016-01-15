#include <kernel.h>
#include <klib/io.h>

typedef struct multiboot_tag
{
	unsigned int type;
	unsigned int size;
} MULTIBOOT_TAG;

typedef struct multiboot_mmap_entry
{
	unsigned long addr;
	unsigned long len;
	unsigned int type;
	unsigned int zero;
} __attribute__((packed)) MULTIBOOT_MMAP_ENTRY;

typedef struct multiboot_mmap
{
	unsigned int type;
	unsigned int size;
	unsigned int entry_size;
	unsigned int entry_version;
	MULTIBOOT_MMAP_ENTRY entries[0];
} MULTIBOOT_MMAP;

typedef struct multiboot_basic_mem
{
	unsigned int type;
	unsigned int size;
	unsigned int low;
	unsigned int high;
} MULTIBOOT_BASIC_MEM;

typedef struct multiboot_command_line
{
	unsigned int type;
	unsigned int size;
	char cmd;
} MULTIBOOT_CMD_LINE;

typedef struct multiboot_loader
{
	unsigned int type;
	unsigned int size;
	char name;
} MULTIBOOT_LOADER;

typedef struct multiboot_device
{
	unsigned int type;
	unsigned int size;
	unsigned int biosdev;
	unsigned int partition;
	unsigned int sub_partition;
} MULTIBOOT_DEVICE;

void getBootInfo(void * addr)
{
	MULTIBOOT_TAG *tag;
	MULTIBOOT_MMAP_ENTRY *mmap;
	MULTIBOOT_BASIC_MEM *basic_mem;
	MULTIBOOT_CMD_LINE *cmd;
	MULTIBOOT_LOADER *ldr;
	MULTIBOOT_DEVICE *dev;

	int i = 0;

	kmsg(KM_INFO, "Getting Boot Info");

  for (tag = (MULTIBOOT_TAG *) (addr + 8);
			 tag->type != 0;
			 tag = (MULTIBOOT_TAG  *)((unsigned char *) tag + ((tag->size + 7) & ~7))){
		switch(tag->type){
		case 1:
			kmsg(KM_INFO, "Boot Command Line Found");
			cmd = (MULTIBOOT_CMD_LINE *)tag;
			kmsg_lls(KM_INFO, "Command Line: %2", 0, 0, &cmd->cmd);
			break;
		case 2:
			kmsg(KM_INFO, "Boot Loader Name Found");
			ldr = (MULTIBOOT_LOADER *)tag;
			kmsg_lls(KM_INFO, "Booted by %2", 0, 0, &ldr->name);
			break;
		case 3:
			kmsg(KM_INFO, "Module Info Found");
			break;
		case 4:
			basic_mem = (MULTIBOOT_BASIC_MEM *)tag;
			sys_info.memory_low = basic_mem->low;
			sys_info.memory_high = basic_mem->high;
			sys_info.memory_size = basic_mem->high + 1024;
			kmsg_iii(KM_INFO, "Memory Low: %0 kb  High: %1 kb  Total: %2 Mb", basic_mem->low, basic_mem->high, sys_info.memory_size / 1024);
			break;
		case 5:
			dev = (MULTIBOOT_DEVICE *)tag;
			kmsg_iii(KM_INFO, "Boot Device %0  Partition: %1 (%2)", dev->biosdev, dev->partition, dev->sub_partition);
			break;
		case 6:
			kmsg(KM_INFO, "Memory Map");
			for (mmap = ((MULTIBOOT_MMAP *) tag)->entries;
					 (unsigned char *) mmap < (unsigned char *) tag + tag->size;
					 mmap = (MULTIBOOT_MMAP_ENTRY *)((unsigned long) mmap	+ ((MULTIBOOT_MMAP *) tag)->entry_size)) {
				sys_info.memory_map[i].base = mmap->addr;
				sys_info.memory_map[i].len = mmap->len;
				sys_info.memory_map[i].type = mmap->type;

				switch(mmap->type){
				case 1:
					kmsg_lls(KM_INFO, "%0 - %1 (%2)", mmap->addr, mmap->addr + mmap->len, "AVAIL");
					break;
				case 3:
					kmsg_lls(KM_INFO, "%0 - %1 (%2)", mmap->addr, mmap->addr + mmap->len, "ACPI");
					break;
				case 4:
					kmsg_lls(KM_INFO, "%0 - %1 (%2)", mmap->addr, mmap->addr + mmap->len, "RESERV");
					break;
				default:
					kmsg_lls(KM_INFO, "%0 - %1 (%2)", mmap->addr, mmap->addr + mmap->len, "Unknown");
					kmsg_lll(KM_DEBUG, "type-> %1", mmap->type, 0, 0);
				}
				i = i + 1;
			}
			sys_info.memory_map_size = i;
			break;
		case 7:
			kmsg(KM_INFO, "VBE Info Found");
			break;
		case 8:
			kmsg(KM_INFO, "Frame buffer info Found");
			break;
		case 9:
			kmsg(KM_INFO, "ELF-Symbol table Found");
			break;
		case 10:
			kmsg(KM_INFO, "APM Table found");
			break;
		default:
			kmsg_iii(KM_WARNING, "Unknown Information Found (%0)", tag->type, 0, 0);
		}
	}
}
