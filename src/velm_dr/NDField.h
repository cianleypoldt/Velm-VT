#include <cstddef>
#include <cstdlib>

namespace vlem_DR {

/*
 * vulnerabilities:
 *  1. Abort is the only error handling in place currently
 *  2. If new[] fails in assignment operators, momory could be leaked
 *
 */

template <typename T, std::size_t N> struct grid {
    T *         data = nullptr;
    std::size_t dims[N];
    std::size_t strides[N];

    template <typename... Idx> grid(Idx... idx);
    ~grid();

    template <typename... Idx> [[nodiscard]] T &       at(Idx... idx);
    template <typename... Idx> [[nodiscard]] const T & at(Idx... idx) const;

    template <typename... Idx> [[nodiscard]] std::size_t offset_of_index(const Idx &... idx) const;
    [[nodiscard]] std::size_t                            total_elements() const;

    void                    fill(T value);
    [[nodiscard]] T *       begin();
    [[nodiscard]] const T * begin() const;
    [[nodiscard]] T *       end();
    [[nodiscard]] const T * end() const;

    template <typename... Idx> [[nodiscard]] T &       operator()(Idx... idx);
    template <typename... Idx> [[nodiscard]] const T & operator()(Idx... idx) const;
    [[nodiscard]] grid &                               operator=(const grid & B);
    [[nodiscard]] grid &                               operator=(grid && B) noexcept;
    grid(const grid & B);
    grid(grid && B) noexcept;
};

template <typename T, std::size_t N> template <typename... Idx> grid<T, N>::grid(Idx... idx) {
    static_assert(sizeof...(Idx) == N, "Number of indices must match grid dimension");
    std::size_t indices[N] = { static_cast<std::size_t>(idx)... };
    for (std::size_t i = 0; i < N; ++i) {
        dims[i] = indices[i];
    }

    strides[N - 1] = 1;
    for (std::size_t i = N - 1; i > 0; --i) {
        strides[i - 1] = strides[i] * dims[i];
    }

    // allocate memory
    data = new T[total_elements()]{};
}

template <typename T, std::size_t N> grid<T, N>::~grid() {
    delete[] data;
}

template <typename T, std::size_t N> template <typename... Idx> [[nodiscard]] T & grid<T, N>::at(Idx... idx) {
    std::size_t indices[N] = { static_cast<std::size_t>(idx)... };
    for (std::size_t i = 0; i < N; ++i) {
        if (indices[i] >= dims[i]) {
            abort();
        }
    }
    return data[offset_of_index(idx...)];
}

template <typename T, std::size_t N> template <typename... Idx> const T & grid<T, N>::at(Idx... idx) const {
    std::size_t indices[N] = { static_cast<std::size_t>(idx)... };
    for (std::size_t i = 0; i < N; ++i) {
        if (indices[i] >= dims[i]) {
            abort();
        }
    }
    return data[offset_of_index(idx...)];
}

template <typename T, std::size_t N> template <typename... Idx>
std::size_t grid<T, N>::offset_of_index(const Idx &... idx) const {
    static_assert(sizeof...(Idx) == N, "Number of indices must match grid dimension");
    std::size_t indices[N] = { static_cast<std::size_t>(idx)... };
    std::size_t offset     = 0;
    for (std::size_t i = 0; i < N; ++i) {
        offset += indices[i] * strides[i];
    }
    return offset;
}

template <typename T, std::size_t N> std::size_t grid<T, N>::total_elements() const {
    std::size_t element_count = 1;
    for (std::size_t i = 0; i < N; ++i) {
        element_count *= dims[i];
    }
    return element_count;
}

template <typename T, std::size_t N> T * grid<T, N>::begin() {
    return data;
}

template <typename T, std::size_t N> const T * grid<T, N>::begin() const {
    return data;
}

template <typename T, std::size_t N> T * grid<T, N>::end() {
    return data + total_elements();
}

template <typename T, std::size_t N> const T * grid<T, N>::end() const {
    return data + total_elements();
}

template <typename T, std::size_t N> void grid<T, N>::fill(T value) {
    for (std::size_t i = 0; i < total_elements(); ++i) {
        data[i] = value;
    }
}

template <typename T, std::size_t N> template <typename... Idx> T & grid<T, N>::operator()(Idx... idx) {
    return data[offset_of_index(idx...)];
}

template <typename T, std::size_t N> template <typename... Idx> const T & grid<T, N>::operator()(Idx... idx) const {
    return data[offset_of_index(idx...)];
}

template <typename T, std::size_t N> grid<T, N> & grid<T, N>::operator=(const grid & B) {
    // self-assignment check
    if (this != &B) {
        bool same_dims = true;
        for (std::size_t i = 0; i < N && same_dims; ++i) {
            if (dims[i] != B.dims[i]) {
                same_dims = false;
            }
        }

        // if dimensions are different, deallocate and reallocate
        if (!same_dims) {
            delete[] data;
            for (std::size_t i = 0; i < N; ++i) {
                dims[i]    = B.dims[i];
                strides[i] = B.strides[i];
            }
            data = new T[total_elements()];
        }

        // copy the data
        for (std::size_t i = 0; i < total_elements(); ++i) {
            data[i] = B.data[i];
        }
    }
    return *this;
}

template <typename T, std::size_t N> grid<T, N> & grid<T, N>::operator=(grid && B) noexcept {
    if (this != &B) {
        delete[] data;

        for (std::size_t i = 0; i < N; ++i) {
            dims[i]    = B.dims[i];
            strides[i] = B.strides[i];
        }

        // transfer ownership of data
        data   = B.data;
        B.data = nullptr;
    }
    return *this;
}

template <typename T, std::size_t N> grid<T, N>::grid(const grid & grid_b) {
    for (std::size_t i = 0; i < N; ++i) {
        dims[i]    = grid_b.dims[i];
        strides[i] = grid_b.strides[i];
    }
    data = new T[total_elements()];
    for (std::size_t i = 0; i < total_elements(); ++i) {
        data[i] = grid_b.data[i];
    }
}

template <typename T, std::size_t N> grid<T, N>::grid(grid && grid_b) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
        dims[i]    = grid_b.dims[i];
        strides[i] = grid_b.strides[i];
    }
    data        = grid_b.data;
    grid_b.data = nullptr;
}

};  // namespace vlem_DR
