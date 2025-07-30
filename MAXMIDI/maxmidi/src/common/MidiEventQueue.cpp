

#include "maxmidi/EventTypes.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>

namespace MaxMidi {

class MidiEventQueue {
public:
    void push(const MidiEvent& event) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(event);
        cond_.notify_one();
    }

    bool pop(MidiEvent& event) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) return false;
        event = queue_.front();
        queue_.pop();
        return true;
    }

    void waitAndPop(MidiEvent& event) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { return !queue_.empty(); });
        event = queue_.front();
        queue_.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::queue<MidiEvent> queue_;
    std::condition_variable cond_;
};

} // namespace MaxMidi