#include "Command.hpp"
#include "FileManager.hpp"
#include "CommandInterpreter.hpp"
#include "MakeFile.hpp"
#include <iostream>

//
//
//  BASIC TESTS
//  Basic object instantiation.
//
//
void test_makefile_creation() {
	MakeFile mk("makefile");
	std::cout << "test_makefile_creation: OK!" << std::endl;
}

void test_target_creation() {
	Target t1("test");
	std::cout << "test_target_creation: OK!" << std::endl;
}

void test_command_creation() {
	Command c1;
	std::cout << "test_command_creation: OK!" << std::endl;
}

void test_compiler_creation() {
	Compiler compiler("g++");
	std::cout << "test_compiler_creation: OK!" << std::endl;
}

void test_flag_creation() {
	Flag flag1("-o");
	std::cout << "test_flag_creation: OK!" << std::endl;
}

void test_file_creation() {
	File f1("main.cpp");
	std::cout << "test_file_creation: OK!" << std::endl;
}

//
//
//  WEAK TESTS
//  Interaction between objects and file generation.
//
void test_makefile_memory_insert() {
	MakeFile mk("makefile");

	// Creating targets
	Target t1("test");
	Target t2("compile");

	// Adding targets to makefile
	mk.add_target(t1);
	mk.add_target(t2);

	if(mk.get_targets().size() != 2) {
		std::cout << "###### ERROR: test_makefile_memory_insert" << std::endl;
		throw -1;
	}

	std::cout << "test_makefile_memory_insert: OK!" << std::endl;
}

void test_makefile_memory_delete() {
	MakeFile mk("makefile");

	// Creating targets
	Target t1("test");
	Target t2("compile");
	Target t3("teste2");
	Target t4("release");

	// Adding targets to makefile
	mk.add_target(t1);
	mk.add_target(t2);
	mk.add_target(t3);
	mk.add_target(t4);

	mk.remove_target();
	mk.remove_target();
	mk.remove_target();

	if(mk.get_targets().size() != 1) {
		std::cout << "###### ERROR: test_makefile_memory_delete" << std::endl;
		throw -1;
	}

	std::cout << "test_makefile_memory_delete: OK!" << std::endl;
}

void test_makefile_memory_add_target_twice() {
	MakeFile mk("makefile");
	int exception = 0;

	Target t1("test");
	try {
		mk.add_target(t1);
		mk.add_target(t1);
	} catch (int e) {
		exception = e;
	}

	if(mk.get_targets().size() != 1) {
		std::cout << "###### ERROR: test_makefile_memory_add_target_twice" << std::endl;
		throw -1;
	}

	if (exception == -1) {
		std::cout << "test_makefile_memory_add_target_twice: OK!" << std::endl;
	}
}

void test_makefile_memory_add_diff_target_with_same_name() {
	MakeFile mk("makefile");
	int error = 0;
	Target t1("test");
	Target t2("test");

	try {
		mk.add_target(t1);
		mk.add_target(t2);	
	} catch (int e) {
		error = e;
	}

	// The problem is that target isn't creating a valid title (it's empty).
	// Probably related to the Target constructor.


	if(mk.get_targets().size() != 1) {
		std::cout << "###### ERROR: test_makefile_memory_add_diff_target_with_same_name" << std::endl;
		throw -1;
	}

	if (error == -1) {
		std::cout << "test_makefile_memory_add_diff_target_with_same_name: OK!" << std::endl;
	}
	
}

/**

	This test should generate the following makefile:

	test: 
		g++ main.cpp testing.cpp lib.hpp -o -h
		g++ lib.hpp temp.hpp main.cpp --verbose

	compile:
		g++ temp.hpp temp.hpp -h -o
		g++ temp.hpp temp.hpp -h -o

*/
void test_makefile_disk() {

	// Creating Makefile.
	MakeFile mk("makefile");

	// Creating targets
	Target t1("test");
	Target t2("compile");

	// Creating commands
	Command c1, c2, c3;

	// Creating and setting compiler into commands
	Compiler compiler("g++");
	c1.set_compiler(compiler);
	c2.set_compiler(compiler);
	c3.set_compiler(compiler);

	// Creating flags
	Flag flag1("-o");
	Flag flag2("-h");
	Flag flag3("--verbose");

	// Creating files
	File f1("main.cpp");
	File f2("testing.cpp");
	File f3("temp.hpp");
	File f4("lib.hpp");

	// Associating flags with commands
	c1.add_flag(flag1);
	c1.add_flag(flag2);
	c2.add_flag(flag2);
	c2.add_flag(flag1);
	c3.add_flag(flag3);

	// Associating files with commands
	c1.add_file(f1);
	c1.add_file(f2);
	c1.add_file(f4);
	c2.add_file(f3);
	c2.add_file(f3);
	c3.add_file(f4);
	c3.add_file(f3);
	c3.add_file(f1);

	// Associating commands with targets
	t1.add_command(c1);
	t1.add_command(c3);
	t2.add_command(c2);
	t2.add_command(c2);

	// Adding targets to makefile
	mk.add_target(t1);
	mk.add_target(t2);

	// Saving makefile
	mk.save();

	std::cout << "test_makefile_create: OK!" << std::endl;
}

int main(int argc, char* argv[]) {

	// Basic tests
	std::cout << "\n# Basic tests (1/2): " << std::endl;
	test_makefile_creation();
	test_file_creation();
	test_flag_creation();
	test_compiler_creation();
	test_command_creation();
	test_target_creation();

	// Weak tests
	std::cout << "\n# Weak tests (2/2): " << std::endl;
	test_makefile_disk();
	test_makefile_memory_insert();
	test_makefile_memory_delete();
	test_makefile_memory_add_target_twice();
	test_makefile_memory_add_diff_target_with_same_name();

}