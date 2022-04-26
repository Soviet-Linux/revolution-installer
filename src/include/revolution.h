/*
 * revolution.h
 */

struct user_acc {
    char* uname;
    char* pword;
};

struct part {
    char* dev;
    char* mnt_point;
    char* fs;
};

typedef struct {
    char* root_pw;
    struct user_acc* user;
    struct part* part_list;
    char* kb_layout;
    char* hostname;
    char* locale;
    char* tzone;
    char* grub_install;
} instal_conf;

extern int root_setup(); //set up the root password
extern int user_setup(); //create a new user
extern int partition_disk(char choice, char* disk); //executes cfdisk
extern int make_fs(char* fs, char* disk); //makes new file system on disk
extern int mount_setup(); //specifies mounting points for directories
extern int copy_sys_files(); //copy the system files from the iso to the disk
extern int recompile_kernel(); //recompiles the kernel following user directions
extern int generate_fstab(char* part, char* fs); //generates /etc/fstab
