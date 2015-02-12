#include <string.h>		// strcmp()
#include <stdio.h>		// print, file, fgetc, fputc
#include <stdlib.h>		// exit
#include <stdbool.h>	// boolean
#include <errno.h>		// perror
#include <unistd.h>		// usleep

#include <libudev.h>			// -ludev
#include <blkid/blkid.h>		// -lblkid
#include <linux/capability.h>	// -lcap
#include <sys/capability.h>		// -lcap
#include <sys/mount.h>			// mount
#include <mntent.h>				// mntent

size_t write_to_jump(const char* mnt_point, const char* filename) {
	printf("WAITUSB :: omf() --> entering with [%s]\n", mnt_point);
//	char* mapfile = "/mnt/map.csv";
//	char* mapfile[256];	// should be large enough. 
	char* file_src  = malloc(256);
	if (file_src == NULL) {
		fprintf(stderr, "WAITUSB :: cannot allocate memory for source filename\n");
		fprintf(stderr, "WAITUSB :: FATAL -- exiting.\n");
		exit(47);
	}

	char* file_dest = malloc(256);
	if (file_src == NULL) {
		fprintf(stderr, "WAITUSB :: cannot allocate memory for destinationfilename\n");
		fprintf(stderr, "WAITUSB :: FATAL -- exiting.\n");
		exit(47);
	}

	// form the destination file name
	// need to find out where the file really is. EMG
	strcpy(file_src, "config");
	strcat(file_src, "/");
	strcat(file_src, filename);

	strcpy(file_dest, mnt_point);
	strcat(file_dest, "/");
	strcat(file_dest, filename);

	FILE* fd_src;
	FILE* fd_dest;
	fd_src  = fopen(file_src,  "r");
	fd_dest = fopen(file_dest, "w");

	if (fd_src == NULL) {
		fprintf(stderr, "WAITUSB :: unable to open SOURCE (%s) reading\n", file_src);
		free(file_src);
		exit(48);
	}

	if (fd_dest == NULL) {
		fprintf(stderr, "WAITUSB :: unable to open DESTINATION (%s) for writing\n", file_dest);
		free(file_src);
		free(file_dest);
		exit(48);
	}
//	char* mapdata;
	size_t len = 0;
	char cp;

	while ( (cp = fgetc(fd_src)) != EOF) {
		fputc(cp, fd_dest);
		len += 1;
	}

	free(file_src);
	free(file_dest);
	return len;
}

