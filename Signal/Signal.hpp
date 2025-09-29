#pragma once

#include <map>
#include <functional>
#include <iostream>
#include <cstdint>

namespace cpputils {

    template <typename... Args>
    struct Connection {
    public:
        using Callback = std::function<void(Args...)>;
        using KeyType = u_int64_t;

        Connection(KeyType id, std::map<KeyType, const Callback> &callbacks)
            : _id(id), _callbacks(callbacks), _isConnected(true)
        {
        }
        ~Connection() = default;

        Connection &operator=(const Connection &other)
        {
            if (this != &other) {
                _id = other._id;
                _callbacks = other._callbacks;
                _isConnected = other._isConnected;
                _callback = other._callback;
            }
            return *this;
        }

        void disconnect()
        {
            if (_isConnected) {
                _callback = _callbacks.at(_id);
                _callbacks.erase(_id);
                _isConnected = false;
            }
        }

        void reconnect()
        {
            if (!_isConnected) {
                _callbacks.emplace(_id, _callback);
                _isConnected = true;
            }
        }

    private:
        std::map<KeyType, const Callback> &_callbacks;
        KeyType _id = 0;
        bool _isConnected = false;
        Callback _callback;
    };

    template <>
    struct Connection<void> {
    public:
        using Callback = std::function<void()>;
        using KeyType = u_int64_t;

        Connection(KeyType id, std::map<KeyType, const Callback> &callbacks)
            : _id(id), _callbacks(callbacks), _isConnected(true) {}
        ~Connection() = default;

        Connection &operator=(const Connection &other)
        {
            if (this != &other) {
                _id = other._id;
                _callbacks = other._callbacks;
                _isConnected = other._isConnected;
                _callback = other._callback;
            }
            return *this;
        }

        void disconnect()
        {
            if (_isConnected) {
                _callback = _callbacks.at(_id);
                _callbacks.erase(_id);
                _isConnected = false;
            }
        }

        void reconnect()
        {
            if (!_isConnected) {
                _callbacks.emplace(_id, _callback);
                _isConnected = true;
            }
        }

    private:
        std::map<KeyType, const Callback> &_callbacks;
        KeyType _id = 0;
        bool _isConnected = false;
        Callback _callback;
    };

    template <typename... Args>
    struct Signal {
    public:
        using Callback = const std::function<void(Args...)>;
        using KeyType = u_int64_t;

        Signal() = default;
        ~Signal() = default;

        Connection<Args...> connect(Callback &callback)
        {
            _callbacks.emplace(_id, callback);
            return Connection<Args...>(_id++, _callbacks);
        }

        void emit(Args... args)
        {
            for (auto &[_, callback] : _callbacks) {
                callback(args...);
            }
        }

    private:
        std::map<KeyType, Callback> _callbacks;
        KeyType _id = 0;
    };

    template <>
    struct Signal<void> {
    public:
        using Callback = const std::function<void()>;
        using KeyType = u_int64_t;

        Signal() = default;
        ~Signal() = default;

        Connection<void> connect(Callback &callback)
        {
            _callbacks.emplace(_id, callback);
            return Connection<void>(_id++, _callbacks);
        }

        void emit()
        {
            for (auto &[_, callback] : _callbacks) {
                callback();
            }
        }

    private:
        std::map<KeyType, Callback> _callbacks;
        KeyType _id = 0;
    };

} // namespace cpputils
