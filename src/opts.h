/*
* License: BSD-style license
* Copyright: Radek Podgorny <radek@podgorny.cz>,
*            Bernd Schubert <bernd-schubert@gmx.de>
*/

#ifndef OPTS_H
#define OPTS_H


#include <fuse.h>
#include <stdbool.h>
#include <pthread.h>

#include "unionfs.h"


#define ROOT_SEP ":"

typedef struct {
	bool cow_enabled;
	bool preserve_branch;
	bool statfs_omit_ro;
	int doexit;
	int retval;
	char *chroot; 		// chroot we might go into
	bool debug;		// enable debugging
	char *dbgpath;		// debug file we write debug information into
	pthread_rwlock_t dbgpath_lock; // locks dbgpath
	bool hide_meta_files;
	bool relaxed_permissions;
	bool direct_io;

} uopt_t;

enum {
	KEY_CHROOT,
	KEY_COW,
	KEY_PRESERVE_BRANCH,
	KEY_DEBUG_FILE,
	KEY_DIRS,
	KEY_HELP,
	KEY_HIDE_META_FILES,
	KEY_HIDE_METADIR,
	KEY_MAX_FILES,
	KEY_NOINITGROUPS,
	KEY_RELAXED_PERMISSIONS,
	KEY_STATFS_OMIT_RO,
	KEY_DIRECT_IO,
	KEY_VERSION,
};

typedef struct {
	pthread_rwlock_t lock;
	int nbranches;
	branch_entry_t *branches;
} binf_t;

extern uopt_t uopt;
extern binf_t binf;

#define BINF_RDLOCK() pthread_rwlock_rdlock(&binf.lock)
#define BINF_WRLOCK() pthread_rwlock_wrlock(&binf.lock)
#define BINF_UNLOCK() pthread_rwlock_unlock(&binf.lock)

void set_debug_path(char *new_path, int len);
bool set_debug_onoff(int value);
void uopt_init();
int unionfs_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs);
void unionfs_post_opts();
void add_branch(char *branch);
int parse_branches(const char *arg);


#endif
