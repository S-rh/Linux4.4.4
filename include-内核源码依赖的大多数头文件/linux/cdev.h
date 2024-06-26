#ifndef _LINUX_CDEV_H
#define _LINUX_CDEV_H

#include <linux/kobject.h>
#include <linux/kdev_t.h>
#include <linux/list.h>

struct file_operations;
struct inode;
struct module;

struct cdev {
	struct kobject kobj;					// 嵌入到该结构中的内核对象
	struct module *owner;					// 指向提供驱动程序的模块
	const struct file_operations *ops;		// 一组文件操作，实现了与硬件通信的具体操作
	struct list_head list;					// 包含所有表示该设备的设备特殊文件的inode
	dev_t dev;								// 指定了设备号
	unsigned int count;						// 与改设备关联的从设备号数目
};

// 初始化一个struct cdev实例
void cdev_init(struct cdev *, const struct file_operations *);

struct cdev *cdev_alloc(void);

void cdev_put(struct cdev *p);

int cdev_add(struct cdev *, dev_t, unsigned);

void cdev_del(struct cdev *);

void cd_forget(struct inode *);

#endif
