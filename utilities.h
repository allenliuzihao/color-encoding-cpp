#pragma once

template <typename T, size_t N>
struct vector
{
    T data[N]{}; // Fix C26495: always initialize member variable

    vector() : data{} {}

    // Copy constructor
    vector(const vector<T, N>& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // Move constructor
    vector(vector<T, N>&& other) noexcept
    {
        for (size_t i = 0; i < N; ++i)
        {
            data[i] = std::move(other.data[i]);
        }
    }

    // initialize from initializer list
    vector(std::initializer_list<T> init) 
    {
        size_t i = 0;
        for (auto it = init.begin(); it != init.end() && i < N; ++it, ++i)
        {
            data[i] = *it;
        }
    }

    // Variadic argument constructor
    template<typename... Args, 
        typename = std::enable_if_t<
        sizeof...(Args) == N &&
        std::is_same_v<T, std::decay_t<Args>>...
        >>
    vector(Args&&... args) 
    {
        static_assert(sizeof...(Args) == N, "vector requires N arguments");
        T arr[N] = { args... };
        for (size_t i = 0; i < N; ++i)
        {
            data[i] = arr[i];
        }
    }

    T& operator[](size_t index)
    {
        if (index >= N)
        {
            throw std::out_of_range("vector index out of range");
        }
        return data[index];
    }
    const T& operator[](size_t index) const
    {
        if (index >= N)
        {
            throw std::out_of_range("vector index out of range");
        }
        return data[index];
    }

    T x() const
    {
        if (N < 1)
        {
            throw std::out_of_range("vector has no x component");
        }
        return data[0];
    }

    T y() const
    {
        if (N < 2)
        {
            throw std::out_of_range("vector has no y component");
        }
        return data[1];
    }

    T z() const
    {
        if (N < 3)
        {
            throw std::out_of_range("vector has no z component");
        }
        return data[2];
    }

    T w() const
    {
        if (N < 4)
        {
            throw std::out_of_range("vector has no w component");
        }
        return data[3];
    }

    vector<T, N>& operator=(const vector<T, N>& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    vector<T, N>& operator=(vector<T, N>&& other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = std::move(other.data[i]);
            }
        }
        return *this;
    }
};

template<typename T>
using float3 = vector<T, 3>;

template<typename T>
using float4 = vector<T, 4>;

template<typename T, size_t N>
vector<T, N> saturate(vector<T, N> v)
{
    vector<T, N> result = {};
    for (int i = 0; i < N; ++i)
    {
        result[i] = std::clamp((float) v[i], 0.f, 1.f);
    }
    return result;
}

template<typename T, size_t N>
vector<T, N> min(vector<T, N> v, float minValue)
{
    vector<T, N> result = {};
    for (int i = 0; i < N; ++i)
    {
        result[i] = std::min((float)v[i], minValue);
    }
    return result;
}

template<typename T, size_t N>
vector<T, N> max(vector<T, N> v, float maxValue)
{
    vector<T, N> result = {};
    for (int i = 0; i < N; ++i)
    {
        result[i] = std::max((float)v[i], maxValue);
    }
    return result;
}

template<typename T, size_t N>
vector<T, N> ldexp(vector<T, N> v, int exp)
{
    vector<T, N> result = {};
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = std::ldexpf((float)v[i], exp);
    }
    return result;
}

uint32_t asuint(float x);
float asfloat(uint32_t x);

std::string binary_string(uint16_t input, uint16_t num_bits = 16);
std::string binary_string(uint32_t input, uint32_t num_bits = 32);

