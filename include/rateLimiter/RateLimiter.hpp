
#include <atomic>
#include <chrono>
#include <thread>
#include <mutex>

namespace rateLimiter {

    using Clock = std::chrono::steady_clock;
    using TimeInterval = Clock::duration;
    using TimePoint = Clock::time_point;

class rate_limiter {

    public:
        /**
         * Constructor RateLimiter.
         * @param Describe the number of allowed calls in interval.
         * @param Describe time duration for allowed calls
         */
        rate_limiter(unsigned limit, TimeInterval interval):_myFirstRequest{std::chrono::time_point<Clock>(TimeInterval::zero())},
                                                                 _myLastRequest{std::chrono::time_point<Clock>(TimeInterval::zero())},
                                                                 _maxRequests{limit},
                                                                 _duration{interval},
                                                                 _currRequests{limit} {}


        /**
         * Update Current Interval and Number of Calls.
         * @param Number of calls for the interval.
         * @param Interval Duration.
         * @param Boolean to reset current limit.
         */
        void setRate(unsigned limit, TimeInterval interval, bool reset = false) {
            std::lock_guard<std::mutex> lock(_myMutex);
            _maxRequests = limit;
            _duration = interval;
            if (reset) {
                _myFirstRequest = std::chrono::time_point<Clock>(TimeInterval::zero());
                _myLastRequest = std::chrono::time_point<Clock>(TimeInterval::zero());
                _currRequests = _maxRequests;
            }
        }


        /**
         * Number of calls .
         * @return Return Number of calls allowed.
         */
        unsigned long getLimit(){
                std::lock_guard<std::mutex> lock(_myMutex);
                return _maxRequests;
            }

         /**
         * Allowed Time interval.
         * @return Return TIME INTERVAL allowed.
         */

         TimeInterval getInterval(){
                std::lock_guard<std::mutex> lock(_myMutex);
                return _duration;
            }
            /**
            * Allow permission for the task. Blocks the call for if limit is reached.
       0    * for current interval.
            */
            void acquire(){
                std::lock_guard<std::mutex> lock(_myMutex);
                while (_currRequests == 0) {
                    if (isExpired(_duration)) {
                        _currRequests = _maxRequests;
                    }
                    std::this_thread::yield();
                }
                if (_currRequests == _maxRequests) {
                    _myFirstRequest = Clock::now();
                }
                _currRequests--;
                _myLastRequest = Clock::now();
            }
    private:
        TimePoint _myFirstRequest;
        TimePoint _myLastRequest;
        unsigned long _maxRequests;
        unsigned long _currRequests;
            TimeInterval _duration;
        std::mutex _myMutex;
    private:
        /**
         * Ensure if current window is expired
         * @param Time-stamp
         * @return Return true if current window is valid.
         * This checks if current limit and current time stamp is valid for
         * current window.
         */
        const bool isExpired(const TimeInterval &timeWindow) const {
                if (timeWindow == TimeInterval::zero()) { return true; }
                auto now = Clock::now();
                auto offset = _myFirstRequest.time_since_epoch() % _duration;
                auto epoch = _myLastRequest.time_since_epoch();
                auto duration = std::chrono::duration_cast<Clock::duration>(epoch);
                duration = duration - (duration % timeWindow) + timeWindow + offset;
                auto expirationDate = std::chrono::time_point<Clock>(duration);
                return now >= expirationDate;
            }

};

}
