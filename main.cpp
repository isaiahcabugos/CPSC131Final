#if defined( __clang__ )
#  pragma clang diagnostic ignored "-Wcomma"               // Statement scoped timer operations use the coma operator
#  pragma clang diagnostic ignored "-Wunused-parameter"    // Several functions won't use their parameters until implemented
#  pragma clang diagnostic ignored "-Wunused-variable"     // Several functions won't use their variables until implemented
// no option to set optimization level akin to GCC optimize

#elif defined( __GNUC__ )
#  pragma GCC diagnostic ignored "-Wunused-parameter"    // Several functions won't use their parameters until implemented
#  pragma GCC diagnostic ignored "-Wunused-variable"     // Several functions won't use their variables until implemented
#  pragma GCC            optimize 3

#elif defined( _MSC_VER )
#  pragma warning( disable : 4834 )                        // discarding function return value for functions marked with [[nodiscard]] attribute (since C++17)

#endif


#include <algorithm>        // shuffle(), find_if()
#include <cstddef>          // size_t
#include <forward_list>     // Singly linked list
#include <iostream>         // standard i/o streams cout, clog, cin
#include <iterator>         // next()
#include <list>             // doubly linked list
#include <map>              // Binary search tree associative container with no duplicates
#include <random>           // random_device, default_random_engine
#include <string>           // Unbounded strings
#include <unordered_map>    // Hash Table associative container with no duplicates
#include <vector>           // Unbounded vector

#include "GroceryItem.hpp"
#include "Timer.hpp"







namespace  // unnamed, anonymous namespace
{
  /*********************************************************************************************************************************
  **  Type Definitions
  *********************************************************************************************************************************/
  // Create a matrix indexed by Data Structure and Operation that holds a collection of time samples collected to perform the operation.
  using OperationName     = std::string;
  using DataStructureName = std::string;
  using SnapshotInterval  = std::size_t;
  using ElapsedTime       = std::size_t;

  using TimeMatrix        = std::map<SnapshotInterval, std::map<DataStructureName, std::map<OperationName, ElapsedTime>>>;

  struct Direction
  { enum value {Grow=1, Shrink=-Grow}; };

  using Utilities::Timer;



  /*********************************************************************************************************************************
  **  Function Declarations
  *********************************************************************************************************************************/
  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix );

  template<class Operation, class Preamble>
  void measure( const std::string & structureName,                            // free text name of data structure being measured
                const std::string & operationDescription,                     // free text name of the operation of the data structure being measured
                Preamble            preamble,                                 // set up work to occur before operation, expressed as a Functiod defaulted to "do nothing"
                Operation           operation,                                // operation to be measured, expressed as a Functiod
                Direction::value    direction = Direction::Grow );            // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)


  void collect_Vector_measurements();
  void collect_DoublyLinkedList_measurements();
  void collect_SinglyLinkedList_measurements();
  void collect_BinarySearchTree_measurements();
  void collect_HashTable_measurements();

  /*********************************************************************************************************************************
  **  Object Definitions
  *********************************************************************************************************************************/
  std::vector<GroceryItem> sampleData;                                         // collection of data samples
  TimeMatrix               runTimes;                                           // collection of operation time measurements
  auto                     noop = []( auto & ) {};                             // A no-operation (do nothing) Functiod. Useful when
                                                                               // requesting no set up be done prior to measuring an
                                                                               // operation.
}    // unnamed, anonymous namespace











