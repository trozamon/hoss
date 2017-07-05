#ifndef HOSS_BUILDER_BUILDER_HPP
#define HOSS_BUILDER_BUILDER_HPP

#include <memory>

namespace hoss
{

namespace builder
{

class Builder
{
public:
        Builder();

        ~Builder();

        int run();

private:
        class Impl;

        std::unique_ptr<Impl> impl;
};

} /* namespace builder */

} /* namespace hoss */

#endif /* HOSS_BUILDER_BUILDER_HPP */
