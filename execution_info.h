#pragma once

template <class Result, class TimeRep = double>
struct execution_info {
    private:
        using Duration = std::chrono::duration<TimeRep>;

        Result _result;
        Duration _execution_time;

    public:
        // TODO: find a way to remove this
        // TODO: optmize for move semantics
        execution_info(const Result& result,
                       const Duration& execution_time):
            _result(result), _execution_time(execution_time) {}

        // getters
        Result get_result() const { return _result; }
        auto get_execution_time() const { return _execution_time; }
};

template <class Fun, class... Args,
          class Result = utl::void_invoke_result_t<Fun, Args...>>
execution_info<Result>
record_execution(Fun&& fun, Args&&... args) {
    namespace chrono = std::chrono;

    // start recording time
    auto startTime = chrono::system_clock::now();

    // execute function
    //     TODO: write template deduction guide for void 
    Result result = utl::void_invoke(std::forward<Fun>(fun),
                                std::forward<Args>(args)...);

    auto endTime = chrono::system_clock::now();
    auto executionTime = endTime - startTime;

    // return function execution info
    return {result, executionTime};
}
