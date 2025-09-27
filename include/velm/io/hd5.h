#include "velm/core/ndarray.h"

#include <cstddef>

namespace vlem {

class hdf5_file {
    hdf5_file();
    ~hdf5_file();

    template <typename T, std::size_t N, typename... Idx> velm_DR::ndarray<T, N> extract_field(const char *... fields);
    template <typename T, std::size_t N, typename... Idx> velm_DR::ndarray<T, N> extract_field(const char *);
};

};  // namespace vlem
