#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <type_traits>
#include <array>

template <typename T, int m, int n>
class Matrix
{
public:
    static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type");
    static_assert(m > 0 && n > 0, "m and n must be greater than 0");
    using size_type = typename std::vector<T>::size_type;

public:
    Matrix(const T initial={})
    {
        m_matrix.resize(rows());
        for (auto& v: m_matrix)
        {
            v.resize(columns(), T{initial});
        }
    }
    ~Matrix() = default;

    Matrix(const Matrix& other)
        : m_matrix{other.m_matrix}
    {
        std::cout << "Copy constructor\n";
    }
    Matrix& operator=(const Matrix& other)
    {
        std::cout << "Copy assignment\n";
        if (this != &other)
            m_matrix = other.m_matrix;
        return *this;
    }

    Matrix(Matrix&& other)
        : m_matrix{}
    {
        std::cout << "Move constructor\n";
        *this = std::move(other);
    }
    Matrix& operator=(Matrix&& other)
    {
        std::cout << "Move assignment\n";
        if (this != &other)
        {
            m_matrix = std::move(other.m_matrix);
        }
        return *this;
    }

    constexpr size_type rows() const
    {
        return m;
    }
    constexpr size_type columns() const
    {
        return n;
    }
    T& at(const size_type i, const size_type j)
    {
        return m_matrix.at(i).at(j);
    }
    const T& at(const size_type i, const size_type j) const
    {
        return m_matrix.at(i).at(j);
    }

    //Scalar operations
    Matrix operator+(const T rhs)
    {
        auto tmp{*this};
        for (size_type i=0; i<tmp.rows(); ++i)
            for (size_type j=0; j<tmp.columns(); ++j)
                tmp.at(i, j) += rhs;
        return tmp;
    }
    Matrix operator-(const T rhs)
    {
        return this->operator+(-rhs);
    }
    Matrix operator*(const T rhs)
    {
        auto tmp{*this};
        for (size_type i=0; i<tmp.rows(); ++i)
            for (size_type j=0; j<tmp.columns(); ++j)
                tmp.at(i, j) *= rhs;
        return tmp;
    }
    Matrix operator/(const T rhs)
    {
        return this->operator*(1/rhs);
    }

    template <int x, int y, typename Result = Matrix<T, m, y>>
    Result operator*(const Matrix<T, x, y>& other) const
    {
        static_assert(n == x, "columns of first should match rows of second");
        Result tmp{0};
        for (size_type i=0; i<tmp.rows(); ++i)
        {
            for (size_type j=0; j<tmp.columns(); ++j)
            {
                for (size_type k=0; k<m; ++k)
                {
                    tmp.at(i, j) = at(i, k) * other.at(k, j);
                }
            }
        }
        return tmp;
    }

    Matrix operator+(const Matrix& other) const
    {
        Matrix tmp{};
        for (size_type i=0; i<rows(); ++i)
        {
            for (size_type j=0; j<columns(); ++j)
            {
                tmp.at(i, j) = at(i, j) + other.at(i, j);
            }
        }
        return tmp;
    }

    template <typename Result = Matrix<T, n, m>>
    Result transpose() const
    {
        Result tmp{0};
        for (size_type i=0; i<m; ++i)
        {
            for (size_type j=0; j<n; ++j)
            {
                tmp.at(j, i) = at(i, j);
            }
        }
        return tmp;
    }

private:
    std::vector<std::vector<T>> m_matrix;
};

template <typename T, int m, int n>
std::ostream& operator<<(std::ostream& os, const Matrix<T, m, n>& matrix)
{
    using size_type = typename Matrix<T, m, n>::size_type;
    for (size_type i=0; i<matrix.rows(); ++i)
    {
        for (size_type j=0; j<matrix.columns(); ++j)
        {
            os << matrix.at(i, j) << " ";
            if (j == (matrix.columns() - 1))
                os << "\n";
        }
    }
    return os;
}

#endif // __MATRIX_HPP__
