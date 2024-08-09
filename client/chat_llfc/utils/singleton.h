#ifndef SINGLETON_H
#define SINGLETON_H

/******************************************************************************
 *
 * @file       singleton.h
 * @brief      单例模式模版类
 *
 * @author     Jiguang Zearo
 * @date       2024/08/08
 * @history
 *****************************************************************************/

#include <memory>
#include <iostream>
#include <mutex>

template <typename T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton<T>& _) = delete;
    Singleton& operator = (const Singleton<T>& _) = delete;

    static std::shared_ptr<T> _instance;

public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            // 使用 std::make_shared 的缺点是它在一个内存块中同时分配对象和控制块
            // 导致即使所有 shared_ptr 实例都已销毁，由于如 std::weak_ptr 的其他引用，内存可能仍未释放
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "Singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
