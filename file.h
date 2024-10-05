struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE } type;
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe;
  struct inode *ip;
  uint off;

  void * dev_payload;
  //Modify to hold color value
  int color;
};


// in-memory copy of an inode
struct inode {
  uint dev;           // Device number
  uint inum;          // Inode number
  int ref;            // Reference count
  struct sleeplock lock;
  int flags;          // I_VALID

  short type;         // copy of disk inode
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
};
#define I_VALID 0x2

// table mapping major device number to
// device functions
struct devsw {
  int (*read)(struct file*, char*, int);
  int (*write)(struct file*, char*, int);
  int (*ioctl)(struct file*, int, int);
};

extern struct devsw devsw[];

#define CONSOLE 1

