#include <iostream>
#define LINEINFO             std::cout << __PRETTY_FUNCTION__ << std::endl
#define LINEINFO_P( x )      std::cout << __PRETTY_FUNCTION__ << x << std::endl
#define LINEINFO_COPY        LINEINFO_P( " copy" )
#define LINEINFO_ASSIGN      LINEINFO_P( " assign" )
#define LINEINFO_MOVE_COPY   LINEINFO_P( " move copy" )
#define LINEINFO_MOVE_ASSIGN LINEINFO_P( " move assign" )
#define LINEINFO_SWAP        LINEINFO_P( " swap" )

struct DataLog
{
    void swap( DataLog& dataLog ) noexcept
    {
        LINEINFO_SWAP;
        std::swap( m_some_data, dataLog.m_some_data );
    }

    DataLog() noexcept { LINEINFO; }
    explicit DataLog( size_t count )
        : m_some_data( count )
    {
        LINEINFO_P( ':' << count );
    }
    ~DataLog() { LINEINFO; }
    DataLog( const DataLog& dataLog ) noexcept
        : m_some_data( dataLog.m_some_data )
    {
        LINEINFO_COPY;
    }
    DataLog( DataLog&& dataLog ) noexcept
        : m_some_data( dataLog.m_some_data )
    {
        LINEINFO_MOVE_COPY;
    }
    DataLog& operator=( const DataLog& dataLog ) noexcept;
    DataLog& operator=( DataLog&& dataLog ) noexcept;

    [[maybe_unused]] [[nodiscard]] size_t getSomeData() const { return m_some_data; }
    [[maybe_unused]] void setSomeData( size_t mSomeData ) { m_some_data = mSomeData; }

private:
    size_t m_some_data = 0;
};

DataLog& DataLog::operator=( const DataLog& dataLog ) noexcept
{
    LINEINFO_ASSIGN;
    if ( this == &dataLog )
        return *this;
    DataLog tmp( dataLog );
    this->swap( tmp );
    --m_some_data;
    return *this;
}
DataLog& DataLog::operator=( DataLog&& dataLog ) noexcept
{
    LINEINFO_MOVE_ASSIGN;
    swap( dataLog );
    return *this;
}

class Base
{
public:
    Base() { LINEINFO; };
    explicit Base( size_t data )
        : m_PrivateData( data )
    {
        LINEINFO_P( ':' << m_PrivateData.getSomeData() );
    }
    virtual ~Base() { LINEINFO; }
    Base( const Base& base ) noexcept
        : m_PrivateData( base.m_PrivateData )
    {
        LINEINFO_COPY;
    }
    Base( Base&& base ) noexcept
        : m_PrivateData( std::move(base.m_PrivateData) )
    {
        LINEINFO_MOVE_COPY;
    }
    Base& operator=( Base base ) noexcept
    {
        LINEINFO_ASSIGN;;
        this->swap( base );
        return *this;
    }
    Base& operator=( Base&& base ) noexcept
    {
        LINEINFO_ASSIGN;;
        this->swap( base );
        return *this;
    }
    void swap( Base& base ) { std::swap( m_PrivateData, base.m_PrivateData ); }

protected:
    DataLog m_PrivateData;
};

class Derived : public Base
{
public:
    void swap( Derived& l ) noexcept
    {
        LINEINFO_SWAP;
        Base::swap( l );
    }
    Derived() noexcept { LINEINFO; };
    ~Derived() override { LINEINFO; }
    explicit Derived( size_t d )
        : Base( d )
    {
        LINEINFO_P( ' ' << d );
    }
    Derived( const Derived& derived ) noexcept
        : Base( derived )
    {
        LINEINFO_COPY;
    }
    Derived( Derived&& derived ) noexcept
        : Base( derived )
    {
        LINEINFO_MOVE_COPY;
    }
    Derived& operator=( Derived derived ) noexcept
    {
        LINEINFO_ASSIGN;
        this->swap( derived );
        return *this;
    }
    Derived& operator=( Derived&& derived ) noexcept
    {
        LINEINFO_MOVE_ASSIGN;
        this->swap( derived );
        return *this;
    }
};

Derived getRVODerived() { return {}; }
int main()
{
    Derived coolObject( 5 );
    std::cout << "\n\n\nFrom function copy\n";
    Derived coolDerivedObject = getRVODerived();
    std::cout << "\n\n\nFrom function copy\n";
    Derived second = getRVODerived();
    std::cout << "\n\n\nStart copy\n";
    coolDerivedObject = second;
    std::cout << "\n\nFinis copy\n";
    return 0;
}