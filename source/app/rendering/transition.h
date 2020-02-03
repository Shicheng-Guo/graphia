#ifndef TRANSITION_H
#define TRANSITION_H

#include <QObject>

#include <functional>
#include <limits>

class Transition : public QObject
{
    Q_OBJECT
public:
    Transition() : _function([](float) {}) {}

    enum class Type
    {
        None,
        Linear,
        EaseInEaseOut,
        Power,
        InversePower
    };

private:
    Type _type = Type::None;
    float _duration = 0.0f;
    float _elapsed = std::numeric_limits<float>::max();
    std::function<void(float)> _function;
    std::vector<std::function<void()>> _finishedFunctions;
    bool _finishing = false;
    bool _suppressSignals = false;

public:
    template<typename Fn>
    Transition& start(float duration, Type type, Fn&& function)
    {
        Q_ASSERT(!_finishing);

        if(!active() && !_suppressSignals)
            emit started();

        _duration = duration;
        _elapsed = 0.0f;
        _type = type;
        _function = std::move(function);
        _finishedFunctions.clear();
        _suppressSignals = false;

        return *this;
    }

    template<typename FinishedFn>
    Transition& then(FinishedFn&& finishedFn)
    {
        _finishedFunctions.emplace_back(std::move(finishedFn));
        return *this;
    }

    bool update(float dTime);
    bool active() const { return _elapsed == 0.0f || _elapsed < _duration; }

    // The idea behind this is that when you have a chain of transitions, you
    // don't necessarily want to signal when each starts and finishes, so by
    // calling this from a finishedFunction, the finished signal of the current
    // transition is not emitted, nor is the started signal of the subsequent
    // transition, the net result being the entire chain of transitions has a
    // single started and single finished signal emitted
    void willBeImmediatelyReused();

signals:
    void started() const;
    void finished() const;
};

#endif // TRANSITION_H
