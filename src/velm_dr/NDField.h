#include <array>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace vlem_DR {

template <typename T, std::size_t N> class NDField {
    std::vector<T>             data_;
    std::array<std::size_t, N> dims_;
    std::array<std::size_t, N> strides_;

  public:
    explicit NDField(const std::array<std::size_t, N> & dims) : dims_(dims) {
        std::size_t total = 1;
        for (std::size_t i = N; i-- > 0;) {  // compute strides from last to first
            strides_[i] = total;
            total *= dims_[i];
        }
        data_.resize(total);
    }

    // Bounds-checked access
    template <typename... Idx> T & at(Idx... idx) {
        static_assert(sizeof...(idx) == N, "Wrong number of indices");
        std::size_t offset = compute_offset(idx...);
        return data_.at(offset);
    }

    template <typename... Idx> const T & at(Idx... idx) const {
        static_assert(sizeof...(idx) == N, "Wrong number of indices");
        std::size_t offset = compute_offset(idx...);
        return data_.at(offset);
    }

    // Fast access without bounds checking
    template <typename... Idx> T & operator()(Idx... idx) {
        static_assert(sizeof...(idx) == N, "Wrong number of indices");
        return data_[compute_offset(idx...)];
    }

    template <typename... Idx> const T & operator()(Idx... idx) const {
        static_assert(sizeof...(idx) == N, "Wrong number of indices");
        return data_[compute_offset(idx...)];
    }

    // Linear access operator
    T & operator[](std::size_t index) { return data_[index]; }

    const T & operator[](std::size_t index) const { return data_[index]; }

    // Get dimension sizes
    std::size_t size(std::size_t dim) const {
        if (dim >= N) {
            throw std::out_of_range("Dimension out of range");
        }
        return dims_[dim];
    }

    std::array<std::size_t, N> dimensions() const { return dims_; }

  private:
    template <typename... Idx> std::size_t compute_offset(Idx... idx) const {
        std::size_t indices[N] = { static_cast<std::size_t>(idx)... };
        std::size_t offset     = 0;
        for (std::size_t i = 0; i < N; ++i) {
            if (indices[i] >= dims_[i]) {
                throw std::out_of_range("Index out of bounds");
            }
            offset += indices[i] * strides_[i];
        }
        return offset;
    }
};

};  // namespace vlem_DR
