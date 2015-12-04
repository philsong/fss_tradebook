qmake
make
cd doc
doxygen tradebook.cfg

# Build process
:'
1. Check for dependencies
	Install them if needed
2. Check database exists
	Create if needed
3. Compile f8 classes
4. Generate Makefile ( qmake )
5. Compile ( make )
6. Generate documentation
'