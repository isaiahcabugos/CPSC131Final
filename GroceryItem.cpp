// Isaiah Cabugos CPSC131 Final

#include "GroceryItem.hpp"
#include <cstdlib>
#include <iomanip>
#include <sstream>

const double EPSILON = 0.0001;

/* ===== Constructors ===== */
GroceryItem::GroceryItem(const std::string& productName,
                         const std::string& brandName,
                         const std::string& upcCode,
                         double             price)
  : _upcCode(upcCode),
    _brandName(brandName),
    _productName(productName),
    _price(price)
{}

/* ===== Accessors ===== */
std::string GroceryItem::upcCode() const    { return _upcCode; }
std::string GroceryItem::brandName() const  { return _brandName; }
std::string GroceryItem::productName() const{ return _productName; }
double GroceryItem::price() const           { return _price; }

/* ===== Mutators ===== */
void GroceryItem::upcCode(const std::string& upcCode)   { _upcCode = upcCode; }
void GroceryItem::brandName(const std::string& bName)   { _brandName = bName; }
void GroceryItem::productName(const std::string& pName) { _productName = pName; }
void GroceryItem::price(double price)                   { _price = price; }

/* ===== Insertion/Extraction ===== */
std::ostream & operator<<( std::ostream& stream, const GroceryItem& groceryItem ) {
    stream << std::quoted(groceryItem.upcCode())     << ", "
           << std::quoted(groceryItem.brandName())   << ", "
           << std::quoted(groceryItem.productName()) << ", "
           <<             groceryItem.price();

   return stream;
}

std::istream& operator>>( std::istream& stream, GroceryItem& groceryItem ) {
  try { // Attempts to write stream into a GroceryItem, if it fails, an exception is thrown.
       GroceryItem validItem;
       char comma = {};

       stream >> std::quoted(validItem._upcCode)     >> comma
              >> std::quoted(validItem._brandName)   >> comma
              >> std::quoted(validItem._productName) >> comma
              >>             validItem._price;

      if (stream) groceryItem = std::move(validItem);
  }

  catch (const std::ios::failure &) {
    if( !stream.eof() ) throw;
  }

  return stream;
}

/* ===== Logic Operators ===== */
bool operator== (const GroceryItem& lhs, const GroceryItem& rhs) {

       return    lhs.upcCode()     == rhs.upcCode()
              && lhs.brandName()   == rhs.brandName()
              && lhs.productName() == rhs.productName()
              && std::abs(lhs.price() - rhs.price()) < EPSILON;
}

bool operator< (const GroceryItem& lhs, const GroceryItem& rhs) {

  if (auto result = lhs.upcCode()     .compare(rhs.upcCode()     ); result != 0)  return result < 0;
  if (auto result = lhs.brandName()   .compare(rhs.brandName()   ); result != 0)  return result < 0;
  if (auto result = lhs.productName() .compare(rhs.productName() ); result != 0)  return result < 0;
  if (std::abs(lhs.price() - rhs.price()) >= EPSILON)                              return lhs.price() < rhs.price();

  return false;
}

bool operator!=( const GroceryItem & lhs, const GroceryItem & rhs ) { return !(lhs == rhs); }
bool operator<=( const GroceryItem & lhs, const GroceryItem & rhs ) { return !(rhs <  lhs); }
bool operator> ( const GroceryItem & lhs, const GroceryItem & rhs ) { return  (rhs <  lhs); }
bool operator>=( const GroceryItem & lhs, const GroceryItem & rhs ) { return !(lhs <  rhs); }
