#pragma once    // include guard

#include <string>
#include <iostream>




class GroceryItem
{
  // Insertion and Extraction Operators
  friend std::ostream & operator<<( std::ostream & stream, const GroceryItem & groceryItem );
  friend std::istream & operator>>( std::istream & stream,       GroceryItem & groceryItem );

  // Relational Operators
  friend bool operator==( const GroceryItem & lhs, const GroceryItem & rhs );
  friend bool operator< ( const GroceryItem & lhs, const GroceryItem & rhs );

  public:
    // Constructors
    GroceryItem() = default;
    GroceryItem( const std::string & productName,
                 const std::string & brandName   = {},
                 const std::string & upcCode     = {},
                 double              price       = 0.0 );

    // Queries
    std::string upcCode     () const;
    std::string brandName   () const;
    std::string productName () const;
    double      price       () const;

    // Mutators
    void upcCode      ( const std::string & upcCode     );
    void brandName    ( const std::string & brandName   );
    void productName  ( const std::string & productName );
    void price        ( double              price       );

  private:
    std::string _upcCode;
    std::string _brandName;
    std::string _productName;
    double      _price = 0.0;
};

// Relational Operators
bool operator==( const GroceryItem & lhs, const GroceryItem & rhs );
bool operator!=( const GroceryItem & lhs, const GroceryItem & rhs );

bool operator< ( const GroceryItem & lhs, const GroceryItem & rhs );
bool operator<=( const GroceryItem & lhs, const GroceryItem & rhs );
bool operator> ( const GroceryItem & lhs, const GroceryItem & rhs );
bool operator>=( const GroceryItem & lhs, const GroceryItem & rhs );
