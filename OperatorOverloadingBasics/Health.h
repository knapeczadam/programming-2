// Knapecz, Adam - 1DAE11
#pragma once

class Health final
{
public:
    Health(int value);
    int GetValue() const;

    Health& operator +=(const int rhs);

    Health& operator -=(const int rhs);

private:
    int m_Value;
};

Health operator +(const int lhs, const Health& rhs);

Health operator -(const int lhs, const Health& rhs);

Health operator +(const Health& lhs, const int rhs);

Health operator -(const Health& lhs, const int rhs);
