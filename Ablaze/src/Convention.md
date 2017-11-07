Ablaze Engine

CONVENTION:

All classes/structs/functions are to be written under namespace "Ablaze"
Further namespacing can be applied as see fit

FOLDER STRUCTURE:
	All folders must contain __FOLDERNAME__.h which includes all files in the folder
	One class/struct per file, enums may be declared alongside classes and structs

OBJECTS:
	All Classes must derive from class Object (except static classes)
	All non-static members must be declared with m_ prefix (except public members)
	All static members must be declared with s_ prefix (except public members)

	All public methods must be declared with PascalCase
	All members to be declared with camelCase
	All members to be declared at the top of the class/struct declaration
	Methods and members must be separated by Visibility Group
	Static variables and methods must be separated from member variables and methods by Visibility Group

	Names of classes and structs must be PascalCase
	No classes or structs are to share the same names even across namespaces

	AB_API is to be used for all class and struct declarations

	STRUCTS:
		Must expose at least one public member to be declared as a struct
		Structs do not need to inherit from Object

	CLASSES:
		Cannot expose any public members or public static members
		Must contain at least one constructor and method (appart from methods defined in Object.h)
		All members must be initialised in Initialiser list

		Example Class:

		class GameObject : public Object
		{
		private:
			int m_Age;
			String m_Name;

		public:
			GameObject(int age, const String& name);

			int GetAge() const;
			const String& GetName() const;

		public:
			static int GameObjectCount();

		private:
			void SetAge(int age);
			void SetName(const String& name);

		}

	INTERFACES:
		Must begin name with I (eg IRenderable)
		No implementation at all

	TEMPLATES:
		Template classes and methods are to be completely defined in the header file

INCLUDES:
	All outside libraries will be included with <>
	All internal dependencies will be include with ""
	"..\" syntax is not to be used except in specific cases
	All file includes will be made with "\" not "/"