//int main(void) {
bool wait_for_usb(const char* filename) {
	// determine correct capabilities first

	cap_t caps = cap_get_proc();
	cap_flag_value_t flag_e, flag_p;

	// if we cannot get any of the needed capabilities, fail and exit
	if (cap_get_flag(caps, CAP_SYS_ADMIN, CAP_EFFECTIVE, &flag_e)) {
		printf ("could not grok effective caps\n");
		exit(41);
	}
	if (cap_get_flag(caps, CAP_SYS_ADMIN, CAP_PERMITTED, &flag_p)) {
		printf ("could not grok permitted caps\n");
		exit(41);
	}
	if (!(flag_e && flag_p)) {
		printf ("required CAP_SYS_ADMIN capabilities not presnt. bailing.\n");
		exit(42);
	}

	flag_e = flag_p = 0;

	if (cap_get_flag(caps, CAP_DAC_READ_SEARCH, CAP_EFFECTIVE, &flag_e)) {
		printf ("could not grok effective caps\n");
		exit(41);
	}
	if (cap_get_flag(caps, CAP_DAC_READ_SEARCH, CAP_PERMITTED, &flag_p)) {
		printf ("could not grok permitted caps\n");
		exit(41);
	}
	if (!(flag_e && flag_p)) {
		printf ("required CAP_DAC_READ_SEARCH capabilities not present. bailing.\n");
		exit(43);
	}

	cap_free(caps);

	struct udev *udev_i;
	struct udev_device *dev_u;

	// open the UDEV bindings to notice when the kernel identifies an action
	udev_i = udev_new();
	if (!udev_i) {
		printf ("could not create udev interface. bailing.\n");
		exit(44);
	}

	struct udev_monitor *monitor;
	int fd;

	monitor = udev_monitor_new_from_netlink(udev_i, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "block", NULL);
	udev_monitor_enable_receiving(monitor);
	fd = udev_monitor_get_fd(monitor);

	ssize_t read = -1;
	bool file_copied = false;
	while (1) {

		fd_set fds;
		struct timeval tv;
		int ret;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(fd+1, &fds, NULL, NULL, &tv);

		if (ret > 0 && FD_ISSET(fd, &fds)) {
			printf ("\nselect() says there should be data\n");

			dev_u = udev_monitor_receive_device(monitor);
			printf ("device action: \t%s\n", udev_device_get_action(dev_u));

			const char* expected = "add";
			if (strcmp(udev_device_get_action(dev_u),expected) == 0) {
				printf ("got add action. acquiring kernel device name: ");
				const char* devname = udev_device_get_devnode(dev_u);
				printf ("%s\n", devname);

				blkid_probe probe;
				probe = blkid_new_probe_from_filename(devname);
				if (!probe) {
					printf ("unable to open %s for probing. bailing\n", devname);
					exit(45);
				}

				blkid_do_probe(probe);
				blkid_partlist part_list;
				int num_parts = 0;
				int i = 0;
				bool mounted = false;

				part_list = blkid_probe_get_partitions(probe);
				num_parts = blkid_partlist_numof_partitions(part_list);

				for (; i < num_parts; i++) {
					if (file_copied)
						break;
/**					blkid_partition part = blkid_partlist_get_partition(part_list, i);
					printf ("#%d: start(%llu), size(%llu) type(0x%x)\n",	\
							blkid_partition_get_partno(part),				\
							blkid_partition_get_start(part),				\
							blkid_partition_get_size(part),					\
							blkid_partition_get_type(part));
**/
					char* partnum = malloc(3);
					char* partname = malloc(10);
					strcpy(partname, devname);
					sprintf(partnum, "%d", (i+1));
					strcat(partname, partnum);
					printf ("partition device name: %s\n", partname);
					probe = blkid_new_probe_from_filename(partname);
					blkid_do_probe(probe);
					const char* fs_type;
					blkid_probe_lookup_value(probe, "TYPE", &fs_type, NULL);
					printf("type(%s)\n", fs_type);
					free(partnum);
//					free(partname);

					// mount
					const char* target = "/mnt";

					if (mount(partname, target, fs_type, (MS_RDONLY | MS_NOATIME | MS_NOSUID | MS_NOEXEC), NULL) < 0) {
						int error_code = errno;
						if (error_code == EBUSY) {
							printf ("device %s busy; likely cause is automounted. finding\n", partname);
							struct mntent *ent;
							FILE *mtab;
							mtab = setmntent("/proc/mounts", "r");
							if (mtab == NULL) {
								perror("mtab search");
								printf("WAITUSB :: mount() :: EBUSY --> can't get mtab. this should be fatal. need better error handling here.\n");
								printf("\tperhaps a fallback mount point search method\n");
								break;
							} else {
								while ((ent = getmntent(mtab)) != NULL) {
//									printf("WAITUSB :: mount() :: EBUSY --> %s %s\n", ent->mnt_fsname, ent->mnt_dir);
									if (strcmp(partname, ent->mnt_fsname) == 0) {
										printf ("WAITUSB :: mount() :: EBUSY --> found %s in mtab mounted at (%s)\n", partname, ent->mnt_dir);
										target = ent->mnt_dir;
										mounted = true;
										break;
									} else {
										// TODO : error handling; need to handle a case where the device isn't in the mtab.
										//			have no clue what this would mean if the device is busy then.
									}
								}	// end(while): get entity from mtab
								endmntent(mtab);
							}	// end(else): the case where it was EBUSY
						} else {
							// this handles all other mount errnos
							perror("probe_mount");
							continue;
						}
					} else {
						// mount succeeded
						mounted = true;
					}

					free(partname);

					if (mounted) {
						if ( (write_to_jump(target, filename)) > 0 ) {
							// successful, unmount
							if (umount(target) < 0) {
								fprintf(stderr, "WAITUSB :: unable to unmount (%s).\n", target);
								fprintf(stderr, "WAITUSB :: please fix this by hand.\n");
								fprintf(stderr, "WAITUSB :: NON-fatal to operation - continuing\n");
							}
							// complete success, unmounted and good to go.
							blkid_free_probe(probe);
							return true;
						} else {
							blkid_free_probe(probe);
							return false;
						}
					}
				} // end FOR(partition scanning)

				blkid_free_probe(probe);
				// only want to look at first device reported by kernel.
				break;
			} // end if(UDEV_ACTION(ADD))
		}

		// this will sleep for an amount of time in between actions (scans)
		usleep(250*1000);	// granularity: microseconds. (10^6 useconds / second)
		printf(".");
		fflush(stdout);
	}
	return false;
}
