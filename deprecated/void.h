#pragma once

template <class Data> 
struct void_holder {
    private:
        Data _data;

    public:
        void_holder<Data>(Data&& data): _data(std::forward<Data>(data)) {}

        Data get() const { return _data; }

        const bool is_void() const { return false; }

        operator Data() const { return _data; }
};

template <>
struct void_holder<void> {
    public:
        void_holder<void>(...) {}

        const bool is_void() const { return true; }
};

template <class T>
std::ostream& operator<<(std::ostream& ostream, const void_holder<T>& toPrint) {
    if constexpr(std::is_void_v<T>) {
        ostream << "{void_holder<void>}";
    }
    else {
        ostream << toPrint.get();
    }
    return ostream;
}

template <class Fun, class... Args,
          class Result = std::invoke_result_t<Fun, Args...>>
void_holder<Result> void_invoke(Fun&& fun, Args&&... args) {
    // TODO: maybe add macro to avoid repetition of std::invoke
    if constexpr(std::is_void_v<Result>) {
        std::invoke(std::forward<Fun>(fun),
                    std::forward<Args>(args)...);
        return {};
    }
    else {
        return std::invoke(std::forward<Fun>(fun),
                           std::forward<Args>(args)...);
    }
}

