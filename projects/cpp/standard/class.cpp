class ModernClass {
public:
	// Rule of zero: let compiler handle special members
	ModernClass() = default;
	~ModernClass() = default;
	
	// Or rule of five: define all special members
	class ExplicitClass {
	public:
		// Default constructor
		ExplicitClass() = default;
		// Default destructor
		~ExplicitClass() = default;
		// Default copy constructor
		ExplicitClass(const ExplicitClass&) = default;
		// Default move constructor
		ExplicitClass(ExplicitClass&&) noexcept = default;
		// Default copy assignment operator
		ExplicitClass& operator=(const ExplicitClass&) = default;
		// Default move assignment operator
		ExplicitClass& operator=(ExplicitClass&&) noexcept = default;
	};
	
	// Move-only class
	class MoveOnly {
	public:
		MoveOnly() = default;
		~MoveOnly() = default;
		MoveOnly(const MoveOnly&) = delete;
		MoveOnly& operator=(const MoveOnly&) = delete;
		MoveOnly(MoveOnly&&) noexcept = default;
		MoveOnly& operator=(MoveOnly&&) noexcept = default;
	};
	
	// Prevent inheritance
	class Final final {
		// Class contents...
	};
};


#include <string>
#include <vector>
#include <memory>

// Example 1: Why default is needed
class SimpleWithPointer {
	int* data_;
public:
	// Custom constructor
	SimpleWithPointer(int value) : data_(new int(value)) {}
	
	// Because we defined a custom constructor,
	// compiler won't generate default constructor automatically
	
	// Without this, class would have no default constructor
	SimpleWithPointer() = default;  // Generate default constructor
};

// Example 2: Move operations
class Widget {
	std::string name_;
	std::vector<int> data_;
public:
	// Once you declare any constructor, move operations
	// are not automatically generated
	Widget(const std::string& name) : name_(name) {}
	
	// Explicitly request compiler-generated versions
	Widget(Widget&&) = default;
	Widget& operator=(Widget&&) = default;
};

// Example 3: Complex case showing when defaulting is crucial
class Resource {
	std::unique_ptr<int> ptr_;
public:
	// Custom constructor
	Resource(int value) : ptr_(std::make_unique<int>(value)) {}
	
	// Because we have a unique_ptr, we can't use compiler-generated
	// copy operations, but move operations would work fine
	
	// These would be implicitly deleted because we have a unique_ptr
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;
	
	// Explicitly request move operations
	Resource(Resource&&) = default;  // Compiler generates correct move
	Resource& operator=(Resource&&) = default;
};

// Example 4: Base class with virtual functions
class Base {
public:
	virtual ~Base() = default;  // Virtual but still use default impl
	
	// Copy operations are not automatically generated 
	// for classes with virtual destructors
	Base(const Base&) = default;
	Base& operator=(const Base&) = default;
};

// Example 5: When defaulting is better than manual implementation
class Number {
	int value_;
public:
	Number(int v) : value_(v) {}
	
	// BAD: Manual implementation
	Number(const Number& other) {
		value_ = other.value_;
	}
	
	// GOOD: Let compiler do it
	Number(const Number& other) = default;
	
	// GOOD: Explicit about intent and better optimization
	Number& operator=(const Number&) = default;
};

// Example 6: Showing compiler-generated behavior
class ComplexDefault {
	std::string str_;
	std::vector<int> vec_;
	std::unique_ptr<int> ptr_;
	
public:
	// Custom constructor disables automatic generation
	// of other special members
	ComplexDefault(std::string s) : str_(std::move(s)) {}
	
	// Defaulted copy operations won't compile due to unique_ptr
	// ComplexDefault(const ComplexDefault&) = default;  // Error!
	
	// Move operations can be defaulted
	ComplexDefault(ComplexDefault&&) = default;
	ComplexDefault& operator=(ComplexDefault&&) = default;
	
	// Destructor can be defaulted
	~ComplexDefault() = default;
};

// Example 7: Using =default in template classes
template<typename T>
class Container {
	T value_;
	
public:
	Container() = default;
	
	// Conditional defaulting based on T's properties
	Container(const Container&) = default;
	Container& operator=(const Container&) = default;
	
	// Move operations always defaulted
	Container(Container&&) noexcept = default;
	Container& operator=(Container&&) noexcept = default;
};
