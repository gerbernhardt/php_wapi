class MyClass : public Php::Base
{
	/**
	*  First factory method
	*  @return Php::Value      object holding a new MyClass instance
	*/
	static Php::Value factory1()
	{
		// use the Php::Object class to create an instance (this will
		// result in __construct() being called)
		return Php::Object("MyClass");
	}

	/**
	*  Alternative factory method
	*  @return Php::Value
	*/
	static Php::Value factory2()
	{
		// create an instance ourselves
		MyClass *object = new MyClass();

		// the object now only exists as C++ object, to ensure that it is also
		// registered as an object in PHP user space, we wrap it in a
		// Php::Object class (which is an extended Php::Value class). Because
		// PHP supports reflection it is necessary to also pass in the class
		// name. The __construct() method will _not_ be called - because the
		// C++ object is already instantiated.
		return Php::Object("MyClass", object);
	}

	/**
	*  Method that returns 'this' to allow chaining ($x->chain()->chain()).
	*  @return Php::Value
	*/
	Php::Value chain()
	{
		// the Php::Value has an implicit constructor for Php::Base pointers.
		// This means that you can safely return 'this' from a method, which
		// will automatically be converted into a valid Php::Value object. This
		// works only for pointers to objects that already exist in PHP user
		// space.
		return this;
	}

	/**
	*  Method that gets a MyClass instance as parameter
	*  @param  params      vector holding all parameters
	*/
	void process(Php::Parameters &params)
	{
		// store the first parameter in a Php::Value object
		Php::Value value = params[0];

		// if you know for sure that the 'value' variable holds a (wrapped)
		// instance of a MyClass object, you can convert the value back into
		// a pointer to the original C++ object by calling the 'implementation'
		// method.
		//
		// Note that this only works for value objects that hold instances of
		// C++ classes defined by your extension! Calling the 'implementation()'
		// method on a non-object, on an object of a user space class, or of
		// a core PHP class or a class from a different extension will probably
		// result in a crash!
		MyClass *object = (MyClass *)value.implementation();
	}
};