int main()
{
  // Load a set of data samples and  guarantee they are not in any particular order
  for( GroceryItem item; std::cin >> item; ) sampleData.emplace_back( item );
  std::shuffle( sampleData.begin(), sampleData.end(), std::default_random_engine( std::random_device {}() ) );


  // Define the things to be measured.  Specifically, measure the three primary operations
  //    1) insert,
  //    2) remove, and
  //    3) search
  // on the
  //    a) Vector,
  //    b) Singly Linked List,
  //    c) Doubly Linked List,
  //    d) Binary Search Tree, and
  //    e) Hash Table.
  // When modifying a structure, do so at the front and the back.  When searching, assume worst case and look for an element that is
  // not in the container

  Timer totalElapsedTime( "total elapsed time is ", std::clog );

  std::clog << "Starting to collect Vector measurements\n";
  Timer("Vector measurements completed in ", std::clog), collect_Vector_measurements();

  std::clog << "\nStarting to collect Doubly Linked List measurements\n";
  Timer( "Doubly Linked List measurements completed in ", std::clog ), collect_DoublyLinkedList_measurements();

  std::clog << "\nStarting to collect Singly Linked List measurements\n";
  Timer( "Singly Linked List measurements completed in ", std::clog ), collect_SinglyLinkedList_measurements();

  std::clog << "\nStarting to collect Binary Search Tree measurements\n";
  Timer( "Binary Search Tree measurements completed in ", std::clog ), collect_BinarySearchTree_measurements();

  std::clog << "\nStarting to collect Hash Table measurements\n";
  Timer( "Hash Table measurements completed in ", std::clog ), collect_HashTable_measurements();

  //  Report measurements
  std::cout << runTimes << '\n';

  std::clog << '\n' << std::string( 80, '-' ) << '\n';
}













/*********************************************************************************************************************************
**  Private definitions
*********************************************************************************************************************************/
namespace    // unnamed, anonymous namespace
{
  /*********************************************************************************************************************************
  **  Collect Vector Measurements
  *********************************************************************************************************************************/
  void collect_Vector_measurements()
  {
    {  // 1a:  Insert at the back of a vector
      std::vector<GroceryItem> dataStructureUnderTest;
      measure( "Vector", "Insert at the back", noop, [&]( const GroceryItem & item ) {

        ///////////////////////// TO-DO (1) //////////////////////////////
          /// Write the line of code to push "item" at the back of the data structure under test
          dataStructureUnderTest.push_back(item);

        /////////////////////// END-TO-DO (1) ////////////////////////////

      } );
    }


    {  // 1a:  Insert at the front of a vector
      std::vector<GroceryItem> dataStructureUnderTest;
      measure( "Vector", "Insert at the front", noop, [&]( const GroceryItem & item ) {

        ///////////////////////// TO-DO (2) //////////////////////////////
          /// Write the line of code to insert "item" at the beginning of the data structure under test
          dataStructureUnderTest.insert( dataStructureUnderTest.begin(), item );

        /////////////////////// END-TO-DO (2) ////////////////////////////

      } );
    }


    {  // 2a:  Remove from the back of a vector
      std::vector<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "Vector", "Remove from the back", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (3) //////////////////////////////
          /// Write the line of code to pop the back element of the data structure under test
          dataStructureUnderTest.pop_back();

        /////////////////////// END-TO-DO (3) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 2a:  Remove from the front of a vector
      std::vector<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "Vector", "Remove from the front", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (4) //////////////////////////////
          /// Write the line of code to erase the beginning element from the data structure under test
          dataStructureUnderTest.erase( dataStructureUnderTest.begin() );

        /////////////////////// END-TO-DO (4) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 3a: Search for an element in a vector
      std::vector<GroceryItem> dataStructureUnderTest;
      auto                     target_upc = "non-existent";
      measure( "Vector", "Search", [&]( const GroceryItem & item) {dataStructureUnderTest.emplace_back(item);}, [&] (auto&) {

        ///////////////////////// TO-DO (5) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to search for the Grocery Item within the data structure under test with
          /// a UPC matching the target UPC.  Return immediately upon finding the item, or when you know the item is not in the
          /// container.
          for ( const auto& item : dataStructureUnderTest ) {
            if ( item.upcCode() == target_upc ) return;
          }
          return;

        /////////////////////// END-TO-DO (5) ////////////////////////////

      } );
    }
  }








