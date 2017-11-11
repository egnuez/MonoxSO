#include "stdlib/include/stdlib.h"

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct fs_node;

typedef uint32 (*read_type_t)(struct fs_node*,uint32,uint32,uint8*);
typedef uint32 (*write_type_t)(struct fs_node*,uint32,uint32,uint8*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef struct fs_node {
    char name[128];     // The filename.
    uint32 mask;        // The permissions mask.
    uint32 uid;         // The owning user.
    uint32 gid;         // The owning group.
    uint32 flags;       // Includes the node type. See #defines above.
    uint32 inode;       // This is device-specific - provides a way for a filesystem to identify files.
    uint32 length;      // Size of the file, in bytes.
    uint32 impl;        // An implementation-defined number.
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;
    struct fs_node *ptr; // Used by mountpoints and symlinks.
} fs_node_t;

struct dirent {
    char name[128]; // Filename.
    uint32 ino;     // Inode number. Required by POSIX.
};

fs_node_t *fs_root = 0; // The root of the filesystem.

uint32 read_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer){
    // Has the node got a read callback?
    if (node->read != 0)
        return node->read(node, offset, size, buffer);
    else
        return 0;
}

uint32 write_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer){
    // Has the node got a write callback?
    if (node->write != 0)
        return node->write(node, offset, size, buffer);
    else
        return 0;
}

void open_fs(fs_node_t *node, uint8 read, uint8 write){
    // Has the node got an open callback?
    if (node->open != 0)
        return node->open(node);
}

void close_fs(fs_node_t *node){
    // Has the node got a close callback?
    if (node->close != 0)
        return node->close(node);
}

struct dirent *readdir_fs(fs_node_t *node, uint32 index){
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->readdir != 0 )
        return node->readdir(node, index);
    else
        return 0;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name){
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->finddir != 0 )
        return node->finddir(node, name);
    else
        return 0;
}
