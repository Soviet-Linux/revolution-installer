/*
 * revolution.h
 */

typedef struct partition_node {
    char* path;
    char* mnt_point;
    char* fs;
    struct partition_node *next;
} part;

typedef struct partition_list {
    part *first;
} p_list;

extern int root_setup(); //set up the root password
extern int user_setup(); //create a new user
extern int make_fs(char* fs, char* disk); //makes new file system on disk
extern int mount_setup(p_list *list); //specifies mounting points for directories
extern int copy_sys_files(char *sq_path, char *target); //copy the system files from the iso to the disk
extern int recompile_kernel(); //recompiles the kernel following user directions
extern int generate_fstab(p_list* list); //generates /etc/fstab
extern int dpart_loop(); //disk partition prompt loop
extern int list_dev();
extern int fs_loop(p_list *list);
extern int mount_root(p_list *list);
extern int mount_dev(p_list *list);
extern int mount_virtkfs();
extern int move_boot_dir();
extern int create_grub_conf(p_list* list);