  /*********************************************************************************************************************************
  **  Collect Doubly Linked List Measurements
  *********************************************************************************************************************************/
  void collect_DoublyLinkedList_measurements()
  {
    {  // 1c:  Insert at the back of a doubly linked list
      std::list<GroceryItem> dataStructureUnderTest;
      measure( "DLL", "Insert at the back", noop, [&]( const GroceryItem & item ) {

        ///////////////////////// TO-DO (6) //////////////////////////////
          /// Write the line of code to push "item" at the back of the data structure under test
          dataStructureUnderTest.push_back( item );

        /////////////////////// END-TO-DO (6) ////////////////////////////

      } );
    }


    {  // 1c:  Insert at the front of a doubly linked list
      std::list<GroceryItem> dataStructureUnderTest;
      measure( "DLL", "Insert at the front", noop, [&]( const GroceryItem & item ) {

        ///////////////////////// TO-DO (7) //////////////////////////////
          /// Write the line of code to insert "item" at the beginning of the data structure under test
          dataStructureUnderTest.push_front( item );

        /////////////////////// END-TO-DO (7) ////////////////////////////

      } );
    }


    {  // 2c:  Remove from the back of a doubly linked list
      std::list<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "DLL", "Remove from the back", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (8) //////////////////////////////
          /// Write the line of code to pop the back element of the data structure under test
          dataStructureUnderTest.pop_back();

        /////////////////////// END-TO-DO (8) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 2c:  Remove from the front of a doubly linked list
      std::list<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "DLL", "Remove from the front", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (9) //////////////////////////////
          /// Write the line of code to pop the front element from the data structure under test
          dataStructureUnderTest.pop_front();

        /////////////////////// END-TO-DO (9) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 3c: Search for an element in a doubly linked list
      std::list<GroceryItem> dataStructureUnderTest;
      auto                   target_upc = "non-existent";
      measure( "DLL", "Search", [&]( const GroceryItem & item) {dataStructureUnderTest.emplace_back(item);}, [&] (auto&) {

        ///////////////////////// TO-DO (10) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to search for the Grocery Item within the data structure under test with
          /// a UPC matching the target UPC.  Return immediately upon finding the item, or when you know the item is not in the
          /// container.

          for ( const auto& item : dataStructureUnderTest ) {
            if ( item.upcCode() == target_upc ) return;
          }
          return;

        /////////////////////// END-TO-DO (10) ////////////////////////////

      } );
    }
  }








