#ifndef HOSS_CORE_JUNK_HPP
#define HOSS_CORE_JUNK_HPP

namespace hoss
{

namespace core
{

/**
 * Some libraries need to do global initialization, unfortunately.
 */
void do_global_inits();

/**
 * Some libraries need to do global cleanup, unfortunately.
 */
void do_global_cleanups();

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_JUNK_HPP */
