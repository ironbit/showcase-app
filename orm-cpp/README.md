# ORM CPP

## Description
The present sketch tries to implement an **interface** of a Object Relational Mapping (ORM) in the C++ programming language.

The goal of this design are:
* Present a clean and simple interface.
* Be used on the server side (concurrent).
* Designed based on high performance computing.

## Design
### Interface
In order to store the data using the Store (orm::store::Store) component, one way is to use a helper class called Property(orm::core::Property), and the other is to implement the Coder (orm::core::Coder) component for the Data Structure.

#### Using the Property component
```C++
using shareprop = orm::core::GenShareProperty
std::shared_ptr<orm::store::Factory> factory;

// create store component
auto store = factory->create();
std::int64_t identity = 1234;

// using parenthesis
store->insert(identity, shareprop("attribute 1", 3.1416)("attribute 2", "sample"));

// using curly brackets
store->insert(identity, shareprop({{"attribute 1", 3.1416},{"attribute 2", "sample"}});
```

#### Using the Coder Component
```C++
struct Person : public orm::core::Entity {
  using Coder = PersonCoder;

  std::int64_t identity;
  std::string  name
  double       height;
};

struct PersonDecoder : public orm::core::Coder<PersonCoder> {
  std::shared_ptr<orm::core::Property> encode(Person& person) {
    auto outcome = std::make_shared<orm::core::Property>();
    (*outcome)(Name, person.name());
    (*outcome)(Height, person.height());
    return outcome;
  }

  void decode(Person& person, const std::shared_ptr<orm::core::Property>& properties) {
    person.name() = std::string(properties->get(Name).To<const char*>());
    person.height() = properties->get(Height).To<double>();
  }
};


Person person;
person.identity = 1234;

// retrieve data from database
auto store = factory->create();
store->query(person);

// update the height in the cache (not database)
person.height = 1.8
store->update(person);
```

## Implementation
The Store component is designed like a smart pointer. Inside the Store component is a Memory component that holds the information as a cache. The Store class can be "cloned", which means that multiple Store components share the same Memory component.

Whether different Store components make a query of the same record in the database, each of the Store component will have a unique Memory component with the same data. Each Store component can change the cache without interfering. When the 'commit' function is used in the Store component, only then each component competes to store the information in the database.

```C++
using shareprop = orm::core::GenShareProperty
std::shared_ptr<orm::store::Factory> factory;

// create store component
auto store1 = factory->create();
std::int64_t id1 = 1234;
std::int64_t id2 = 4567;

// retrieve record from database
store1->query(id1);

// create clone - access store 1 cache
auto store2 = store1->clone();

// modify cache store 1 & store 2
store2(identity, shareprop("attribute 1", 3.1416))

// break link with store 1
// cache is for id2
store2->query(id2)
```

## High Performance
The idea behind this design is using transactional memory. It is not intended to use a 'global' structure that handles each of the records already read from the database; instead, it makes a copy of each of the records, and then they compete to alter the records securely in the database.