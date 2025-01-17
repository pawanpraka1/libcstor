/*
 * Copyright © 2017-2019 The OpenEBS Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef	_UZFS_REBUILDING_H
#define	_UZFS_REBUILDING_H

#ifdef __cplusplus
extern "C" {
#endif
#define	IO_DIFF_SNAPNAME		".io_snap"
#define	REBUILD_SNAPSHOT_SNAPNAME	"rebuild_snap"
#define	REBUILD_SNAPSHOT_CLONENAME	"rebuild_clone"
#define	STALE				"stale"

/*
 * API to compare metadata
 * return :
 * 	-1 : if first < second
 *	 0 : if first == second
 *	 1 : if first > second
 */
int compare_blk_metadata(blk_metadata_t *first_md, blk_metadata_t *second_md);

/*
 * API to access data whose metadata is higer than base_metadata
 */
int uzfs_get_io_diff(zvol_state_t *zv, blk_metadata_t *base_metadata,
    zvol_state_t *snap_zv, uzfs_get_io_diff_cb_t *cb_func,
    off_t offset, size_t len, void *arg);

/*
 * uzfs_get_nonoverlapping_ondisk_blks will check on_disk metadata with
 * incoming metadata and will populate list with non-overlapping
 * segment(offset,len).
 * Segment will be compared by meta_vol_block_size. If on_disk metadata
 * is greater than incoming metadata then that segment will be discarded
 * else it will be added to list.
 */
int uzfs_get_nonoverlapping_ondisk_blks(zvol_state_t *zv, uint64_t offset,
    uint64_t len, blk_metadata_t *incoming_md, void **list);
int uzfs_zvol_get_or_create_internal_clone(zvol_state_t *zv,
    zvol_state_t **snap_zv, zvol_state_t **clone_zv, int *ret_val);
int uzfs_zvol_release_internal_clone(zvol_state_t *zv,
    zvol_state_t *snap_zv, zvol_state_t *clone_zv);

/*
 * To remove all internal snapshots of a dataset
 */
int uzfs_destroy_all_internal_snapshots(zvol_state_t *zv);
boolean_t is_stale_clone(zvol_state_t *);
int uzfs_destroy_all_iosnap_snapshots(zvol_state_t *zv);
boolean_t is_stale_clone(zvol_state_t *);

#ifdef __cplusplus
}
#endif
#endif
