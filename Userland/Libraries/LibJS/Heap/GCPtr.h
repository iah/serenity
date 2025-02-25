/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h>

namespace JS {

template<typename T>
class GCPtr;

template<typename T>
class NonnullGCPtr {
public:
    NonnullGCPtr() = delete;

    NonnullGCPtr(T& ptr)
        : m_ptr(&ptr)
    {
    }

    template<typename U>
    NonnullGCPtr(U& ptr)
    requires(IsConvertible<U*, T*>)
        : m_ptr(&static_cast<T&>(ptr))
    {
    }

    NonnullGCPtr(NonnullGCPtr const& other)
        : m_ptr(other.ptr())
    {
    }

    template<typename U>
    NonnullGCPtr(NonnullGCPtr<U> const& other)
    requires(IsConvertible<U*, T*>)
        : m_ptr(other.ptr())
    {
    }

    NonnullGCPtr& operator=(NonnullGCPtr const& other)
    {
        m_ptr = other.ptr();
        return *this;
    }

    template<typename U>
    NonnullGCPtr& operator=(NonnullGCPtr<U> const& other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = static_cast<T*>(other.ptr());
        return *this;
    }

    NonnullGCPtr& operator=(T& other)
    {
        m_ptr = &other;
        return *this;
    }

    template<typename U>
    NonnullGCPtr& operator=(U& other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = &static_cast<T&>(other);
        return *this;
    }

    T* operator->() const { return m_ptr; }

    T& operator*() const { return *m_ptr; }

    T* ptr() const { return m_ptr; }

    operator T*() const { return m_ptr; }

    operator T&() const { return *m_ptr; }

private:
    T* m_ptr { nullptr };
};

template<typename T>
class GCPtr {
public:
    GCPtr() = default;

    GCPtr(T& ptr)
        : m_ptr(&ptr)
    {
    }

    GCPtr(T* ptr)
        : m_ptr(ptr)
    {
    }

    GCPtr(NonnullGCPtr<T> const& other)
        : m_ptr(other.ptr())
    {
    }

    template<typename U>
    GCPtr(NonnullGCPtr<U> const& other)
    requires(IsConvertible<U*, T*>)
        : m_ptr(other.ptr())
    {
    }

    GCPtr(nullptr_t)
        : m_ptr(nullptr)
    {
    }

    GCPtr(GCPtr const&) = default;
    GCPtr& operator=(GCPtr const&) = default;

    template<typename U>
    GCPtr& operator=(GCPtr<U> const& other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = static_cast<T*>(other.ptr());
        return *this;
    }

    GCPtr& operator=(NonnullGCPtr<T> const& other)
    {
        m_ptr = other.ptr();
        return *this;
    }

    template<typename U>
    GCPtr& operator=(NonnullGCPtr<U> const& other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = static_cast<T*>(other.ptr());
        return *this;
    }

    GCPtr& operator=(T& other)
    {
        m_ptr = &other;
        return *this;
    }

    template<typename U>
    GCPtr& operator=(U& other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = &static_cast<T&>(other);
        return *this;
    }

    GCPtr& operator=(T* other)
    {
        m_ptr = other;
        return *this;
    }

    template<typename U>
    GCPtr& operator=(U* other)
    requires(IsConvertible<U*, T*>)
    {
        m_ptr = static_cast<T*>(other);
        return *this;
    }

    T* operator->() const
    {
        VERIFY(m_ptr);
        return m_ptr;
    }

    T& operator*() const
    {
        VERIFY(m_ptr);
        return *m_ptr;
    }

    T* ptr() const { return m_ptr; }

    operator bool() const { return !!m_ptr; }
    bool operator!() const { return !m_ptr; }

    operator T*() const { return m_ptr; }

private:
    T* m_ptr { nullptr };
};

template<typename T, typename U>
inline bool operator==(GCPtr<T> const& a, GCPtr<U> const& b)
{
    return a.ptr() == b.ptr();
}

template<typename T, typename U>
inline bool operator==(GCPtr<T> const& a, NonnullGCPtr<U> const& b)
{
    return a.ptr() == b.ptr();
}

template<typename T, typename U>
inline bool operator==(NonnullGCPtr<T> const& a, NonnullGCPtr<U> const& b)
{
    return a.ptr() == b.ptr();
}

template<typename T, typename U>
inline bool operator==(NonnullGCPtr<T> const& a, GCPtr<U> const& b)
{
    return a.ptr() == b.ptr();
}

}
