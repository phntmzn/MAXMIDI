


#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

namespace MaxMidi {

class MidiClock {
public:
    using Callback = std::function<void(uint64_t)>;

    MidiClock(int bpm = 120)
        : bpm_(bpm), running_(false) {}

    void start(Callback callback) {
        running_ = true;
        thread_ = std::thread([=]() {
            auto interval = std::chrono::milliseconds(60000 / bpm_ / 24); // 24 PPQN MIDI clock
            uint64_t tick = 0;
            while (running_) {
                auto start = std::chrono::steady_clock::now();
                callback(tick++);
                std::this_thread::sleep_until(start + interval);
            }
        });
    }

    void stop() {
        running_ = false;
        if (thread_.joinable()) thread_.join();
    }

    void setBPM(int bpm) {
        bpm_ = bpm;
    }

private:
    int bpm_;
    std::atomic<bool> running_;
    std::thread thread_;
};

} // namespace MaxMidi