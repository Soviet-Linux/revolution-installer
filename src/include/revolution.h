/*
 * revolution.h
 */

extern int root_setup(); //set up the root password
extern int user_setup(); //create a new user
extern int partition_disk(); //executes cfdisk
extern int make_fs(); //makes new file system on disk
extern int mount_setup(); //specifies mounting points for directories
extern int copy_sys_files(); //copy the system files from the iso to the disk
extern int recompile_kernel(); //recomplies the kernel following user directions
