/*
* License: BSD-style license
* Copyright: Radek Podgorny <radek@podgorny.cz>,
*            Bernd Schubert <bernd-schubert@gmx.de>
*/

#ifndef FINDBRANCH_H
#define FINDBRANCH_H

typedef enum searchflag {
	RWRO,
	RWONLY
} searchflag_t;

bool branch_contains_file_or_parent_dir(branch_entry_t *branch, const char *path);
int find_rorw_branch(const char *path, branch_entry_t *be);
int find_lowest_rw_branch(int branch_ro, branch_entry_t *be);
int find_rw_branch_cutlast(const char *path, branch_entry_t *be);
int __find_rw_branch_cutlast(const char *path, int rw_hint, branch_entry_t *be);
int find_rw_branch_cow(const char *path, branch_entry_t *be);
int find_rw_branch_cow_common(const char *path, bool copy_dir, branch_entry_t *be);

#endif