  /*********************************************************************************************************************************
  **  Collect Singly Linked List Measurements
  *********************************************************************************************************************************/
   void collect_SinglyLinkedList_measurements()
  {
    {  // 1b:  Insert at the back of a singly linked list
      std::forward_list<GroceryItem> dataStructureUnderTest;
      measure( "SLL", "Insert at the back", noop, [&]( const GroceryItem & item )  {

        ///////////////////////// TO-DO (11) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to insert "item" after the last node of the data structure under test.
          /// Since the SLL has no size() function and no tail pointer, you must walk the list looking for the last node.
          ///Hint:  Do not attempt to insert after "end()"

          auto iter = dataStructureUnderTest.begin();
          while ( iter != dataStructureUnderTest.end() ) {
            if ( ++iter == dataStructureUnderTest.end() ) dataStructureUnderTest.insert_after( iter, item );
          }

        /////////////////////// END-TO-DO (11) ////////////////////////////

      } );
    }


    {  // 1b:  Insert at the front of a singly linked list
      std::forward_list<GroceryItem> dataStructureUnderTest;
      measure( "SLL", "Insert at the front", noop, [&]( const GroceryItem & item ) {

        ///////////////////////// TO-DO (12) //////////////////////////////
          /// Write the line of code to push "item" at the front of the data structure under test
          dataStructureUnderTest.push_front( item );

        /////////////////////// END-TO-DO (12) ////////////////////////////

      } );
    }


    {  // 2b:  Remove from the back of a singly linked list
      std::forward_list<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "SLL", "Remove from the back", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (13) //////////////////////////////
          /// Write the lines of code (approximately 6 or 7) to remove the last node of the data structure under test. Since the SLL
          /// has no size() function and no tail pointer, you must walk the list looking for the last node.
          ///
          /// Hint:  If the data structure under test is empty, simply return.  Otherwise
          ///        o) Define two iterators called predecessor and current.  Initialize predecessor to the node before the
          ///           beginning, and current to the node at the beginning
          ///        o) Walk the list until current's next iterator is equal to end() and advance both predecessor and current each
          ///           time through the loop
          ///        o) Once current's next node is equal to end(), then erase the node after predecessor

          if ( dataStructureUnderTest.empty() ) return;

          auto predecessor = dataStructureUnderTest.before_begin();
          auto current     = dataStructureUnderTest.begin();

          while ( current != dataStructureUnderTest.end() ) {
            if ( ++current == dataStructureUnderTest.end() ) {
              dataStructureUnderTest.erase_after( predecessor );
            }
          ++predecessor;
          }

        /////////////////////// END-TO-DO (13) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 2b:  Remove from the front of a singly linked list
      std::forward_list<GroceryItem> dataStructureUnderTest( sampleData.cbegin(), sampleData.cend() );
      measure( "SLL", "Remove from the front", noop, [&]( const GroceryItem & ) {

        ///////////////////////// TO-DO (14) //////////////////////////////
          /// Write the line of code to pop the front element from the data structure under test
          dataStructureUnderTest.pop_front();

        /////////////////////// END-TO-DO (14) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 3b: Search for an element in a singly linked list
      std::forward_list<GroceryItem> dataStructureUnderTest;
      auto                   target_upc = "non-existent";
      measure( "SLL", "Search", [&]( const GroceryItem & item) {dataStructureUnderTest.push_front(item);}, [&] (auto&) {

        ///////////////////////// TO-DO (15) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to search for the Grocery Item within the data structure under test with
          /// a UPC matching the target UPC.  Return immediately upon finding the item, or when you know the item is not in the
          /// container.

          for ( auto& item : dataStructureUnderTest ){
            if ( item.upcCode() == target_upc ) return;
          }
          return;

        /////////////////////// END-TO-DO (15) ////////////////////////////

      } );
    }

 }








  /*********************************************************************************************************************************
  **  Collect Binary Search Tree Measurements
  *********************************************************************************************************************************/
  void collect_BinarySearchTree_measurements()
  {
    {  // 1d:  Insert into a binary search tree
      std::map<std::string, GroceryItem> dataStructureUnderTest;
      measure( "BST", "Insert", noop, [&]( const GroceryItem & item )  {

        ///////////////////////// TO-DO (16) //////////////////////////////
          /// Write the line of code to emplace (or insert) the key (UPC) and value (item) into the data structure under test.  You
          /// may use either the subscript operator, emplace, or insert function.

          dataStructureUnderTest.insert( std::make_pair( item.upcCode(), item) );

        /////////////////////// END-TO-DO (16) ////////////////////////////

      } );
    }


    {  // 2d:  Remove from a binary search tree
      std::map<std::string, GroceryItem> dataStructureUnderTest;
      for( const auto & groceryItem : sampleData ) dataStructureUnderTest.emplace( groceryItem.upcCode(), groceryItem );
      measure( "BST", "Remove", noop, [&]( const GroceryItem & item )  {

        ///////////////////////// TO-DO (17) //////////////////////////////
          /// Write the line of code to erase from the data structure under test the node that matches item's UPC

          dataStructureUnderTest.erase( item.upcCode() );

        /////////////////////// END-TO-DO (17) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 3d: Search for an element in a binary search tree
      std::map<std::string, GroceryItem> dataStructureUnderTest;
      auto                               target_upc = "non-existent";
      measure( "BST", "Search", [&]( const GroceryItem & item) {dataStructureUnderTest.emplace( item.upcCode(), item );}, [&] (auto&) {

        ///////////////////////// TO-DO (18) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to search for the Grocery Item within the data structure under test with
          /// a UPC matching the target UPC.  Return immediately upon finding the item, or when you know the item is not in the
          /// container.
          /// Note: do not implement a linear search, i.e., do not loop from beginning to end.

          dataStructureUnderTest.find ( target_upc );
          return;

        /////////////////////// END-TO-DO (18) ////////////////////////////

      } );
    }

  }








  /*********************************************************************************************************************************
  **  Collect Hash Table Measurements
  *********************************************************************************************************************************/
  void collect_HashTable_measurements()
  {
    {  // 1e:  Insert into a hash table
      std::unordered_map<std::string, GroceryItem> dataStructureUnderTest;
      measure( "Hash Table", "Insert", noop, [&]( const GroceryItem & item )  {

        ///////////////////////// TO-DO (19) //////////////////////////////
          /// Write the line of code to emplace (or insert) the key (UPC) and value (item) into the data structure under test.  You
          /// may use either the subscript operator, emplace, or insert function.

          dataStructureUnderTest.insert( std::make_pair( item.upcCode(), item ) );

        /////////////////////// END-TO-DO (19) ////////////////////////////

      } );
    }


    {  // 2e:  Remove from a hash table
      std::unordered_map<std::string, GroceryItem> dataStructureUnderTest;
      for( const auto & groceryItem : sampleData ) dataStructureUnderTest.emplace( groceryItem.upcCode(), groceryItem );
      measure( "Hash Table", "Remove", noop, [&]( const GroceryItem & item )  {

        ///////////////////////// TO-DO (20) //////////////////////////////
          /// Write the line of code to erase from the data structure under test the node that matches item's UPC

          dataStructureUnderTest.erase( item.upcCode() );

        /////////////////////// END-TO-DO (20) ////////////////////////////

      }, Direction::Shrink );
    }


    {  // 3d: Search for an element in a hash table
      std::unordered_map<std::string, GroceryItem> dataStructureUnderTest;
      auto                                         target_upc = "non-existent";
      measure( "Hash Table", "Search", [&]( const GroceryItem & item) {dataStructureUnderTest.emplace( item.upcCode(), item );}, [&] (auto&) {

        ///////////////////////// TO-DO (21) //////////////////////////////
          /// Write the lines of code (approximately 3 or 4) to search for the Grocery Item within the data structure under test with
          /// a UPC matching the target UPC.  Return immediately upon finding the item, or when you know the item is not in the
          /// container.
          /// Note: do not implement a linear search, i.e., do not loop from beginning to end.

          dataStructureUnderTest.erase( target_upc );

        /////////////////////// END-TO-DO (21) ////////////////////////////

      } );
    }

  }








  /*********************************************************************************************************************************
  **  Other Function Definitions
  *********************************************************************************************************************************/
  // Template function to measure the elapsed time consumed to perform a container's operation
  template<class Operation, class Preamble>
  void measure( const std::string & structureName,                            // free text name of data structure being measured
                const std::string & operationDescription,                     // free text name of the operation of the data structure being measured
                Preamble            preamble,                                 // set up work to occur before operation, expressed as a Functiod defaulted to "do nothing"
                Operation           operation,                                // operation to be measured, expressed as a Functiod
                Direction::value    direction )                               // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)
  {
    constexpr std::size_t SAMPLE_SIZE = 250;                                  // Number of operations to perform before reporting timing data
    Utilities::TimerUS    timer;                                              // measures wall clock time in microseconds

    std::size_t sampleIndex = (direction == Direction::Grow) ? 0 : sampleData.size();
    for( const auto & element : sampleData )
    {
      preamble( element );                                                    // perform any set work, but don't include this in the measured time

      timer.reset();                                                          // start the timer
      operation( element );                                                   // perform the operation and measure the elapsed wall clock time, subject to the OS's task scheduling
      std::size_t measuredTime = timer;                                       // stop the timer

      //if( sampleIndex % SAMPLE_SIZE  ==  0)                                 // uncomment if you want single samples, otherwise it accumulates all the samples over the interval
      runTimes[(sampleIndex / SAMPLE_SIZE) * SAMPLE_SIZE][structureName][operationDescription] += measuredTime;
      sampleIndex += direction;
    }
  }



  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix)
  {
    // dump the data collected in a tab-separated values (tsv) table, for example:
    //   Size  Vector/insert  Vector/Remove  List/insert  List/remove
    //   10    1              1              23           14
    //   20    3              2              40           37

    // Display the table header
    stream << "Size";
    for( const auto & [structure, operations] : matrix.begin()->second ) for( const auto & [operation, accumulatedTime] : operations )
    {
        stream << '\t' << structure << '/' << operation;
    }
    stream << '\n';

    // Display the table data
    for( const auto & [size, structures] : matrix )
    {
      stream << size;
      for( const auto & [structure, operations] : structures )  for( const auto & [operation, accumulatedTime] : operations )
      {
          stream << '\t' << accumulatedTime;
      }
      stream << '\n';
    }

    return stream;
  }
}    // namespace
