#include <mutex> // std::mutex(), std::unique_lock, mutable

class TestMutex {
    public:
        TestMutex() : m_loglevel_val(0) {}

        void add_test() {
            auto lock = unique_lock();
            ++m_loglevel_val;
            unlock(lock);
        }

    private:
        using UniqueLock = std::unique_lock<std::mutex>;
        UniqueLock unique_lock() const { return UniqueLock(m_mutex); }
        // NOLINTNEXTLINE (runtime/references)
        void unlock(UniqueLock &lock) const { lock.unlock(); }

    private:
        int m_loglevel_val;
        mutable std::mutex m_mutex{};
};