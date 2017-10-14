#include "junk.hpp"

static void libgit2_init();
static void libgit2_cleanup();

void hoss::core::do_global_inits()
{
        libgit2_init();
}

void hoss::core::do_global_cleanups()
{
        libgit2_cleanup();
}

#ifdef HOSS_ENABLE_VCS_GIT

#include <git2.h>

static void libgit2_init()
{
        git_libgit2_init();
}

static void libgit2_cleanup()
{
        git_libgit2_shutdown();
}

#else /* ifdef HOSS_ENABLE_VCS_GIT */

static void libgit2_init()
{
}

static void libgit2_cleanup()
{
}

#endif /* ifdef HOSS_ENABLE_VCS_GIT */
